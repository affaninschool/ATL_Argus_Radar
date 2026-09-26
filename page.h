#ifndef ARGUS_PAGE_H
#define ARGUS_PAGE_H

const char ARGUS_PAGE[] PROGMEM = R"=====(
<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="utf-8">
<meta name="viewport" content="width=device-width,initial-scale=1,viewport-fit=cover">
<meta name="theme-color" content="#04090c">
<title>ARGUS · Smart Radar</title>
<style>
:root{
  --bg:#04090c;--ink:#d8f4ec;--muted:#5f8a8d;--dim:#223f43;
  --green:#00ffa3;--cyan:#00c2ff;--red:#ff3b5c;--amber:#ffc857;--violet:#8b5cff;
  --line:rgba(0,255,163,.14);
  --mono:ui-monospace,'SFMono-Regular',Consolas,'Roboto Mono',Menlo,monospace;
  --display:'Segoe UI',system-ui,-apple-system,'Helvetica Neue',Arial,sans-serif;
  --radar-aspect:0.52;
}
*{box-sizing:border-box;-webkit-tap-highlight-color:transparent}
html,body{margin:0;padding:0}
body{
  min-height:100vh;background:var(--bg);color:var(--ink);font-family:var(--mono);
  padding:12px 14px 22px;overflow-x:hidden;-webkit-font-smoothing:antialiased;position:relative;
}
#bg{position:fixed;inset:0;width:100%;height:100%;z-index:0;pointer-events:none;opacity:.85}
.aurora{
  position:fixed;inset:-20%;z-index:0;pointer-events:none;
  background:
    radial-gradient(38% 30% at 18% 12%, rgba(0,255,163,.10), transparent 70%),
    radial-gradient(34% 28% at 84% 22%, rgba(0,194,255,.09), transparent 70%),
    radial-gradient(40% 34% at 62% 92%, rgba(139,92,255,.10), transparent 72%),
    radial-gradient(30% 24% at 30% 78%, rgba(255,59,92,.05), transparent 70%);
  filter:blur(28px);animation:drift 26s ease-in-out infinite alternate;
}
@keyframes drift{0%{transform:translate3d(-2%,-1%,0) scale(1)}100%{transform:translate3d(3%,2%,0) scale(1.09)}}
body::before{
  content:'';position:fixed;inset:0;z-index:2;pointer-events:none;opacity:.035;
  background-image:url("data:image/svg+xml,%3Csvg xmlns='http://www.w3.org/2000/svg' width='140' height='140'%3E%3Cfilter id='n'%3E%3CfeTurbulence type='fractalNoise' baseFrequency='.85' numOctaves='3'/%3E%3C/filter%3E%3Crect width='140' height='140' filter='url(%23n)'/%3E%3C/svg%3E");
}
body::after{
  content:'';position:fixed;inset:0;z-index:3;pointer-events:none;opacity:.35;
  background:repeating-linear-gradient(to bottom,rgba(0,0,0,0) 0px,rgba(0,0,0,0) 2px,rgba(0,0,0,.16) 3px,rgba(0,0,0,0) 4px);
  mix-blend-mode:multiply;
}
.vignette{position:fixed;inset:0;z-index:2;pointer-events:none;background:radial-gradient(120% 100% at 50% 45%, transparent 45%, rgba(0,0,0,.62) 100%)}
.shell{position:relative;z-index:4;max-width:1500px;margin:0 auto}
.card{
  position:relative;background:linear-gradient(180deg, rgba(9,22,26,.86) 0%, rgba(5,13,16,.9) 100%);
  border:1px solid var(--line);border-radius:16px;padding:14px;
  backdrop-filter:blur(9px);-webkit-backdrop-filter:blur(9px);
  box-shadow:0 1px 0 rgba(255,255,255,.03) inset,0 18px 44px -26px rgba(0,0,0,.95),0 0 0 1px rgba(0,255,163,.02);
  overflow:hidden;
}
.card::after{
  content:'';position:absolute;inset:7px;pointer-events:none;border-radius:10px;opacity:.55;
  background:
    linear-gradient(var(--green),var(--green)) left  top   /14px 1px no-repeat,
    linear-gradient(var(--green),var(--green)) left  top   /1px 14px no-repeat,
    linear-gradient(var(--green),var(--green)) right top   /14px 1px no-repeat,
    linear-gradient(var(--green),var(--green)) right top   /1px 14px no-repeat,
    linear-gradient(var(--green),var(--green)) left  bottom/14px 1px no-repeat,
    linear-gradient(var(--green),var(--green)) left  bottom/1px 14px no-repeat,
    linear-gradient(var(--green),var(--green)) right bottom/14px 1px no-repeat,
    linear-gradient(var(--green),var(--green)) right bottom/1px 14px no-repeat;
}
.card h2{margin:0 0 11px;font-size:9.5px;letter-spacing:3px;color:var(--muted);font-weight:600;text-transform:uppercase;display:flex;align-items:center;gap:9px}
.card h2::after{content:'';flex:1;height:1px;background:linear-gradient(90deg,var(--line),transparent)}
.topbar{
  display:flex;align-items:center;justify-content:space-between;gap:16px;flex-wrap:wrap;
  padding:13px 20px;margin-bottom:12px;border-radius:18px;
  background:linear-gradient(120deg, rgba(0,255,163,.055), rgba(0,194,255,.03) 45%, rgba(139,92,255,.045));
  border:1px solid rgba(0,255,163,.18);backdrop-filter:blur(10px);position:relative;overflow:hidden;
}
.topbar::before{content:'';position:absolute;top:0;left:-40%;width:40%;height:100%;background:linear-gradient(90deg,transparent,rgba(0,255,163,.09),transparent);animation:sheen 7s linear infinite}
@keyframes sheen{0%{left:-45%}100%{left:115%}}
.brand{display:flex;align-items:center;gap:15px;position:relative;z-index:1}
.sigil{width:42px;height:42px;flex:none;border-radius:12px;display:grid;place-items:center;background:radial-gradient(circle at 30% 25%, rgba(0,255,163,.28), rgba(0,255,163,.04));border:1px solid rgba(0,255,163,.4);box-shadow:0 0 24px rgba(0,255,163,.26), inset 0 0 14px rgba(0,255,163,.12);position:relative}
.sigil i{width:10px;height:10px;border-radius:50%;background:var(--green);display:block;box-shadow:0 0 12px var(--green);animation:beat 2s ease-in-out infinite}
.sigil::after{content:'';position:absolute;inset:-4px;border-radius:15px;border:1px solid rgba(0,255,163,.22);animation:halo 2.6s ease-out infinite}
@keyframes halo{0%{transform:scale(.9);opacity:.8}100%{transform:scale(1.25);opacity:0}}
@keyframes beat{0%,100%{transform:scale(1);opacity:1}50%{transform:scale(.6);opacity:.55}}
.brand h1{margin:0;font-family:var(--display);font-size:26px;font-weight:900;letter-spacing:.4em;text-transform:uppercase;line-height:1;background:linear-gradient(92deg,#ffffff 0%,var(--green) 42%,var(--cyan) 100%);-webkit-background-clip:text;background-clip:text;color:transparent;filter:drop-shadow(0 0 18px rgba(0,255,163,.48))}
.brand small{display:block;margin-top:7px;font-size:9px;letter-spacing:3px;color:var(--muted);text-transform:uppercase}
.brand small b{color:var(--green);font-weight:600}
.netinfo{display:flex;gap:8px;flex-wrap:wrap;position:relative;z-index:1}
.chip{border:1px solid var(--line);border-radius:999px;padding:7px 13px;font-size:10px;letter-spacing:1.4px;color:var(--muted);background:rgba(0,255,163,.035);white-space:nowrap}
.chip b{color:var(--green);font-weight:600;margin-left:4px}
.chip.warn{border-color:rgba(255,200,87,.32);background:rgba(255,200,87,.06)}
.chip.warn b{color:var(--amber)}
.chip.violet{border-color:rgba(139,92,255,.3);background:rgba(139,92,255,.06)}
.chip.violet b{color:#b39dff}
.grid{display:grid;grid-template-columns:minmax(0, 1fr) 330px;gap:12px;align-items:start}
@media(max-width:1050px){.grid{grid-template-columns:1fr}}
.side{display:flex;flex-direction:column;gap:12px}
.radar-card{padding:12px}
.radar-wrap{
  position:relative;width:100%;aspect-ratio:1 / var(--radar-aspect);border-radius:13px;overflow:hidden;
  border:1px solid rgba(0,255,163,.16);
  background:radial-gradient(115% 85% at 50% 104%, rgba(0,255,163,.13) 0%, transparent 58%),radial-gradient(85% 70% at 50% 100%, #07201e 0%, #030b0b 62%, #010506 100%);
  box-shadow:inset 0 0 80px rgba(0,255,163,.07);
}
#radar{position:absolute;inset:0;width:100%;height:100%;display:block}
.badge{position:absolute;top:12px;left:14px;z-index:2;font-size:8.5px;letter-spacing:2.4px;color:var(--amber);border:1px solid rgba(255,200,87,.42);background:rgba(255,200,87,.09);padding:5px 11px;border-radius:7px;box-shadow:0 0 18px rgba(255,200,87,.14);text-transform:uppercase}
.badge.live{color:var(--green);border-color:rgba(0,255,163,.45);background:rgba(0,255,163,.09);box-shadow:0 0 18px rgba(0,255,163,.2)}
.badge.live::before{content:'';display:inline-block;width:6px;height:6px;border-radius:50%;background:var(--green);margin-right:7px;vertical-align:1px;box-shadow:0 0 9px var(--green);animation:beat 1.6s ease-in-out infinite}
.range-tag{position:absolute;top:12px;right:14px;z-index:2;font-size:8.5px;letter-spacing:2.2px;color:var(--muted);border:1px solid var(--line);border-radius:7px;padding:5px 11px;background:rgba(0,0,0,.32)}
.range-tag b{color:var(--green)}
.readout{text-align:center;overflow:hidden;position:relative}
.readout::before{content:'';position:absolute;left:50%;top:-40%;width:130%;height:150%;transform:translateX(-50%);background:radial-gradient(50% 50% at 50% 50%, rgba(0,255,163,.09), transparent 70%);pointer-events:none;transition:background .2s}
.readout.alert::before{background:radial-gradient(50% 50% at 50% 50%, rgba(255,59,92,.13), transparent 70%)}
.readout .big{position:relative;font-family:var(--display);font-size:54px;line-height:.95;font-weight:800;letter-spacing:-.02em;color:var(--green);text-shadow:0 0 30px rgba(0,255,163,.5), 0 0 70px rgba(0,255,163,.18);transition:color .16s,text-shadow .16s;font-variant-numeric:tabular-nums}
.readout .big.alert{color:var(--red);text-shadow:0 0 30px rgba(255,59,92,.62), 0 0 70px rgba(255,59,92,.22);animation:jolt .34s ease}
@keyframes jolt{0%,100%{transform:none}30%{transform:translateX(-1.5px)}60%{transform:translateX(1.5px)}}
.readout .unit{font-family:var(--mono);font-size:13px;color:var(--muted);margin-left:5px;letter-spacing:2.5px}
.readout .sub{position:relative;font-size:9.5px;color:var(--muted);letter-spacing:3.4px;margin-top:10px;text-transform:uppercase}
.statusbar{position:relative;margin-top:13px;padding:10px;border-radius:10px;font-size:10.5px;letter-spacing:3.2px;font-weight:700;text-transform:uppercase;border:1px solid rgba(0,255,163,.32);color:var(--green);background:rgba(0,255,163,.07);transition:all .16s}
.statusbar.alert{border-color:rgba(255,59,92,.6);color:var(--red);background:rgba(255,59,92,.1);box-shadow:0 0 26px rgba(255,59,92,.2)}
.statusbar.paused{border-color:rgba(255,200,87,.45);color:var(--amber);background:rgba(255,200,87,.08)}
.leds{display:flex;gap:10px;justify-content:center;margin-top:13px;position:relative}
.led{flex:1;display:flex;flex-direction:column;align-items:center;gap:8px;padding:11px 4px;border-radius:11px;border:1px solid var(--line);font-size:8.5px;letter-spacing:2px;color:var(--muted);background:rgba(0,0,0,.22);transition:all .16s;text-transform:uppercase}
.led i{width:16px;height:16px;border-radius:50%;display:block;background:#12262b;border:1px solid #1c3a3f;transition:all .16s}
.led.g.on i{background:var(--green);border-color:var(--green);box-shadow:0 0 18px var(--green),0 0 40px rgba(0,255,163,.55)}
.led.r.on i{background:var(--red);border-color:var(--red);box-shadow:0 0 18px var(--red),0 0 40px rgba(255,59,92,.55)}
.led.g.on{color:var(--green);border-color:rgba(0,255,163,.42);background:rgba(0,255,163,.06)}
.led.r.on{color:var(--red);border-color:rgba(255,59,92,.42);background:rgba(255,59,92,.07)}
.stats{display:grid;grid-template-columns:1fr 1fr;gap:9px}
.stat{position:relative;overflow:hidden;background:linear-gradient(160deg,rgba(0,255,163,.055),rgba(0,255,163,.012));border:1px solid var(--line);border-radius:11px;padding:10px 12px}
.stat::before{content:'';position:absolute;left:0;top:0;bottom:0;width:2px;background:linear-gradient(180deg,var(--green),transparent);opacity:.6}
.stat .k{font-size:8.5px;letter-spacing:1.9px;color:var(--muted);margin-bottom:6px;text-transform:uppercase}
.stat .v{font-family:var(--display);font-size:19px;font-weight:800;color:var(--ink);letter-spacing:-.01em;font-variant-numeric:tabular-nums}
.stat .v small{font-family:var(--mono);font-size:9.5px;color:var(--muted);font-weight:400;margin-left:3px}
.ctrl{margin-bottom:15px}
.ctrl:last-of-type{margin-bottom:0}
.ctrl label{display:flex;justify-content:space-between;align-items:baseline;font-size:9px;letter-spacing:2px;color:var(--muted);margin-bottom:9px;text-transform:uppercase}
.ctrl label b{color:var(--green);font-size:11px;letter-spacing:1px}
input[type=range]{-webkit-appearance:none;appearance:none;width:100%;height:3px;border-radius:2px;outline:none;background:linear-gradient(90deg,rgba(0,255,163,.55),rgba(0,255,163,.1))}
input[type=range]::-webkit-slider-thumb{-webkit-appearance:none;width:17px;height:17px;border-radius:50%;background:radial-gradient(circle at 35% 30%,#baffe6,var(--green));cursor:pointer;border:none;box-shadow:0 0 14px rgba(0,255,163,.85),0 0 30px rgba(0,255,163,.35)}
input[type=range]::-moz-range-thumb{width:17px;height:17px;border:none;border-radius:50%;background:radial-gradient(circle at 35% 30%,#baffe6,var(--green));cursor:pointer;box-shadow:0 0 14px rgba(0,255,163,.85),0 0 30px rgba(0,255,163,.35)}
.btns{display:flex;gap:9px;margin-top:16px}
button{flex:1;padding:11px;border-radius:11px;cursor:pointer;font-family:var(--mono);font-size:9.5px;letter-spacing:2.2px;font-weight:700;text-transform:uppercase;background:linear-gradient(180deg,rgba(0,255,163,.11),rgba(0,255,163,.035));color:var(--green);border:1px solid rgba(0,255,163,.32);transition:all .15s}
button:hover{background:linear-gradient(180deg,rgba(0,255,163,.2),rgba(0,255,163,.07));box-shadow:0 0 22px rgba(0,255,163,.24);transform:translateY(-1px)}
button:active{transform:translateY(0) scale(.985)}
button.paused{background:linear-gradient(180deg,rgba(255,200,87,.16),rgba(255,200,87,.05));color:var(--amber);border-color:rgba(255,200,87,.45);box-shadow:0 0 20px rgba(255,200,87,.16)}
button.ghost{background:transparent;color:var(--muted);border-color:var(--dim)}
button.ghost:hover{color:var(--ink);background:rgba(255,255,255,.035);box-shadow:none;border-color:var(--muted)}
.log-list{display:flex;flex-direction:column;gap:6px;max-height:158px;overflow:hidden}
.log-item{display:flex;justify-content:space-between;align-items:center;font-size:10px;padding:8px 11px;border-radius:8px;background:linear-gradient(90deg,rgba(0,255,163,.07),rgba(0,255,163,.015));border-left:2px solid var(--green);animation:slidein .28s cubic-bezier(.2,.9,.3,1)}
.log-item.alert{border-left-color:var(--red);background:linear-gradient(90deg,rgba(255,59,92,.11),rgba(255,59,92,.02))}
.log-item .a{color:var(--muted);letter-spacing:1px}
.log-item .d{color:var(--ink);font-weight:700;font-variant-numeric:tabular-nums}
.log-item.alert .d{color:var(--red)}
@keyframes slidein{from{opacity:0;transform:translateX(-10px)}to{opacity:1;transform:none}}
.empty{font-size:9.5px;color:var(--dim);letter-spacing:2.2px;padding:10px 0;text-align:center}
.graph-card{margin-top:12px}
#graph{width:100%;height:150px;display:block}
.legend{display:flex;gap:18px;font-size:8.5px;letter-spacing:2px;color:var(--muted);margin-top:10px;flex-wrap:wrap;text-transform:uppercase}
.legend span{display:flex;align-items:center;gap:7px}
.legend i{width:16px;height:2px;display:block;border-radius:1px}
footer{text-align:center;font-size:8.5px;letter-spacing:2.4px;color:#264447;margin-top:16px;text-transform:uppercase;position:relative;z-index:4}
footer b{color:var(--green);font-weight:600}
.boot{position:fixed;inset:0;z-index:99;display:grid;place-items:center;background:#03080a;transition:opacity .6s ease, visibility .6s}
.boot.done{opacity:0;visibility:hidden}
.boot-inner{text-align:center}
.boot-ring{width:54px;height:54px;margin:0 auto 18px;border-radius:50%;border:2px solid rgba(0,255,163,.14);border-top-color:var(--green);animation:spin .85s linear infinite;box-shadow:0 0 26px rgba(0,255,163,.28)}
@keyframes spin{to{transform:rotate(360deg)}}
.boot-text{font-size:9.5px;letter-spacing:3.4px;color:var(--green);text-transform:uppercase;animation:blink 1.1s steps(2) infinite}
@keyframes blink{50%{opacity:.35}}
@media(max-width:640px){.brand h1{font-size:20px;letter-spacing:.3em}.readout .big{font-size:46px}.topbar{padding:11px 14px}body{padding:10px 10px 20px}}
</style>
</head>
<body>
<canvas id="bg"></canvas>
<div class="aurora"></div>
<div class="vignette"></div>

<div class="boot" id="boot">
  <div class="boot-inner">
    <div class="boot-ring"></div>
    <div class="boot-text">Initializing Argus Array…</div>
  </div>
</div>

<div class="shell">
  <header class="topbar">
    <div class="brand">
      <div class="sigil"><i></i></div>
      <div>
        <h1>ARGUS</h1>
        <small>Perimeter Awareness Array · ESP8266 <b>MOD</b></small>
      </div>
    </div>
    <div class="netinfo">
      <div class="chip">AP <b>ATL-RADAR</b></div>
      <div class="chip">IP <b>192.168.4.1</b></div>
      <div class="chip warn">RANGE <b>50 CM</b></div>
      <div class="chip violet">CLIENTS <b id="clients">–</b></div>
    </div>
  </header>

  <main class="grid">
    <section class="card radar-card">
      <div class="radar-wrap">
        <canvas id="radar"></canvas>
        <div class="badge live" id="badge">Live Feed</div>
        <div class="range-tag">MAX <b>50 CM</b></div>
      </div>
    </section>

    <aside class="side">
      <div class="card readout" id="readoutCard">
        <div class="big" id="distBig">--<span class="unit">cm</span></div>
        <div class="sub" id="angleSub">Angle 000°</div>
        <div class="statusbar" id="statusBar">● Scanning</div>
        <div class="leds">
          <div class="led g" id="ledG"><i></i>Green</div>
          <div class="led r" id="ledR"><i></i>Red</div>
        </div>
      </div>

      <div class="card">
        <h2>Telemetry</h2>
        <div class="stats">
          <div class="stat"><div class="k">Min Distance</div><div class="v" id="stMin">--<small>cm</small></div></div>
          <div class="stat"><div class="k">Detections</div><div class="v" id="stCount">0</div></div>
          <div class="stat"><div class="k">Sweep Time</div><div class="v" id="stSweep">3.6<small>s</small></div></div>
          <div class="stat"><div class="k">Uptime</div><div class="v" id="stUp">00:00</div></div>
        </div>
      </div>

      <div class="card">
        <h2>Controls</h2>
        <div class="ctrl">
          <label>Alert Threshold <b><span id="thVal">20</span> cm</b></label>
          <input type="range" id="thSlider" min="5" max="50" value="20" step="1">
        </div>
        <div class="ctrl">
          <label>Sweep Speed <b><span id="spVal">Medium</span></b></label>
          <input type="range" id="spSlider" min="1" max="3" value="2" step="1">
        </div>
        <div class="btns">
          <button id="btnScan">Pause Scan</button>
          <button id="btnClear" class="ghost">Clear</button>
        </div>
      </div>

      <div class="card">
        <h2>Detection Log</h2>
        <div class="log-list" id="logList"><div class="empty">Awaiting targets…</div></div>
      </div>
    </aside>
  </main>

  <section class="card graph-card">
    <h2>Distance History · Last 120 Samples</h2>
    <canvas id="graph"></canvas>
    <div class="legend">
      <span><i style="background:linear-gradient(90deg,#00ffa3,#00c2ff)"></i>Distance</span>
      <span><i style="background:#ff3b5c"></i>Alert Threshold</span>
      <span><i style="background:#ffc857"></i>Max Range 50 cm</span>
    </div>
  </section>

  <footer>ARGUS · Live Feed · <b>http://192.168.4.1</b></footer>
</div>

<script>
/* ═══════════ ARGUS client — works live AND offline ═══════════ */
const MAX_RANGE = 50;
const FADE_MS   = 2600;
const HIST_MAX  = 120;
const PAD_SIDE  = 30, PAD_TOP = 26, PAD_BOTTOM = 34;

const S = {
  angle: 0, dir: 1, running: true, threshold: 20,
  step: 3, tickMs: 30,
  blips: [], history: [], detections: 0,
  minDist: null, startTime: Date.now(), lastLog: 0,
  current: { dist: null, detected: false },
  live: false,
  fails: 0
};

/* only used when the ESP is unreachable */
const targets = [
  { a: 38,  d: 17, w: 4,   drift:  0.05 },
  { a: 96,  d: 41, w: 3,   drift: -0.04 },
  { a: 146, d: 26, w: 3.5, drift:  0.03 }
];

const bgc = document.getElementById('bg'), bctx = bgc.getContext('2d');
const radar = document.getElementById('radar'), rctx = radar.getContext('2d');
const graph = document.getElementById('graph'), gctx = graph.getContext('2d');
let BW=0, BH=0, stars=[], DPR = window.devicePixelRatio || 1;
let RW=0, RH=0, GW=0, GH=0, CX=0, CY=0, R=0;

function initStars(){
  const count = Math.min(150, Math.round(BW*BH/15000));
  stars = Array.from({length:count}, function(){
    return {
      x: Math.random()*BW, y: Math.random()*BH,
      r: Math.random()*1.25+0.25, ph: Math.random()*Math.PI*2,
      sp: Math.random()*0.9+0.35, vy: Math.random()*0.09+0.02,
      hue: Math.random()<0.2?'0,194,255':(Math.random()<0.12?'139,92,255':'0,255,163')
    };
  });
}
function drawBG(t){
  bctx.clearRect(0,0,BW,BH);
  for (let i=0; i<stars.length; i++){
    const s = stars[i];
    const tw = 0.35 + 0.65*(0.5 + 0.5*Math.sin(t*0.0011*s.sp + s.ph));
    s.y -= s.vy;
    if (s.y < -4){ s.y = BH+4; s.x = Math.random()*BW; }
    bctx.beginPath(); bctx.arc(s.x,s.y,s.r,0,Math.PI*2);
    bctx.fillStyle = "rgba("+s.hue+","+(tw*0.75)+")"; bctx.fill();
    if (s.r > 1.05){
      bctx.beginPath(); bctx.arc(s.x,s.y,s.r*4.5,0,Math.PI*2);
      bctx.fillStyle = "rgba("+s.hue+","+(tw*0.055)+")"; bctx.fill();
    }
  }
}

function fit(c, ctx){
  const rect = c.getBoundingClientRect();
  c.width  = Math.max(1, Math.round(rect.width  * DPR));
  c.height = Math.max(1, Math.round(rect.height * DPR));
  ctx.setTransform(DPR,0,0,DPR,0,0);
  return { w: rect.width, h: rect.height };
}
function resizeAll(){
  DPR = window.devicePixelRatio || 1;
  bgc.width = Math.round(window.innerWidth*DPR);
  bgc.height= Math.round(window.innerHeight*DPR);
  bctx.setTransform(DPR,0,0,DPR,0,0);
  BW = window.innerWidth; BH = window.innerHeight;
  initStars();
  const r = fit(radar, rctx); RW=r.w; RH=r.h;
  const byWidth  = (RW/2) - PAD_SIDE;
  const byHeight = RH - PAD_TOP - PAD_BOTTOM;
  R  = Math.max(30, Math.min(byWidth, byHeight));
  CX = RW/2; CY = RH - PAD_BOTTOM;
  const g = fit(graph, gctx); GW=g.w; GH=g.h;
}
window.addEventListener('resize', resizeAll);

function polar(angle, dist){
  const rr = Math.max(0, Math.min(1, dist/MAX_RANGE)) * R;
  const a  = angle * Math.PI/180;
  return { x: CX - rr*Math.cos(a), y: CY - rr*Math.sin(a) };
}
function fmtTime(ms){
  const s = Math.floor(ms/1000);
  return String(Math.floor(s/60)).padStart(2,'0') + ':' + String(s%60).padStart(2,'0');
}
const FONT = "9px ui-monospace,Consolas,monospace";

function drawRadar(now){
  rctx.clearRect(0,0,RW,RH);

  const hg = rctx.createRadialGradient(CX,CY,0,CX,CY,R*1.18);
  hg.addColorStop(0,'rgba(0,255,163,.10)');
  hg.addColorStop(.55,'rgba(0,255,163,.035)');
  hg.addColorStop(1,'rgba(0,255,163,0)');
  rctx.fillStyle = hg;
  rctx.beginPath(); rctx.arc(CX,CY,R*1.18,Math.PI,Math.PI*2); rctx.fill();

  for (let i=1; i<=5; i++){
    const rr = (i/5)*R;
    rctx.beginPath(); rctx.arc(CX,CY,rr,Math.PI,Math.PI*2);
    rctx.lineWidth = i===5?1.4:1;
    rctx.strokeStyle = i===5?'rgba(0,255,163,.42)':'rgba(0,255,163,.12)';
    if (i===5){ rctx.shadowBlur=12; rctx.shadowColor='rgba(0,255,163,.5)'; }
    rctx.stroke(); rctx.shadowBlur=0;
    rctx.fillStyle='rgba(95,138,141,.8)'; rctx.font=FONT; rctx.textAlign='left';
    rctx.fillText(String(Math.round(i*MAX_RANGE/5)), CX+6, CY-rr+3);
  }

  for (let a=0; a<=180; a+=30){
    const p = polar(a, MAX_RANGE);
    rctx.beginPath(); rctx.moveTo(CX,CY); rctx.lineTo(p.x,p.y);
    rctx.strokeStyle = a%90===0?'rgba(0,255,163,.20)':'rgba(0,255,163,.09)';
    rctx.lineWidth=1; rctx.stroke();
    const lp = polar(a, MAX_RANGE+12);
    rctx.fillStyle='rgba(95,138,141,.9)'; rctx.font=FONT; rctx.textAlign='center';
    rctx.fillText(a+'°', lp.x, lp.y+3);
    const t1 = polar(a, MAX_RANGE), t2 = polar(a, MAX_RANGE-6);
    rctx.beginPath(); rctx.moveTo(t1.x,t1.y); rctx.lineTo(t2.x,t2.y);
    rctx.strokeStyle='rgba(0,255,163,.30)'; rctx.stroke();
  }

  rctx.beginPath(); rctx.moveTo(CX-R,CY); rctx.lineTo(CX+R,CY);
  rctx.strokeStyle='rgba(0,255,163,.34)'; rctx.lineWidth=1.2; rctx.stroke();

  if (S.running){
    const trail = 30;
    const a0 = Math.max(-2, S.angle - trail);
    const a1 = Math.min(182, S.angle);
    if (a1 > a0){
      const wa0 = Math.PI + a0*Math.PI/180;
      const wa1 = Math.PI + a1*Math.PI/180;
      const wg = rctx.createRadialGradient(CX,CY,0,CX,CY,R);
      wg.addColorStop(0,'rgba(0,255,163,.22)');
      wg.addColorStop(.6,'rgba(0,255,163,.09)');
      wg.addColorStop(1,'rgba(0,255,163,0)');
      rctx.beginPath(); rctx.moveTo(CX,CY); rctx.arc(CX,CY,R,wa0,wa1); rctx.closePath();
      rctx.fillStyle = wg; rctx.fill();
    }
  }

  for (let i = S.blips.length-1; i >= 0; i--){
    const b = S.blips[i];
    const age = (now - b.t) / FADE_MS;
    if (age >= 1){ S.blips.splice(i,1); continue; }
    const alpha = 1 - age;
    const p = polar(b.angle, b.dist);
    const col = b.alert ? '255,59,92' : '0,255,163';
    const rad = b.alert ? 5.4 : 4;
    if (b.alert && age < 0.45){
      const k = age/0.45;
      rctx.beginPath(); rctx.arc(p.x,p.y, rad + k*28, 0, Math.PI*2);
      rctx.strokeStyle = "rgba("+col+","+((1-k)*0.7)+")"; rctx.lineWidth = 1.6; rctx.stroke();
    }
    const gg = rctx.createRadialGradient(p.x,p.y,0,p.x,p.y,rad*5);
    gg.addColorStop(0, "rgba("+col+","+(alpha*0.8)+")");
    gg.addColorStop(1, "rgba("+col+",0)");
    rctx.fillStyle = gg;
    rctx.beginPath(); rctx.arc(p.x,p.y,rad*5,0,Math.PI*2); rctx.fill();
    rctx.beginPath(); rctx.arc(p.x,p.y, rad*(1-age*0.45), 0, Math.PI*2);
    rctx.fillStyle = "rgba("+col+","+alpha+")";
    rctx.shadowBlur = 16; rctx.shadowColor = "rgba("+col+","+alpha+")";
    rctx.fill(); rctx.shadowBlur = 0;
  }

  if (S.running){
    const tip = polar(S.angle, MAX_RANGE);
    const eg = rctx.createLinearGradient(CX,CY,tip.x,tip.y);
    eg.addColorStop(0,'rgba(0,255,163,.10)');
    eg.addColorStop(.7,'rgba(0,255,163,.75)');
    eg.addColorStop(1,'rgba(190,255,235,1)');
    rctx.beginPath(); rctx.moveTo(CX,CY); rctx.lineTo(tip.x,tip.y);
    rctx.strokeStyle = eg; rctx.lineWidth = 2.4;
    rctx.shadowBlur = 18; rctx.shadowColor = 'rgba(0,255,163,.95)';
    rctx.stroke(); rctx.shadowBlur = 0;
  }

  rctx.beginPath(); rctx.arc(CX,CY,4.2,0,Math.PI*2);
  rctx.fillStyle='#00ffa3'; rctx.shadowBlur=20; rctx.shadowColor='#00ffa3';
  rctx.fill(); rctx.shadowBlur = 0;
  rctx.beginPath(); rctx.arc(CX,CY,10,Math.PI,Math.PI*2);
  rctx.strokeStyle='rgba(0,255,163,.35)'; rctx.lineWidth=1; rctx.stroke();
}

function drawGraph(){
  gctx.clearRect(0,0,GW,GH);
  const pad = { l:32, r:12, t:12, b:18 };
  const w = GW - pad.l - pad.r, h = GH - pad.t - pad.b;
  const yOf = function(d){ return pad.t + h - (d/MAX_RANGE)*h; };
  const xOf = function(i){ return pad.l + (i/Math.max(1,HIST_MAX-1))*w; };

  gctx.strokeStyle = 'rgba(0,255,163,.07)'; gctx.lineWidth = 1;
  for (let i=0;i<=5;i++){
    const d = (i/5)*MAX_RANGE, y = yOf(d);
    gctx.beginPath(); gctx.moveTo(pad.l,y); gctx.lineTo(pad.l+w,y); gctx.stroke();
    gctx.fillStyle='rgba(95,138,141,.75)'; gctx.font=FONT; gctx.textAlign='right';
    gctx.fillText(String(Math.round(d)), pad.l-7, y+3);
  }
  gctx.beginPath(); gctx.moveTo(pad.l,yOf(MAX_RANGE)); gctx.lineTo(pad.l+w,yOf(MAX_RANGE));
  gctx.setLineDash([4,4]); gctx.strokeStyle='rgba(255,200,87,.45)'; gctx.stroke();
  gctx.beginPath(); gctx.moveTo(pad.l,yOf(S.threshold)); gctx.lineTo(pad.l+w,yOf(S.threshold));
  gctx.strokeStyle='rgba(255,59,92,.65)';
  gctx.shadowBlur=8; gctx.shadowColor='rgba(255,59,92,.5)';
  gctx.stroke(); gctx.shadowBlur=0; gctx.setLineDash([]);

  if (S.history.length < 2) return;
  const start = HIST_MAX - S.history.length;

  gctx.beginPath();
  gctx.moveTo(xOf(start), yOf(MAX_RANGE));
  S.history.forEach(function(d,i){ gctx.lineTo(xOf(start+i), yOf(d)); });
  gctx.lineTo(xOf(start+S.history.length-1), yOf(MAX_RANGE));
  gctx.closePath();
  const fill = gctx.createLinearGradient(0,pad.t,0,pad.t+h);
  fill.addColorStop(0,'rgba(0,255,163,.26)');
  fill.addColorStop(.6,'rgba(0,194,255,.07)');
  fill.addColorStop(1,'rgba(0,255,163,0)');
  gctx.fillStyle = fill; gctx.fill();

  gctx.beginPath();
  S.history.forEach(function(d,i){
    const x = xOf(start+i), y = yOf(d);
    if (i===0) gctx.moveTo(x,y); else gctx.lineTo(x,y);
  });
  const lg = gctx.createLinearGradient(pad.l,0,pad.l+w,0);
  lg.addColorStop(0,'#00ffa3'); lg.addColorStop(1,'#00c2ff');
  gctx.strokeStyle = lg; gctx.lineWidth = 1.8; gctx.lineJoin = 'round';
  gctx.shadowBlur = 12; gctx.shadowColor = 'rgba(0,255,163,.7)';
  gctx.stroke(); gctx.shadowBlur = 0;

  S.history.forEach(function(d,i){
    if (d <= S.threshold){
      gctx.beginPath(); gctx.arc(xOf(start+i), yOf(d), 2.3, 0, Math.PI*2);
      gctx.fillStyle = '#ff3b5c';
      gctx.shadowBlur = 8; gctx.shadowColor = '#ff3b5c';
      gctx.fill(); gctx.shadowBlur = 0;
    }
  });

  const lastD = S.history[S.history.length-1];
  const hx = xOf(start+S.history.length-1), hy = yOf(lastD);
  gctx.beginPath(); gctx.arc(hx,hy,3.2,0,Math.PI*2);
  gctx.fillStyle='#eafff8';
  gctx.shadowBlur=14; gctx.shadowColor='#00ffa3';
  gctx.fill(); gctx.shadowBlur = 0;
}

const el = {
  distBig: document.getElementById('distBig'),
  angleSub: document.getElementById('angleSub'),
  statusBar: document.getElementById('statusBar'),
  readoutCard: document.getElementById('readoutCard'),
  ledG: document.getElementById('ledG'),
  ledR: document.getElementById('ledR'),
  stMin: document.getElementById('stMin'),
  stCount: document.getElementById('stCount'),
  stUp: document.getElementById('stUp'),
  stSweep: document.getElementById('stSweep'),
  logList: document.getElementById('logList'),
  badge: document.getElementById('badge'),
  btnScan: document.getElementById('btnScan'),
  spVal: document.getElementById('spVal'),
  thVal: document.getElementById('thVal')
};

function syncPauseUI(){
  el.btnScan.textContent = S.running ? 'Pause Scan' : 'Resume Scan';
  el.btnScan.classList.toggle('paused', !S.running);
  el.badge.textContent = S.running ? (S.live ? 'Live Feed' : 'Offline Demo') : 'Scan Paused';
  el.badge.classList.toggle('live', S.running);
}

let lastHud = 0;
function updateHUD(){
  const now = performance.now();
  if (now - lastHud < 70) return;
  lastHud = now;

  const dist = S.current.dist, detected = S.current.detected;
  const alert = detected && dist <= S.threshold;

  el.distBig.innerHTML = detected
    ? Math.round(dist) + '<span class="unit">cm</span>'
    : '--<span class="unit">cm</span>';
  el.distBig.classList.toggle('alert', alert);
  el.readoutCard.classList.toggle('alert', alert);

  el.angleSub.textContent = 'ANGLE ' + String(Math.round(S.angle)).padStart(3,'0') + '°';

  if (!S.running){
    el.statusBar.textContent = '❚❚ Paused';
    el.statusBar.className = 'statusbar paused';
  } else if (alert){
    el.statusBar.textContent = '⚠ Object Detected';
    el.statusBar.className = 'statusbar alert';
  } else if (detected){
    el.statusBar.textContent = '● Tracking';
    el.statusBar.className = 'statusbar';
  } else {
    el.statusBar.textContent = '● Scanning';
    el.statusBar.className = 'statusbar';
  }
  el.ledR.classList.toggle('on', alert);
  el.ledG.classList.toggle('on', !alert);

  el.stMin.innerHTML = S.minDist === null
    ? '--<small>cm</small>'
    : Math.round(S.minDist) + '<small>cm</small>';
  el.stCount.textContent = S.detections;
  el.stUp.textContent = fmtTime(Date.now() - S.startTime);
}

function addLog(angle, dist, alert){
  const empty = el.logList.querySelector('.empty');
  if (empty) empty.remove();
  const div = document.createElement('div');
  div.className = 'log-item' + (alert ? ' alert' : '');
  div.innerHTML =
    '<span class="a">' + String(Math.round(angle)).padStart(3,'0') + '° · ' +
    fmtTime(Date.now()-S.startTime) + '</span>' +
    '<span class="d">' + Math.round(dist) + ' cm</span>';
  el.logList.prepend(div);
  while (el.logList.children.length > 6) el.logList.lastChild.remove();
}

function applyReading(angle, distance, detected){
  S.angle = angle;
  S.current = { dist: distance, detected: detected };

  S.history.push(distance);
  if (S.history.length > HIST_MAX) S.history.shift();

  if (detected){
    const alert = distance <= S.threshold;
    S.blips.push({ angle: angle, dist: distance, t: performance.now(), alert: alert });
    S.detections++;
    if (S.minDist === null || distance < S.minDist) S.minDist = distance;
    const now = performance.now();
    if (now - S.lastLog > 400){
      S.lastLog = now;
      addLog(angle, distance, alert);
    }
  }
}

function simulateStep(){
  for (let i=0; i<targets.length; i++){
    const t = targets[i];
    t.a += t.drift;
    if (t.a < 12 || t.a > 168) t.drift *= -1;
  }
  let best = null;
  for (let i=0; i<targets.length; i++){
    const t = targets[i];
    if (Math.abs(t.a - S.angle) < t.w + 2.5){
      const d = t.d + (Math.random() - 0.5) * 1.6;
      if (best === null || d < best) best = d;
    }
  }
  const reading = best === null ? MAX_RANGE : Math.max(2, best);
  applyReading(S.angle, reading, best !== null);
}

function pollServer(){
  fetch('/data', { cache: 'no-store' })
    .then(function(r){
      if (!r.ok) throw new Error('no server');
      return r.json();
    })
    .then(function(p){
      S.live = true;
      S.fails = 0;
      if (typeof p.angle === 'number')    S.angle = p.angle;
      if (typeof p.running === 'boolean') S.running = p.running;
      if (typeof p.clients === 'number')
        document.getElementById('clients').textContent = p.clients;
      const distance = (typeof p.distance === 'number') ? p.distance : MAX_RANGE;
      applyReading(S.angle, distance, !!p.detected);
    })
    .catch(function(){
      S.fails++;
      if (S.fails >= 5) S.live = false;
    });
}
setInterval(pollServer, 120);
pollServer();

document.getElementById('thSlider').addEventListener('input', function(e){
  S.threshold = +e.target.value;
  el.thVal.textContent = S.threshold;
  drawGraph();
});

document.getElementById('spSlider').addEventListener('input', function(e){
  const v = +e.target.value;
  const names = {1:'Slow',2:'Medium',3:'Fast'};
  const ticks = {1:45, 2:30, 3:18};
  const steps = {1:2, 2:3, 3:4};

  S.tickMs = ticks[v];
  S.step   = steps[v];
  el.spVal.textContent = names[v];
  el.stSweep.innerHTML = ((180 / S.step) * S.tickMs * 2 / 1000).toFixed(1) + '<small>s</small>';

  if (S.live){
    fetch('/speed?v=' + v, { cache: 'no-store' }).catch(function(){});
  }
});

el.btnScan.addEventListener('click', function(){
  if (S.live){
    fetch('/scan', { cache: 'no-store' })
      .then(function(r){ return r.json(); })
      .then(function(p){ S.running = !!p.running; syncPauseUI(); })
      .catch(function(){
        S.running = !S.running;
        syncPauseUI();
      });
  } else {
    S.running = !S.running;
    syncPauseUI();
  }
});

document.getElementById('btnClear').addEventListener('click', function(){
  S.blips = []; S.history = []; S.detections = 0; S.minDist = null;
  S.current = { dist: null, detected: false };
  el.logList.innerHTML = '<div class="empty">Awaiting targets…</div>';
  el.stCount.textContent = '0';
  el.stMin.innerHTML = '--<small>cm</small>';
});

let lastTick = 0;
function loop(now){
  requestAnimationFrame(loop);

  if (!S.live && S.running){
    if (now - lastTick >= S.tickMs){
      lastTick = now;
      S.angle += S.dir * S.step;
      if (S.angle >= 180){ S.angle = 180; S.dir = -1; }
      if (S.angle <= 0){   S.angle = 0;   S.dir =  1; }
      simulateStep();
    }
  }

  drawBG(now);
  drawRadar(now);
  drawGraph();
  updateHUD();
  syncPauseUI();
}

resizeAll();
requestAnimationFrame(loop);
window.addEventListener('load', resizeAll);
setTimeout(resizeAll, 300);
setTimeout(resizeAll, 900);
setTimeout(function(){ document.getElementById('boot').classList.add('done'); }, 1150);
</script>
</body>
</html>
)=====";

#endif