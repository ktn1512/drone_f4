/* Flight mode truc dung cho AUTO (T mode 2). Xem flight_mode.h.
 * Tham so ga dua tren do dac bench: drone nhac khoi dat trong khoang
 * 1390-1420 us (1420 ~ +0.2 m/s). CAN THU LAI khi doi pin/canh/khoi luong.
 */
#include "flight_mode.h"
#include <math.h>
#include <string.h>

/* ---- Ga co ban ---- */
#define FM_MOTOR_OFF_US          1000.0f
#define FM_IDLE_US               1150.0f  /* quay khong tai tren mat dat */
#define FM_HOVER_GUESS_US        1400.0f  /* do thuc te 1390-1420 us */
#define FM_HOVER_MIN_US          1250.0f  /* gioi han hop ly cho hover_ref */
#define FM_HOVER_MAX_US          1600.0f

/* ---- Cat canh ---- */
#define FM_SPOOLUP_RATE_US_S      250.0f  /* idle -> (hover - 30) trong ~0.9 s */
#define FM_SPOOLUP_BELOW_HOVER_US  30.0f
#define FM_TAKEOFF_RATE_US_S       30.0f  /* tang cham qua vung nhac khoi dat */
#define FM_TAKEOFF_MAX_ABOVE_US    80.0f  /* tran ga cat canh = hover + 80 */
#define FM_TAKEOFF_TIMEOUT_MS    6000U    /* ~3.7 s ramp + ~2 s giu tran */
#define FM_LIFTOFF_ALT_M           0.25f  /* tren mat dat */
#define FM_LIFTOFF_VZ_MPS          0.10f
#define FM_LIFTOFF_CONFIRM_MS     300U
/* Dau hieu dang nhac (truoc khi xac nhan): ngung tang ga de khong vot. */
#define FM_LIFTING_ALT_M           0.10f
#define FM_LIFTING_VZ_MPS          0.15f
#define FM_LIFTOFF_TRIM_BACKOFF_US 10.0f  /* ga luc roi dat dang hoi du luc nang */
#define FM_TAKEOFF_TARGET_M        0.50f  /* giu o mat dat + 0.5 m */

/* ---- Ha canh ---- */
#define FM_LAND_FLOOR_BELOW_HOVER_US 60.0f /* san ga khi dang ha (climb < 0) */
#define FM_LAND_BAND_M             0.15f
#define FM_LAND_STILL_MPS          0.06f
#define FM_LAND_THR_DROP_US        40.0f
#define FM_LAND_ACCEL_MIN_G        0.95f  /* mat dat do: |a| khong hut xuong */
#define FM_LAND_CONFIRM_MS        1000U
#define FM_SPOOLDOWN_RATE_US_S    200.0f
#define FM_IDLE_HOLD_MS           1000U

/* ---- Hoc ga treo ---- */
#define FM_HOVER_LEARN_TAU_S       1.0f
#define FM_HOVER_LEARN_MIN_ALT_M   0.30f
#define FM_HOVER_LEARN_AFTER_MS   2000U

/* ---- Khan cap (baro loi giua troi), giu nguyen thong so cu ---- */
#define FM_EMERG_START_DROP_US    25.0f
#define FM_EMERG_RAMP_US_S         3.0f
#define FM_EMERG_ASSUMED_MPS       0.30f
#define FM_EMERG_EXTRA_MS        6000U
#define FM_EMERG_MAX_MS         30000U
#define FM_EMERG_MAX_START_US   1650.0f

/* ---- Bo gioi han giam ga o dau ra (luoi an toan cho moi chuyen trang thai).
 * Bang toc do slew cua AltitudeHold de khong lam meo vong do cao. */
#define FM_OUT_MAX_DROP_US_S     500.0f

#define FM_BARO_VZ_TAU_S           0.25f
#define FM_ACCEL_TAU_S             0.50f
#define FM_LAND_VZ_TAU_S           0.50f

static float clampf(float x, float lo, float hi)
{
    return x < lo ? lo : (x > hi ? hi : x);
}

