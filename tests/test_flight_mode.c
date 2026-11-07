/* Host test cho flight_mode.c + altitude_hold.c voi mo hinh truc dung don gian.
 *
 * Mo hinh (GIA DINH, chi de kiem tra logic, KHONG phai mo hinh bay chinh xac):
 *   T/m = g * ((thr - 1000) / (hover - 1000))^2 ; drag c/m = 3 1/s
 *   hover = 1405 us -> 1420 us cho van toc leo on dinh ~0.25 m/s (do bench: ~0.2).
 *   Baro: do cao that + nhieu Gauss 3 cm, LPF alpha 0.2 o 32 Hz, doc moi 10 ms
 *   (giong DPS310_ReadIfReady + main.c). Accel norm = (T - c v)/m / g khi bay,
 *   = 1 g khi nam tren dat.
 *
 * Kiem tra bat bien an toan:
 *   - Khi drone con tren khong (z > 2 cm) ga KHONG giam nhanh hon 500 us/s.
 *   - Khong phat hien "cham dat" khi z > 5 cm.
 *   - Chi DUNG (mode 0) moi duoc cat ga theo buoc.
 */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "flight_mode.h"

#define G 9.81f
static int failures;
#define CHECK(c, ...) do { if (!(c)) { ++failures; printf("FAIL %s:%d: ", __FILE__, __LINE__); printf(__VA_ARGS__); printf("\n"); } } while (0)

typedef struct
{
    float hover_us;   /* ga treo that cua "drone"; 0 = khong lap canh */
    float z, v;       /* m, m/s (len la duong) */
    float baro_f;     /* ap suat-do cao da loc (m) */
    int baro_init;
    float baro_bias;  /* troi baro (m) */
    int baro_dead;    /* 1 = baro ngung cap mau */
    uint32_t next_sample_ms, last_poll_ms;
    int pending;
    uint32_t last_update_ms;
} Plant;

static float gauss(void)
{
    float u = (rand() + 1.0f) / (RAND_MAX + 2.0f), w = (rand() + 1.0f) / (RAND_MAX + 2.0f);
    return sqrtf(-2.0f * logf(u)) * cosf(6.2831853f * w);
}

/* Tra |a| (g). */
static float plant_step(Plant *p, float thr, float dt)
{
    float tm = 0.0f;
    if (p->hover_us > 1000.0f && thr > 1000.0f)
    {
        float x = (thr - 1000.0f) / (p->hover_us - 1000.0f);
        tm = G * x * x;
    }
    float acc = tm - G - 3.0f * p->v;
    if (p->z <= 0.0f && acc < 0.0f)
    {
        p->z = 0.0f;
        p->v = 0.0f;
        return 1.0f; /* mat dat do */
    }
    p->v += acc * dt;
    p->z += p->v * dt;
    if (p->z < 0.0f)
    {
        p->z = 0.0f;
        p->v = 0.0f;
    }
    return fabsf(tm - 3.0f * p->v) / G;
}

typedef struct
{
    const char *name;
    int climb;        /* lenh tu ESP (truoc failsafe) */
    int link_lost;
    int auto_mode;
} Cmd;

typedef struct
{
    float max_drop_air;     /* us/s lon nhat khi z > 2 cm */
    float max_z;
    int landed_in_air;
    int reached_alt_hold;
    uint32_t liftoff_ms;
} Stats;

static FlightMode_t fm;
static Plant pl;
static uint32_t t_ms;
static Stats st;

static void reset_world(float hover_us)
{
    FlightMode_Init(&fm);
    pl = (Plant){0};
    pl.hover_us = hover_us;
    t_ms = 1000U;
    pl.next_sample_ms = t_ms;
    st = (Stats){0};
}

