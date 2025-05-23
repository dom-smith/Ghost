# Ghost – Lightweight Transform Recorder & Replayer for Unreal Engine 5

Ghost is a **tiny Unreal Engine plugin** (≈ 250 lines of code) that lets you  
record an Actor’s transform at runtime or PIE and instantly **replay** it as a
“ghost” path.  
It’s perfect for quick AI path visualization, instant‑replay kill‑cams, racing
lap ghosts, cinematic pre‑vis, physics determinism checks, and rapid
time‑rewind prototypes.

## Installation

1. **Clone / copy** this repo into your UE project’s `Plugins/` folder  
   (or fork & add as a sub‑module).
   
    MyProject/
    └─ Plugins/
    └─ Ghost/ ← this repo

   
2. Regenerate Visual Studio/Xcode files (right‑click `.uproject` → *Generate
project files*).

3. Build the project (Development Editor).

4. In the Unreal Editor open **Edit → Plugins**, enable **Ghost**, and restart.

> **Engine versions**  
> Tested on UE 5.0 → 5.4. Should work on UE 4.27 if you rename the module’s
> `Default` loading phase to `PostEngineInit`.

---

## Quick Start

1. **Add Component** → *Transform History* to any Actor you want to track.
   
2. In Blueprint:
   ``` 
   Event BeginPlay
       → StartRecording (target: TransformHistoryComponent)
   
   Custom Event <StopAndReplay>
       → StopRecording
       → PlayBack   (Loop = false, OverrideDuration = 0)
   
3. Press Play‑in‑Editor → run around → trigger ShowReplay.
The Actor rewinds along its exact path.


Blueprint nodes:
StartRecording:	Begin capturing keyframes.
StopRecording:	Stop and seal the buffer (adds a final key).
PlayBack(loop, overrideDuration):	Re‑animate the track.
ClearHistory:	Wipe all samples.
GetRecordedLength:	Total seconds captured.
AddTransformHistoryComponent(Target):	Runtime helper (library node).