static void enter(FlightMode_t *fm, FlightState_t s, uint32_t now)
{
    fm->state = s;
    fm->state_since_ms = now;
    fm->cond_since_ms = 0U;
}

/* Hen gio xac nhan: tra 1 khi cond giu lien tuc >= hold_ms. */
static uint8_t confirm(FlightMode_t *fm, uint8_t cond, uint32_t now, uint32_t hold_ms)
{
    if (!cond)
    {
        fm->cond_since_ms = 0U;
        return 0U;
    }
    if (fm->cond_since_ms == 0U)
    {
        fm->cond_since_ms = now | 1U;
        return 0U;
    }
    return (uint32_t)(now - fm->cond_since_ms) >= hold_ms;
}

static void start_spooldown(FlightMode_t *fm, float from_us, uint8_t reason, uint32_t now)
{
    AltitudeHold_Reset(&fm->alt);
    fm->state_thr_us = clampf(from_us, FM_MOTOR_OFF_US, FM_EMERG_MAX_START_US);
    fm->exit_reason = reason;
    enter(fm, FM_SPOOLDOWN, now);
}

/* Baro loi khi dang bay: ha vong ho, KHONG cat motor. */
static void start_emergency(FlightMode_t *fm, uint8_t reason, uint32_t now)
{
    float hover = fm->alt.trim_us + fm->alt.integral_us;
    if (!isfinite(hover))
        hover = fm->hover_ref_us;
    /* Integral co the dang windup: khong khoi dau cao hon ga treo da hoc. */
    if (fm->hover_learned && hover > fm->hover_ref_us)
        hover = fm->hover_ref_us;
    fm->emerg_start_us = clampf(hover - FM_EMERG_START_DROP_US, FM_IDLE_US,
                                FM_EMERG_MAX_START_US);
    float h = fm->alt.target_m - fm->ground_alt_m;
    if (!isfinite(h) || h < 0.0f)
        h = 0.0f;
    if (h > 20.0f)
        h = 20.0f;
    uint32_t d = (uint32_t)(h / FM_EMERG_ASSUMED_MPS * 1000.0f) + FM_EMERG_EXTRA_MS;
    fm->emerg_duration_ms = (d > FM_EMERG_MAX_MS) ? FM_EMERG_MAX_MS : d;
    fm->exit_reason = reason;
    fm->fault_latched = 1U;
    ++fm->fault_count;
    AltitudeHold_Reset(&fm->alt);
    enter(fm, FM_EMERGENCY, now);
}

static void update_estimators(FlightMode_t *fm, const FlightInputs_t *in)
{
    const float dt = in->dt_s;
    if (isfinite(in->accel_norm_g) && isfinite(dt) && dt > 0.0f)
    {
        if (fm->accel_lpf_g <= 0.0f)
            fm->accel_lpf_g = in->accel_norm_g;
        else
            fm->accel_lpf_g += (dt / (FM_ACCEL_TAU_S + dt)) *
                               (in->accel_norm_g - fm->accel_lpf_g);
    }
    if (!in->baro_healthy)
    {
        fm->baro_vz_valid = 0U;
        fm->baro_vz_mps = 0.0f;
        return;
    }
    if (!in->baro_new || !isfinite(in->baro_alt_m))
        return;
    const uint32_t dms = in->baro_sample_ms - fm->baro_last_ms;
    if (fm->baro_vz_valid && dms >= 15U && dms <= 180U)
    {
        const float bdt = (float)dms * 0.001f;
        const float raw = (in->baro_alt_m - fm->baro_last_alt_m) / bdt;
        if (isfinite(raw) && fabsf(raw) < 12.0f)
            fm->baro_vz_mps += (bdt / (FM_BARO_VZ_TAU_S + bdt)) * (raw - fm->baro_vz_mps);
    }
    else
    {
        fm->baro_vz_mps = 0.0f;
    }
    fm->baro_last_alt_m = in->baro_alt_m;
    fm->baro_last_ms = in->baro_sample_ms;
    fm->baro_vz_valid = 1U;
}