/* Chay n ms voi lenh co dinh, buoc 2 ms nhu vong 500 Hz. */
static void run(const Cmd *c, uint32_t dur_ms, int verbose)
{
    const float dt = 0.002f;
    for (uint32_t k = 0; k < dur_ms; k += 2U)
    {
        t_ms += 2U;
        /* DPS310: mau moi moi 31 ms, main doc moi 10 ms. */
        if (t_ms >= pl.next_sample_ms)
        {
            pl.next_sample_ms += 31U;
            pl.pending = 1;
        }
        int baro_new = 0;
        if (t_ms - pl.last_poll_ms >= 10U)
        {
            pl.last_poll_ms = t_ms;
            if (pl.pending && !pl.baro_dead)
            {
                pl.pending = 0;
                float raw = pl.z + pl.baro_bias + 0.03f * gauss();
                pl.baro_f = pl.baro_init ? pl.baro_f + 0.2f * (raw - pl.baro_f) : raw;
                pl.baro_init = 1;
                pl.last_update_ms = t_ms;
                baro_new = 1;
            }
        }
        float before = fm.throttle_us;
        float z_before = pl.z;
        FlightInputs_t in = {
            .now_ms = t_ms,
            .dt_s = dt,
            .auto_mode = (uint8_t)c->auto_mode,
            .link_lost = (uint8_t)c->link_lost,
            .climb_cmd = (int16_t)(c->link_lost ? -60 : c->climb),
            .baro_healthy = (uint8_t)(pl.baro_init && (t_ms - pl.last_update_ms) <= 180U),
            .baro_new = (uint8_t)baro_new,
            .baro_alt_m = pl.baro_f,
            .baro_sample_ms = pl.last_update_ms,
            .accel_norm_g = 1.0f,
        };
        static float last_acc = 1.0f;
        in.accel_norm_g = last_acc + 0.02f * gauss(); /* rung nho */
        FlightState_t s0 = fm.state;
        FlightMode_Step(&fm, &in);
        if (s0 == FM_TAKEOFF && fm.state == FM_ALT_HOLD)
            st.liftoff_ms = t_ms;
        if (fm.state == FM_ALT_HOLD)
            st.reached_alt_hold = 1;
        if ((s0 == FM_LANDING) && fm.state == FM_SPOOLDOWN && z_before > 0.05f)
            st.landed_in_air = 1;
        float drop = (before - fm.throttle_us) / dt;
        if (z_before > 0.02f && drop > st.max_drop_air)
            st.max_drop_air = drop;
        last_acc = plant_step(&pl, fm.throttle_us, dt);
        if (pl.z > st.max_z)
            st.max_z = pl.z;
        if (verbose && (t_ms % 500U) == 0U)
            printf("  %-10s t=%6.2f fs=%d thr=%7.1f z=%5.2f v=%5.2f baro=%5.2f hov=%6.1f exit=%u\n",
                   c->name, t_ms / 1000.0f, fm.state, fm.throttle_us, pl.z, pl.v,
                   pl.baro_f, fm.hover_ref_us, fm.exit_reason);
    }
}

static void test_takeoff_hold_land(int verbose)
{
    printf("== Cat canh -> giu -> ha canh (hover that 1405 us)\n");
    reset_world(1405.0f);
    Cmd idle = {"ground", 0, 0, 1}, up = {"takeoff", 100, 0, 1}, hold = {"hold", 0, 0, 1},
        down = {"down", -100, 0, 1};
    run(&idle, 3000, 0);  /* baro on dinh */
    run(&up, 1500, verbose);   /* UI: nut cat canh chi giu climb>0 ~1.5 s */
    run(&hold, 15000, verbose);
    CHECK(st.reached_alt_hold, "khong vao ALT_HOLD");
    CHECK(st.liftoff_ms != 0U && st.liftoff_ms - 4000U < 6000U, "liftoff qua cham: %u ms", st.liftoff_ms);
    CHECK(fabsf(pl.z - 0.5f) < 0.2f, "khong giu ~0.5 m: z=%.2f", pl.z);
    CHECK(fm.hover_learned && fabsf(fm.hover_ref_us - 1405.0f) < 15.0f,
          "hover_ref hoc sai: %.1f", fm.hover_ref_us);
    run(&down, 12000, verbose);
    CHECK(fm.state == FM_DISARMED, "khong disarm sau ha canh, fs=%d", fm.state);
    CHECK(fm.exit_reason == ALT_EXIT_LANDED, "exit=%u", fm.exit_reason);
    CHECK(pl.z < 0.01f, "disarm khi chua cham dat z=%.2f", pl.z);
    CHECK(!st.landed_in_air, "phat hien cham dat khi con tren khong");
    CHECK(st.max_drop_air <= 501.0f, "ga giam %.0f us/s khi dang bay", st.max_drop_air);
    printf("   liftoff sau %.2f s tu luc bam, hover_ref=%.1f, max drop tren khong=%.0f us/s\n",
           (st.liftoff_ms - 4000U) / 1000.0f, fm.hover_ref_us, st.max_drop_air);
}

static void test_link_lost_in_flight(int verbose)
{
    printf("== Mat link khi dang giu 1 m (hover that 1420, khac gia tri doan)\n");
    reset_world(1420.0f);
    Cmd idle = {"ground", 0, 0, 1}, up = {"takeoff", 100, 0, 1}, hold = {"hold", 0, 0, 1},
        climb = {"climb", 60, 0, 1}, lost = {"lost", 0, 1, 1};
    run(&idle, 3000, 0);
    run(&up, 1500, 0);
    run(&hold, 6000, 0);
    run(&climb, 1500, 0);
    run(&hold, 6000, 0);
    float z0 = pl.z;
    run(&lost, 20000, verbose);
    CHECK(z0 > 0.7f, "chua len du cao truoc khi mat link: %.2f", z0);
    CHECK(fm.state == FM_DISARMED && fm.exit_reason == ALT_EXIT_FAILSAFE_LANDED,
          "fs=%d exit=%u", fm.state, fm.exit_reason);
    CHECK(!st.landed_in_air, "cham dat gia tren khong");
    CHECK(st.max_drop_air <= 501.0f, "ga giam %.0f us/s khi dang bay", st.max_drop_air);
    printf("   z truoc khi mat link=%.2f m, max drop tren khong=%.0f us/s\n", z0, st.max_drop_air);
}

