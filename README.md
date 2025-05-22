# Ghost – Lightweight Transform Recorder & Replayer for Unreal Engine 5

TimeTurner is a **tiny Unreal Engine plugin** (≈ 250 lines of code) that lets you  
record an Actor’s transform at runtime or PIE and instantly **replay** it as a
“ghost” path.  
It’s perfect for quick AI path visualization, instant‑replay kill‑cams, racing
lap ghosts, cinematic pre‑vis, physics determinism checks, and rapid
time‑rewind prototypes.

<p align="center">
  <img src="docs/preview.gif" alt="Ghost plugin demo" width="640">
</p>

---

## ✨ Features

| ✔ | Capability | Notes |
|---|------------|-------|
| 🔴 | **Record** an Actor’s position, rotation & scale every tick (or at a custom sampling interval). | Lightweight: 1 key ≈ 28 bytes. |
| 🟢 | **Replay** the track in place, looped or one‑shot. | Deterministic, frame‑rate‑independent. |
| 🟣 | **Blueprint‑exposed** component & helper library. | Drop‑in, no C++ required. |
| 🟡 | Works in **PIE, Stand‑alone, cooked builds**. | Tick‑driven, no editor dependencies. |
| 🟠 | **API hooks** for OnRecordingStopped / OnPlaybackFinished. | Chain VFX, UI, or analytics. |
| 🟤 | Extensible: spline export, network replication, time‑scrubbing, key reduction. | See “Extending” below. |

---

## 🛠 Installation

1. **Clone / copy** this repo into your UE project’s `Plugins/` folder  
   (or fork & add as a sub‑module).