void FlightMode_Init(FlightMode_t *fm)
{
    if (fm == NULL)
        return;
    memset(fm, 0, sizeof(*fm));
    fm->state = FM_DISARMED;
    fm->throttle_us = FM_MOTOR_OFF_US;
    fm->target_us = FM_MOTOR_OFF_US;
    fm->hover_ref_us = FM_HOVER_GUESS_US;
}

void FlightMode_Kill(FlightMode_t *fm, uint8_t reason)
{
    if (fm == NULL)
        return;
    if (fm->state != FM_DISARMED)
        fm->exit_reason = reason;
    AltitudeHold_Reset(&fm->alt);
    fm->state = FM_DISARMED;
    fm->cond_since_ms = 0U;
    fm->fault_latched = 1U;
    fm->throttle_us = fm->target_us = FM_MOTOR_OFF_US;
}

uint8_t FlightMode_AttitudeCmdEnabled(const FlightMode_t *fm)
{
    return fm && (fm->state == FM_ALT_HOLD || fm->state == FM_LANDING);
}

uint8_t FlightMode_Active(const FlightMode_t *fm)
{
    return fm && (fm->state == FM_SPOOLUP || fm->state == FM_TAKEOFF ||
                  fm->state == FM_ALT_HOLD || fm->state == FM_LANDING ||
                  fm->state == FM_EMERGENCY);
}

/* Huy cat canh tren mat dat (chua roi dat). Tra 1 neu da huy. */
static uint8_t ground_abort(FlightMode_t *fm, const FlightInputs_t *in)
{
    uint8_t reason;
    if (!in->baro_healthy)
    {
        reason = ALT_EXIT_BARO;
        fm->fault_latched = 1U;
    }
    else if (in->link_lost)
        reason = ALT_EXIT_FAILSAFE_LANDED;
    else if (in->climb_cmd < 0)
        reason = ALT_EXIT_LANDED;
    else
        return 0U;
    start_spooldown(fm, fm->state_thr_us, reason, in->now_ms);
    return 1U;
}

static void step_airborne(FlightMode_t *fm, const FlightInputs_t *in)
{
    const uint32_t now = in->now_ms;
    const float dt = in->dt_s;

    if (!in->baro_healthy)
    {
        start_emergency(fm, ALT_EXIT_BARO_LATCHED, now);
        return;
    }
    if (in->baro_new &&
        !AltitudeHold_Update(&fm->alt, in->baro_alt_m, in->baro_sample_ms, in->climb_cmd))
    {
        start_emergency(fm, ALT_EXIT_UPDATE_FAULT, now);
        return;
    }

    const FlightState_t want = (in->climb_cmd < 0) ? FM_LANDING : FM_ALT_HOLD;
    if (want != fm->state)
    {
        if (want == FM_ALT_HOLD)
        {
            /* Roi LANDING: integral co the da bi keo xuong duoi san ga.
             * Can lai de ga KHONG tut tu san xuong (bumpless). */
            AltitudeHold_AlignOutput(&fm->alt);
        }
        else
        {
            fm->land_vz_lpf = fm->alt.vz_mps;
        }
        enter(fm, want, now);
    }

    /* Hoc ga treo chi khi dang bay that, dung yen, khong co lenh doc. */
    const float height = fm->alt.altitude_m - fm->ground_alt_m;
    if (fm->state == FM_ALT_HOLD && in->climb_cmd == 0 &&
        fabsf(fm->alt.vz_mps) < 0.10f && height > FM_HOVER_LEARN_MIN_ALT_M &&
        (uint32_t)(now - fm->airborne_since_ms) > FM_HOVER_LEARN_AFTER_MS)
    {
        fm->hover_ref_us += (dt / (FM_HOVER_LEARN_TAU_S + dt)) *
                            (fm->alt.throttle_us - fm->hover_ref_us);
        fm->hover_ref_us = clampf(fm->hover_ref_us, FM_HOVER_MIN_US, FM_HOVER_MAX_US);
        fm->hover_learned = 1U;
    }

    if (fm->state == FM_LANDING)
    {
        const float floor_us = fm->hover_ref_us - FM_LAND_FLOOR_BELOW_HOVER_US;
        if (fm->alt.throttle_us < floor_us)
            fm->alt.throttle_us = floor_us;

        fm->land_vz_lpf += (dt / (FM_LAND_VZ_TAU_S + dt)) * (fm->alt.vz_mps - fm->land_vz_lpf);
        const uint8_t still = fabsf(fm->land_vz_lpf) < FM_LAND_STILL_MPS;
        /* Dang roi tu do / thieu luc nang thi |a| < 1 g; mat dat do thi ~1 g. */
        const uint8_t supported = fm->accel_lpf_g > FM_LAND_ACCEL_MIN_G;
        const uint8_t near_ground = height < FM_LAND_BAND_M;
        const float thr_drop = fm->hover_ref_us - fm->alt.throttle_us;
        /* Ga bi ghim o san ma van dung yen: chi xay ra khi mat dat do.
         * Tren khong, ga thap hon treo 60 us thi drone phai tang toc xuong. */
        const uint8_t pinned = fm->alt.throttle_us <= floor_us + 1.0f;
        const uint8_t landed_like = still && supported &&
                                    ((near_ground && thr_drop > FM_LAND_THR_DROP_US) || pinned);
        if (confirm(fm, landed_like, now, FM_LAND_CONFIRM_MS))
        {
            start_spooldown(fm, fm->alt.throttle_us,
                            in->link_lost ? ALT_EXIT_FAILSAFE_LANDED : ALT_EXIT_LANDED, now);
            return;
        }
    }
    fm->target_us = fm->alt.throttle_us;
}