static void test_bench_no_props(int verbose)
{
    printf("== Bench KHONG canh: phai het gio cat canh va ha ga tu tu\n");
    reset_world(0.0f);
    Cmd idle = {"ground", 0, 0, 1}, up = {"bench", 100, 0, 1}, hold = {"bench", 0, 0, 1};
    run(&idle, 3000, 0);
    run(&up, 1500, verbose);
    float max_thr = 0.0f, prev = fm.throttle_us, max_step_down = 0.0f;
    for (int i = 0; i < 6000; ++i)
    {
        run(&hold, 2, 0);
        if (fm.throttle_us > max_thr)
            max_thr = fm.throttle_us;
        if (fm.state != FM_DISARMED && prev - fm.throttle_us > max_step_down)
            max_step_down = prev - fm.throttle_us;
        prev = fm.throttle_us;
    }
    CHECK(fm.state == FM_DISARMED && fm.exit_reason == ALT_EXIT_TAKEOFF_FAIL,
          "fs=%d exit=%u", fm.state, fm.exit_reason);
    CHECK(max_thr <= 1480.5f, "vuot tran cat canh: %.1f", max_thr);
    CHECK(max_step_down <= 0.41f, "buoc giam ga %.2f us/chu ky", max_step_down);
    CHECK(fm.fault_latched, "phai chot loi, can DUNG -> KICH HOAT LAI");
    printf("   ga cao nhat=%.1f us, buoc giam lon nhat=%.2f us/2ms\n", max_thr, max_step_down);
}

static void test_baro_fault_in_flight(int verbose)
{
    printf("== Baro chet khi dang giu 0.5 m\n");
    reset_world(1405.0f);
    Cmd idle = {"ground", 0, 0, 1}, up = {"takeoff", 100, 0, 1}, hold = {"hold", 0, 0, 1};
    run(&idle, 3000, 0);
    run(&up, 1500, 0);
    run(&hold, 8000, 0);
    pl.baro_dead = 1;
    run(&hold, 15000, verbose);
    CHECK(fm.exit_reason == ALT_EXIT_EMERG_LANDED, "exit=%u", fm.exit_reason);
    CHECK(st.max_drop_air <= 501.0f, "ga giam %.0f us/s khi dang bay", st.max_drop_air);
    printf("   fs=%d, z cuoi=%.2f, max drop tren khong=%.0f us/s\n", fm.state, pl.z, st.max_drop_air);
}

static void test_stop_is_immediate(void)
{
    printf("== DUNG (mode 0) cat ngay\n");
    reset_world(1405.0f);
    Cmd idle = {"ground", 0, 0, 1}, up = {"takeoff", 100, 0, 1}, hold = {"hold", 0, 0, 1},
        stop = {"stop", 0, 0, 0};
    run(&idle, 3000, 0);
    run(&up, 1500, 0);
    run(&hold, 6000, 0);
    run(&stop, 2, 0);
    CHECK(fm.throttle_us == 1000.0f && fm.exit_reason == ALT_EXIT_STOPPED,
          "thr=%.1f exit=%u", fm.throttle_us, fm.exit_reason);
}

static void test_ground_abort(void)
{
    printf("== Huy cat canh bang XUONG khi dang spool-up\n");
    reset_world(1405.0f);
    Cmd idle = {"ground", 0, 0, 1}, up = {"takeoff", 100, 0, 1}, down = {"down", -100, 0, 1};
    run(&idle, 3000, 0);
    run(&up, 400, 0);
    CHECK(fm.state == FM_SPOOLUP, "fs=%d", fm.state);
    run(&down, 3000, 0);
    CHECK(fm.state == FM_DISARMED && fm.exit_reason == ALT_EXIT_LANDED && !fm.fault_latched,
          "fs=%d exit=%u latch=%u", fm.state, fm.exit_reason, fm.fault_latched);
}

int main(int argc, char **argv)
{
    (void)argv;
    int verbose = argc > 1;
    srand(1234);
    test_takeoff_hold_land(verbose);
    test_link_lost_in_flight(verbose);
    test_bench_no_props(verbose);
    test_baro_fault_in_flight(verbose);
    test_stop_is_immediate();
    test_ground_abort();
    if (failures)
    {
        printf("%d FAILURE(S)\n", failures);
        return 1;
    }
    printf("ALL FLIGHT MODE TESTS PASSED\n");
    return 0;
}
