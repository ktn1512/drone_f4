# Host regression checks

Run from the repository root in PowerShell:

```powershell
$testExe = Join-Path $env:TEMP 'drone_f4_test_pitch_control.exe'
& 'C:\msys64\ucrt64\bin\gcc.exe' -std=c11 -Wall -Wextra -Werror -include stddef.h -ICore/Inc tests/test_pitch_control.c Core/Src/pid.c Core/Src/angle_controller.c Core/Src/rate_controller.c Core/Src/mixer.c -lm -o $testExe
if ($LASTEXITCODE -ne 0) { throw 'Host test compilation failed' }
& $testExe
if ($LASTEXITCODE -ne 0) { throw 'Pitch control regression failed' }
```

`-include stddef.h` provides `NULL` to the existing mixer source when building
against the host C library, without changing firmware includes.

The harness exercises controller/mixer behavior using the firmware defaults:
opposing pitch correction, no angle-history rate request after returning to
level, effective bounded rate I, reset at minimum throttle, damping from gyro
rate feedback with default D disabled, invalid timing reset, and first-sample
and setpoint-step behavior when a generic PID explicitly enables D.

These are software regression checks. They do not verify IMU mounting, motor
wiring, ESC response, PWM timing on hardware, thrust, or flight stability.

For the Mahony attitude estimator:

```powershell
$mahonyTestExe = Join-Path $env:TEMP 'drone_f4_test_mahony.exe'
& 'C:\msys64\ucrt64\bin\gcc.exe' -std=c11 -Wall -Wextra -Werror -ICore/Inc tests/test_mahony.c Core/Src/mahony.c -lm -o $mahonyTestExe
if ($LASTEXITCODE -ne 0) { throw 'Mahony host test compilation failed' }
& $mahonyTestExe
if ($LASTEXITCODE -ne 0) { throw 'Mahony regression failed' }
```

These tests check real stationary roll/pitch initialization and convergence
(including -11 degrees), preservation of physical tilt, gyro propagation when
acceleration is unavailable or rejected, acceleration confidence blending and
recovery, disabled-integral clearing, enabled-integral limits and missing-accel
behavior, invalid input handling, and unit quaternion preservation.
Startup and static convergence tests use the current firmware proportional
gain. Transient confidence tests set a local test gain of 2.0 for repeatable
timing expectations; they do not change the firmware default.

`accel_norm_g` reports acceleration magnitude before normalization, or zero for
invalid/tiny samples. `accel_weight` reports confidence: full weight within
0.1 g of 1 g, linearly decreasing to zero at 0.2 g deviation. These thresholds
are heuristic and require evaluation against actual IMU logs. Magnitude gating
cannot detect an incorrect acceleration direction whose magnitude stays near
1 g, so passing these checks does not establish a hardware vibration cure.
Mahony integral feedback defaults to disabled; if deliberately enabled, each
axis is bounded to 5 degrees/s in radian/s units. This integral is separate
from the flight controller PID integral.

