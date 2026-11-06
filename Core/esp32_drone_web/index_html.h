#pragma once

static const char INDEX_HTML[] PROGMEM = R"WEB(
<!doctype html>
<html lang="vi"><head><meta charset="utf-8"/>
<meta name="viewport" content="width=device-width,initial-scale=1,user-scalable=no"/>
<title>Drone Control</title>
<style>
:root{font-family:system-ui,-apple-system,Segoe UI,Arial,sans-serif;background:#0b1018;color:#e7eef8;color-scheme:dark;--panel:#151e2b;--line:#2b3b4f;--muted:#9aaac0;--accent:#4aa6fa;--red:#ee5969;--green:#76d9b3}
*{box-sizing:border-box}
body{margin:0 auto;padding:16px 14px 50px;max-width:900px;line-height:1.45;user-select:none;-webkit-user-select:none;overscroll-behavior:none}
h2{font-size:15px;margin:0 0 10px}h3{font-size:12px;color:var(--muted);font-weight:650;margin:0 0 8px;text-align:center}
header{display:flex;justify-content:space-between;align-items:center;gap:10px;flex-wrap:wrap;margin-bottom:12px}
h1{margin:0;font-size:22px}.tiny{font-size:11px;color:var(--muted);letter-spacing:.08em;text-transform:uppercase}
.pill{display:inline-flex;align-items:center;border:1px solid var(--line);border-radius:999px;padding:6px 11px;gap:7px;font-size:12px;color:var(--muted)}
.dot{width:8px;height:8px;border-radius:50%;background:#667489;display:inline-block}.dot.ok{background:var(--green)}
button{font:inherit;font-weight:650;border:1px solid transparent;cursor:pointer;background:#33465f;color:#fff;border-radius:10px;padding:12px 15px;min-height:48px;touch-action:none}
button:disabled{opacity:.3;cursor:not-allowed}
button.primary{background:var(--accent);color:#06121c}
button.danger{background:#c53649;border-color:#ef6c79;font-size:16px;padding:14px 22px}
button.hold{background:#244b71;border-color:#3974a9}button.hold.pressed{background:#317eb8}
.banner{display:flex;gap:12px;align-items:center;justify-content:space-between;flex-wrap:wrap;background:#4a1d27;border:1px solid #ef6c79;border-radius:12px;padding:12px 14px;margin-bottom:12px}
.banner[hidden]{display:none}
.top{display:flex;justify-content:space-between;align-items:center;gap:12px;padding:16px;border:1px solid var(--line);border-radius:16px;background:linear-gradient(135deg,#1a2637,#111a27)}
.big{font-size:38px;font-weight:780;font-variant-numeric:tabular-nums;letter-spacing:-.03em}
.pads{display:flex;justify-content:space-around;gap:10px;margin:16px 0 10px}
.stick{position:relative;width:min(42vw,230px);aspect-ratio:1;border-radius:50%;border:1px solid var(--line);background:radial-gradient(circle,#13202f,#0c1522);touch-action:none;margin:0 auto}
.stick::before,.stick::after{content:"";position:absolute;background:#243449}
.stick::before{left:50%;top:8%;bottom:8%;width:1px}.stick::after{top:50%;left:8%;right:8%;height:1px}
.knob{position:absolute;width:38%;height:38%;left:31%;top:31%;border-radius:50%;background:var(--accent);box-shadow:0 2px 10px #0008;pointer-events:none}
.row{display:grid;grid-template-columns:2fr 1fr 1fr;gap:10px}
.msg{min-height:22px;font-size:13px;margin:10px 0;color:var(--muted)}.msg.err{color:#ff99a6}
.grid{display:grid;grid-template-columns:1fr 1fr;gap:12px;margin-top:8px}
.panel{border:1px solid var(--line);border-radius:14px;background:var(--panel);padding:14px;min-width:0}.full{grid-column:1/-1}
.mg{display:grid;grid-template-columns:repeat(2,minmax(0,1fr));gap:8px}
.metric{padding:10px;background:#0c1522;border-radius:10px;min-width:0}.metric .label{font-size:11px;color:var(--muted)}
.val{display:block;font-size:16px;font-weight:700;margin-top:3px;overflow-wrap:anywhere;font-variant-numeric:tabular-nums}
.raw{font:12px/1.4 ui-monospace,Consolas,monospace;white-space:pre-wrap;overflow-wrap:anywhere;background:#0a1220;padding:8px;border-radius:8px;max-height:70px;overflow:auto}
a{color:#88c7ff;font-size:13px}a[hidden]{display:none}
.disabled{opacity:.35;pointer-events:none}
@media(max-width:640px){.grid{grid-template-columns:1fr}.row{grid-template-columns:1fr 1fr}.row #takeoff{grid-column:1/-1}}
</style></head>
<body>
<header>
  <div><div class="tiny">ESP32 · LoRa E220 · STM32F401</div><h1>Drone Control</h1></div>
  <span class="pill"><span id="linkDot" class="dot"></span><span id="linkLabel">Cho telemetry STM32</span></span>
</header>

<div id="banner" class="banner" hidden>
  <span id="bannerText">ĐÃ DỪNG</span>
  <button id="resume" class="primary">KÍCH HOẠT LẠI</button>
</div>

<section class="top">
  <div>
    <div class="tiny">Độ cao tương đối (DPS310)</div>
    <div class="big"><span id="height">--</span></div>
    <span id="holdState" class="pill">--</span>
  </div>
  <button id="stop" class="danger">DỪNG KHẨN CẤP</button>
</section>

<section id="controls">
  <div class="pads">
    <div><h3>ĐỘ CAO ↕ · YAW ↔</h3><div class="stick" id="stickL"><div class="knob"></div></div></div>
    <div><h3>PITCH ↕ · ROLL ↔</h3><div class="stick" id="stickR"><div class="knob"></div></div></div>
  </div>
  <div class="row">
    <button id="takeoff" class="primary">CẤT CÁNH (tự giữ LÊN đến khi ALT_HOLD)</button>
    <button id="up" class="hold">▲ LÊN</button>
    <button id="down" class="hold">▼ XUỐNG</button>
  </div>
</section>
<div id="note" class="msg">Thả cần/nút = giữ độ cao hiện tại. Thử không gắn cánh trước.</div>
<p class="msg" id="cmdLine">--</p>

<section class="grid">
  <div class="panel full">
    <h2>Trạng thái STM32</h2>
    <div class="mg">
      <div class="metric"><div class="label">Roll / Pitch / Yaw</div><strong id="angles" class="val" style="font-size:14px">--</strong></div>
      <div class="metric"><div class="label">Motor M1–M4 (µs)</div><strong id="motors" class="val" style="font-size:14px">--</strong></div>
    </div>
  </div>
  <div class="panel">
    <h2>GPS</h2>
    <div class="mg">
      <div class="metric"><div class="label">Fix / vệ tinh</div><strong id="gpsFix" class="val">--</strong></div>
      <div class="metric"><div class="label">Tốc độ / course</div><strong id="gpsMotion" class="val" style="font-size:14px">--</strong></div>
    </div>
    <div class="metric" style="margin-top:8px"><div class="label">Vĩ độ / kinh độ</div><strong id="gpsCoords" class="val" style="font-size:14px">--</strong></div>
    <a id="gpsMap" target="_blank" rel="noopener noreferrer" hidden>Xem trên OpenStreetMap</a>
  </div>
  <div class="panel">
    <h2>LoRa E220</h2>
    <div class="mg">
      <div class="metric"><div class="label">TX / RX</div><strong id="txrx" class="val">0 / 0</strong></div>
      <div class="metric"><div class="label">S hợp lệ / lỗi</div><strong id="goodbad" class="val">0 / 0</strong></div>
      <div class="metric"><div class="label">Tuổi status</div><strong id="statusAge" class="val">--</strong></div>
      <div class="metric"><div class="label">AUX / lỗi RX</div><strong id="uartErrors" class="val">--</strong></div>
    </div>
    <h3 style="margin-top:10px;text-align:left">Gói gửi gần nhất</h3><div id="lastTx" class="raw">--</div>
    <h3 style="margin-top:8px;text-align:left">Gói nhận gần nhất</h3><div id="lastRx" class="raw">--</div>
  </div>
</section>

<script>
// Neu huong nghieng/yaw bi nguoc so voi chieu lap IMU, doi true/false o day.
const INVERT={roll:false,pitch:false,yaw:false};
const LIM={roll:12,pitch:12,yaw:60};          // khop gioi han ESP32
const TAKEOFF_MAX_MS=15000;

const el=id=>document.getElementById(id);
let st=null;                     // /api/state moi nhat
let L={x:0,y:0}, R={x:0,y:0};    // joystick trai/phai, -1..1 (y>0 la keo xuong)
let btn=0, takeoff=false, takeoffT=0;

const note=(s,err=false)=>{el('note').textContent=s;el('note').className=err?'msg err':'msg';};
const dz=(v,d=.12)=>Math.abs(v)<d?0:(v-Math.sign(v)*d)/(1-d);
const sg=f=>f?-1:1;

// ---- Gop moi nguon dieu khien thanh 1 trang thai ----
function compose(){
  if(document.hidden||!st||st.stopped)return{climb:0,roll:0,pitch:0,yaw:0};
  let climb=Math.round(-dz(L.y)*100);
  if(btn)climb=btn;
  const active=!!(st.status&&st.status.altActive);
  if(takeoff){
    if(active||climb<0||Date.now()-takeoffT>TAKEOFF_MAX_MS)takeoff=false;
    else if(climb===0)climb=100;
  }
   // IMU lap xoay 90 do so voi khung:
  //   roll FC  + = ngoc dau len  -> bay TOI can roll AM
  //   pitch FC + = nghieng phai  -> bay PHAI can pitch DUONG
  const fwd = -dz(R.y);    // day can len = +1 (y man hinh huong xuong)
  const right = dz(R.x);   // keo can sang phai = +1
  return{
    climb,
    roll:Math.round(-fwd*LIM.roll*sg(INVERT.roll)),
    pitch:Math.round(right*LIM.pitch*sg(INVERT.pitch)),
    yaw:Math.round(dz(L.x)*LIM.yaw*sg(INVERT.yaw))
  };
}

async function post(url,body={}){
  const ac=new AbortController();const t=setTimeout(()=>ac.abort(),2000);
  try{
    const r=await fetch(url,{method:'POST',signal:ac.signal,
      headers:{'Content-Type':'application/x-www-form-urlencoded'},body:new URLSearchParams(body)});
    const j=await r.json();
    if(!r.ok||!j.ok)throw Error(j.error||('HTTP '+r.status));
    return j;
  }finally{clearTimeout(t);}
}

// Chi 1 request /api/ctrl cung luc; neu co thay doi trong luc cho thi gui lai ban moi nhat.
let inflight=false,dirty=false;
async function send(){
  if(st&&st.stopped)return;
  if(inflight){dirty=true;return;}
  inflight=true;
  try{do{dirty=false;await post('/api/ctrl',compose());}while(dirty);}
  catch(e){note(e.message,true);}
  finally{inflight=false;}
}
setInterval(send,250);   // heartbeat: ESP32 se ve 0 neu im >800 ms

// ---- Joystick ao ----
function makeStick(root,onChange){
  const knob=root.querySelector('.knob');let id=null;
  const show=(x,y)=>{const r=root.clientWidth*.31;knob.style.transform=`translate(${x*r}px,${y*r}px)`;};
  const set=(x,y)=>{show(x,y);onChange(x,y);send();};
  const move=e=>{
    const b=root.getBoundingClientRect(),r=b.width*.31;
    let x=(e.clientX-(b.left+b.width/2))/r,y=(e.clientY-(b.top+b.height/2))/r;
    const m=Math.hypot(x,y);if(m>1){x/=m;y/=m;}
    set(x,y);
  };
  root.addEventListener('pointerdown',e=>{e.preventDefault();id=e.pointerId;try{root.setPointerCapture(id);}catch(_){}move(e);});
  root.addEventListener('pointermove',e=>{if(e.pointerId===id)move(e);});
  const end=e=>{if(e.pointerId===id||e.type==='lostpointercapture'){id=null;set(0,0);}};
  for(const n of['pointerup','pointercancel','lostpointercapture'])root.addEventListener(n,end);
}
makeStick(el('stickL'),(x,y)=>{L={x,y};});
makeStick(el('stickR'),(x,y)=>{R={x,y};});

// ---- Nut LEN / XUONG: giu de di chuyen, tha de giu do cao ----
function holdBtn(b,v){
  b.addEventListener('pointerdown',e=>{
    e.preventDefault();btn=v;b.classList.add('pressed');
    try{b.setPointerCapture(e.pointerId);}catch(_){}
    send();
  });
  const off=()=>{if(btn===v){btn=0;b.classList.remove('pressed');send();}};
  for(const n of['pointerup','pointercancel','lostpointercapture'])b.addEventListener(n,off);
}
holdBtn(el('up'),100);
holdBtn(el('down'),-100);

el('takeoff').onclick=()=>{
  if(takeoff){takeoff=false;}else{takeoff=true;takeoffT=Date.now();}
  send();
};

el('stop').onclick=async()=>{
  takeoff=false;btn=0;L={x:0,y:0};R={x:0,y:0};
  try{await post('/api/stop');note('Đã gửi DỪNG. Chờ STM32 xác nhận (thr=1000).');}
  catch(e){note('Chưa xác nhận dừng: '+e.message,true);}
};
el('resume').onclick=async()=>{
  try{await post('/api/resume');note('Đã kích hoạt lại. Cất cánh bằng nút CẤT CÁNH.');}
  catch(e){note(e.message,true);}
};

// ---- Hien thi trang thai ----
function render(d){
  const s=d.status||null,radio=d.radio||{},linked=!!d.link,active=!!(s&&s.altActive);
  el('linkDot').className=linked?'dot ok':'dot';
  el('linkLabel').textContent=linked?'Đã nhận status STM32':'Mất/chưa có telemetry STM32';
  el('banner').hidden=!d.stopped;
  if(d.stopped)el('bannerText').textContent='ĐÃ DỪNG · '+(d.stopReason||'');
  el('controls').classList.toggle('disabled',!!d.stopped);
  if(active&&takeoff)takeoff=false;
  el('height').textContent=linked&&s?s.altitudeM.toFixed(2)+' m':'--';
  const exitText=s&&s.altExit===1?'Đã hạ cánh':(s&&s.altExitText)||'';
  el('holdState').textContent=!linked?'Không có telemetry':active?'ALT_HOLD ĐANG GIỮ ĐỘ CAO':'Trên mặt đất / chưa cất cánh'+(exitText?' · '+exitText:'')+(s?' · ga '+s.throttle+' µs':'');
  el('takeoff').textContent=takeoff?'HUỶ CẤT CÁNH':'CẤT CÁNH (tự giữ LÊN đến khi ALT_HOLD)';
  el('takeoff').disabled=!linked||active;
  el('up').disabled=!linked;
  el('down').disabled=!linked||!active;
  el('angles').textContent=linked&&s?[s.roll,s.pitch,s.yaw].map(x=>Number(x).toFixed(1)+'°').join(' / '):'--';
  el('motors').textContent=linked&&s?s.motors.join(' / '):'--';
  el('cmdLine').textContent='Lệnh gửi: climb '+d.climb+'% · roll '+d.rollCommand+'° · pitch '+d.pitchCommand+'° · yaw '+d.yawRateCommand+'°/s';
  el('gpsFix').textContent=linked&&s?(s.gpsFix?'Có · '+s.gpsSatellites+' vệ tinh':'Chưa FIX'):'--';
  el('gpsMotion').textContent=linked&&s&&s.gpsFix?s.gpsSpeedKmh.toFixed(1)+' km/h / '+s.gpsCourseDeg.toFixed(1)+'°':'--';
  el('gpsCoords').textContent=linked&&s&&s.gpsFix?s.gpsLat.toFixed(6)+', '+s.gpsLon.toFixed(6):'--';
  const map=el('gpsMap');map.hidden=!(linked&&s&&s.gpsFix);
  if(!map.hidden)map.href='https://www.openstreetmap.org/?mlat='+s.gpsLat+'&mlon='+s.gpsLon+'#map=17/'+s.gpsLat+'/'+s.gpsLon;
  el('txrx').textContent=(radio.txCount||0)+' / '+(radio.rxCount||0);
  el('goodbad').textContent=(d.statusValidCount||0)+' / '+(d.statusInvalidCount||0);
  el('statusAge').textContent=d.statusAgeMs===null?'--':(d.statusAgeMs/1000).toFixed(1)+' s';
  el('uartErrors').textContent=(radio.auxReady?'HIGH':'LOW')+' / '+(radio.rxErrors||0);
  el('lastTx').textContent=radio.lastTx||'--';
  el('lastRx').textContent=radio.lastRx||'--';
}

async function refresh(){
  try{
    const r=await fetch('/api/state',{cache:'no-store'});
    if(!r.ok)throw Error('HTTP '+r.status);
    st=await r.json();render(st);
  }catch(e){el('linkDot').className='dot';el('linkLabel').textContent='Không đọc được ESP32';}
  setTimeout(refresh,500);
}
refresh();
</script>
</body></html>
)WEB";