void FlightMode_Step(FlightMode_t *fm, const FlightInputs_t *in)
{
    if (fm == NULL || in == NULL)
        return;
    const uint32_t now = in->now_ms;
    const float dt = (isfinite(in->dt_s) && in->dt_s > 0.0f) ? in->dt_s : 0.0f;
    update_estimators(fm, in);

    if (!in->auto_mode)
    {
        /* DUNG (mode 0) = kill switch: cat ngay, ke ca dang ha khan cap. */
        if (fm->state != FM_DISARMED)
            fm->exit_reason = ALT_EXIT_STOPPED;
        AltitudeHold_Reset(&fm->alt);
        enter(fm, FM_DISARMED, now);
        fm->fault_latched = 0U;
        fm->prev_auto = 0U;
        fm->throttle_us = fm->target_us = FM_MOTOR_OFF_US;
        return;
    }
    if (!fm->prev_auto)
    {
        /* Vua vao AUTO: bat dau sach. */
        AltitudeHold_Reset(&fm->alt);
        enter(fm, FM_DISARMED, now);
        fm->fault_latched = 0U;
        fm->prev_auto = 1U;
    }

    switch (fm->state)
    {
    case FM_DISARMED:
        fm->target_us = FM_MOTOR_OFF_US;
        if (!fm->fault_latched && in->baro_healthy && fm->baro_vz_valid &&
            !in->link_lost && in->climb_cmd > 0)
        {
            fm->ground_alt_m = in->baro_alt_m;
            fm->state_thr_us = FM_IDLE_US;
            fm->exit_reason = ALT_EXIT_NONE;
            enter(fm, FM_SPOOLUP, now);
            fm->target_us = fm->state_thr_us;
        }
        break;

    case FM_SPOOLUP:
    {
        if (ground_abort(fm, in))
            break;
        const float goal = fm->hover_ref_us - FM_SPOOLUP_BELOW_HOVER_US;
        fm->state_thr_us += FM_SPOOLUP_RATE_US_S * dt;
        if (fm->state_thr_us >= goal)
        {
            fm->state_thr_us = goal;
            enter(fm, FM_TAKEOFF, now);
        }
        fm->target_us = fm->state_thr_us;
        break;
    }

    case FM_TAKEOFF:
    {
        if (ground_abort(fm, in))
            break;
        const float cap = fm->hover_ref_us + FM_TAKEOFF_MAX_ABOVE_US;
        const uint8_t lifting = fm->baro_vz_valid &&
                                ((in->baro_alt_m - fm->ground_alt_m) > FM_LIFTING_ALT_M ||
                                 fm->baro_vz_mps > FM_LIFTING_VZ_MPS);
        if (!lifting)
            fm->state_thr_us += FM_TAKEOFF_RATE_US_S * dt;
        if (fm->state_thr_us > cap)
            fm->state_thr_us = cap;
        fm->target_us = fm->state_thr_us;

        const uint8_t lifted = fm->baro_vz_valid &&
                               (in->baro_alt_m - fm->ground_alt_m) > FM_LIFTOFF_ALT_M &&
                               fm->baro_vz_mps > FM_LIFTOFF_VZ_MPS;
        if (confirm(fm, lifted, now, FM_LIFTOFF_CONFIRM_MS))
        {
            const float thr = fm->state_thr_us;
            if (AltitudeHold_Start(&fm->alt, in->baro_alt_m,
                                   thr - FM_LIFTOFF_TRIM_BACKOFF_US, in->baro_sample_ms))
            {
                fm->alt.throttle_us = thr; /* lien tuc, khong nhay ga */
                const float tgt = fm->ground_alt_m + FM_TAKEOFF_TARGET_M;
                if (tgt > fm->alt.target_m)
                    fm->alt.target_m = tgt;
                fm->airborne_since_ms = now;
                enter(fm, FM_ALT_HOLD, now);
                fm->target_us = thr;
            }
            else
            {
                start_spooldown(fm, thr, ALT_EXIT_UPDATE_FAULT, now);
                fm->fault_latched = 1U;
            }
            break;
        }
        if ((uint32_t)(now - fm->state_since_ms) > FM_TAKEOFF_TIMEOUT_MS)
        {
            start_spooldown(fm, fm->state_thr_us, ALT_EXIT_TAKEOFF_FAIL, now);
            fm->fault_latched = 1U;
        }
        break;
    }

    case FM_ALT_HOLD:
    case FM_LANDING:
        step_airborne(fm, in);
        break;

    case FM_EMERGENCY:
    {
        const uint32_t elapsed = now - fm->state_since_ms;
        float thr = fm->emerg_start_us - FM_EMERG_RAMP_US_S * ((float)elapsed * 0.001f);
        if (thr < FM_IDLE_US)
            thr = FM_IDLE_US;
        if (elapsed >= fm->emerg_duration_ms)
        {
            /* Het thoi gian uoc luong: ha dan ve idle, KHONG nhay 1000. */
            start_spooldown(fm, thr, ALT_EXIT_EMERG_LANDED, now);
            fm->fault_latched = 1U;
            break;
        }
        fm->target_us = thr;
        break;
    }

    case FM_SPOOLDOWN:
        fm->state_thr_us -= FM_SPOOLDOWN_RATE_US_S * dt;
        if (fm->state_thr_us <= FM_IDLE_US)
        {
            fm->state_thr_us = FM_IDLE_US;
            if (confirm(fm, 1U, now, FM_IDLE_HOLD_MS))
            {
                enter(fm, FM_DISARMED, now);
                fm->target_us = FM_MOTOR_OFF_US;
                fm->throttle_us = FM_MOTOR_OFF_US; /* idle -> dung, da tren mat dat */
                return;
            }
        }
        fm->target_us = fm->state_thr_us;
        break;

    default:
        FlightMode_Kill(fm, ALT_EXIT_UPDATE_FAULT);
        return;
    }

    /* Bo gioi han giam ga dau ra. Tang ga do tung trang thai tu gioi han. */
    if (fm->state == FM_DISARMED || fm->target_us >= fm->throttle_us)
    {
        fm->throttle_us = fm->target_us;
    }
    else
    {
        const float min_us = fm->throttle_us - FM_OUT_MAX_DROP_US_S * dt;
        fm->throttle_us = (fm->target_us < min_us) ? min_us : fm->target_us;
    }
}
