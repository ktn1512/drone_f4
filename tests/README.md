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


## Flight mode (truc dung AUTO) va giao thuc LoRa v2

`test_flight_mode.c` chay `flight_mode.c` + `altitude_hold.c` that voi mo hinh
truc dung don gian (ga treo 1405/1420 us, baro nhieu 3 cm) va kiem tra:
khong giam ga nhanh hon 500 us/s khi drone con tren khong, khong phat hien
cham dat gia, cat canh/ha canh/mat link/baro loi/bench khong canh.

```powershell
$fmTestExe = Join-Path $env:TEMP 'drone_f4_test_flight_mode.exe'
& 'C:\msys64\ucrt64\bin\gcc.exe' -std=c11 -Wall -Wextra -Werror -ICore/Inc tests/test_flight_mode.c Core/Src/flight_mode.c Core/Src/altitude_hold.c -lm -o $fmTestExe
& $fmTestExe          # them 1 tham so bat ky de in quy dao: & $fmTestExe v
```

`test_drone_link.c` bien dich `drone_link.c` that voi HAL/E220/GPS stub
(`tests/host_stubs`) va kiem tra chu ky tra loi S,S,G,S,M, checksum, do dai
goi xau nhat va parse lai bang dung chuoi `sscanf` cua `esp32_drone_web.ino`.

```powershell
$dlTestExe = Join-Path $env:TEMP 'drone_f4_test_drone_link.exe'
& 'C:\msys64\ucrt64\bin\gcc.exe' -std=c11 -Wall -Wextra -Werror -Itests/host_stubs -ICore/Inc tests/test_drone_link.c Core/Src/drone_link.c Core/Src/pid.c -lm -o $dlTestExe
& $dlTestExe
```

Mo hinh vat ly la GIA DINH de kiem tra logic, khong thay the thu nghiem that
(co canh, buoc day).
