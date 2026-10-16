# Glass Cockpit DLSS Fix for MSFS 2024, standalone (no ReShade)

Removes **upscaler ghosting and smearing from glass cockpit displays** in Microsoft Flight Simulator 2024: speed and
altitude tapes, moving maps, ECAM pages and so on stay sharp and readable with **DLSS or FSR**, in every quality mode,
on a monitor and in VR.

This is a fork of [Glass Cockpit DLSS Fix](https://github.com/IFreemz/msfs2024-glass-cockpit-dlss-fix) by IFreemz, which
is a ReShade add-on. The fix is the same; this version needs **no ReShade**: it is one file, `dxgi.dll`, that you drop
next to the sim.

![Fenix A320 PFD in DLSS Performance: 8 s of stock DLSS smearing the altitude readout, then 8 s with the fix](docs/comparison.webp)

*Fenix A320 at 4K, DLSS Performance (1080p internal, upscaled to 4K), climbing at about 6,700 ft/min.
[Watch in full quality on YouTube](https://www.youtube.com/watch?v=Hcz8hwFndoc).*

It works with every aircraft that uses the simulator's cockpit display shaders, so it should cover most glass
cockpits. See [Compatibility](#compatibility).

> Unofficial community mod. Not affiliated with Microsoft, Asobo, NVIDIA, AMD or any aircraft developer.
> **Beta:** the standalone version is new. Please report problems in this repository's [issues](../../issues) (see
> [Troubleshooting](#troubleshooting) for what to send).

## Contents

- [Requirements](#requirements)
- [Installation](#installation)
- [Settings](#settings)
- [Compatibility](#compatibility)
- [Troubleshooting](#troubleshooting)
- [How the fix works](#how-the-fix-works)
- [Known limitations](#known-limitations)
- [Building from source](#building-from-source)
- [License](#license)

## Requirements

- Microsoft Flight Simulator 2024, DirectX 12 (Steam or Microsoft Store / Xbox app). **MSFS 2020 is not supported.**
- **DLSS Super Resolution** (NVIDIA RTX) or **FSR** (any GPU) selected in the sim's graphics settings.

## Installation

1. Download `dxgi.dll` from the [latest release](../../releases/latest).
2. Copy it into the folder that contains `FlightSimulator2024.exe`:
   - Steam: `...\steamapps\common\MSFS2024\`. To find it, right-click the game in Steam, then **Manage → Browse local
     files**.
   - Microsoft Store / Xbox app: usually `C:\XboxGames\Microsoft Flight Simulator 2024\Content\`. To find it, open the
     Xbox app, right-click the game, then **Manage → Files → Browse**.
3. Start the sim with DLSS or FSR selected and load a flight.

If Windows asks whether to replace an existing `dxgi.dll` there, **don't**: another mod (usually ReShade or
OptiScaler) is already using that name. See [Other mods](#other-mods).

To check that it's working, press **Ctrl+Shift+F11** in the cockpit: every screen it fixes turns green-tinted. Press it
again to turn the tint off. The file `glass-cockpit-dlss-fix-status.txt` next to the DLL also says
"Working: fixing N screens" and shows a checklist.

**Coming from the ReShade add-on version?** Delete `glass-cockpit-dlss-fix.addon64`. If you used ReShade only for the
fix, uninstall ReShade too (its `dxgi.dll` is in the same folder). If both versions are installed, this one stays off.

**Update:** replace `dxgi.dll` with the new one. **Uninstall:** delete `dxgi.dll` and the `glass-cockpit-dlss-fix.*`
files next to it.

## Settings

Settings are in `glass-cockpit-dlss-fix.ini` next to the DLL. It is created on the first start, with a comment on every
setting. Edit it with Notepad while the sim runs: saved changes apply within a second.

| Setting | What it does |
|---|---|
| `enabled` (Ctrl+Shift+F9) | Fix on (1) or off (0), for comparison |
| `line_smoothing` (0-50, default 35) | Smooths stair steps on thin slanted lines in the screens, like the upscaler did. 0 = sharpest, 50 = softest. With `extra_smoothing=1` it goes up to 100 (blurs the whole screen; for screens with very jagged lines) |
| Green tint (Ctrl+Shift+F11) | Tints every screen the fix covers (for checking, not saved) |

Under `[advanced]` and `jitter_positive` (only change these if asked to in a bug report):

| Setting | What it does |
|---|---|
| `jitter_positive` (default 1) | Set to 0 only if the screen text shimmers when the camera is still |
| `glass_strength` (0-100, default 100) | How much of the sim's glass effects (dirt, glare, reflections, shadows) is kept on fixed screens. Lower values can help if quickly changing numbers leave a milky trail |

Under `[experimental]` (**all off by default except `seam_fix`**; for problems that only some aircraft have):

| Setting | What it does |
|---|---|
| `dark_screen_fix` (0) | Keeps very dark screens fixed in strong sunlight (e.g. the F/A-18E Super Hornet). Off by default because it made some other screens drop out of the fix (e.g. the iFly EFB) |
| `seam_fix` (1) | Removes thin dashed lines where a screen's picture meets a part of the same screen that uses another area of its image (FSS E-Jets), and keeps those edges smooth on low DLSS modes. If a screen edge looks worse with it on, set it to 0 and please report the aircraft |
| `detail_clamp` (0-100) | Keeps the fixed screens within the brightness the sim itself draws around each pixel. Hides texture detail too thin for the sim to show. **Can make screens flicker**, the more the lower the DLSS render resolution |
| `edge_fade` (0-250) | Fades screen edges into the sim's own picture, in hundredths of a render pixel (100 = 1 pixel). Can calm jaggy or crawling screen edges. Above about 200 it can flicker |
| `angle_softening` (0-100) | Draws screens seen at a steep angle softer, like the sim does. Screens seen straight on are unchanged |
| `edge_stretch` (0-400) | Extends screens outwards over their frame, in hundredths of a render pixel, continuing their picture. For screens that don't quite reach their frame |

## Compatibility

The fix itself is the same as in the ReShade add-on, which has been tested with the aircraft, headsets and GPUs below.
The standalone version gets into the sim differently, so please report how it works for you.

### Aircraft

| Aircraft | Status (ReShade add-on) |
|---|---|
| Fenix A320 family | Tested |
| iFly 737 MAX 8 | Tested (the EFB tablet is left to DLSS/FSR, see [Known limitations](#known-limitations)) |
| iniBuilds A220, A330, A340, A350, A380 | Tested |
| PMDG 737, PMDG 777 | Tested by the community (also in VR) |
| FlightFX C750 | Tested by the community |
| Default DA62 | Tested |
| Default Cessna Longitude | Tested by the community (in VR) |
| FSS E-Jets (ERJ-170/175/190/195) | Tested |
| Default F/A-18E Super Hornet | Tested (if its dark screens drop out of the fix in strong sun, set `dark_screen_fix=1`) |

Other glass cockpits should work too. If some screens of an aircraft don't turn green with Ctrl+Shift+F11, please
report it (see [Troubleshooting](#troubleshooting)).

### VR

No special install for VR. The fix works inside the sim's own rendering, so it covers the headset views automatically.
Tested (with the add-on) on a Meta Quest 3 through Virtual Desktop (DLSS and FSR, foveated rendering on and off) and by
the community on a Pimax Crystal Light (DLSS).

### GPUs and upscalers

| Setup | Status (ReShade add-on) |
|---|---|
| NVIDIA RTX, DLSS Super Resolution | Tested, including DLSS Frame Generation up to 6x Multi Frame Generation |
| NVIDIA, FSR | Tested |
| AMD, FSR | Tested by the community on an RX 6800 XT and an RX 7800 XT |
| Intel, FSR | Untested, reports welcome |
| Any GPU, upscaler chosen in OptiScaler | Tested on NVIDIA with DLSS, FSR 2/3 and XeSS, and by the community on an AMD RX 9070 XT with DLSS selected and FSR 4 underneath |

### Other mods

The fix has to be loaded as `dxgi.dll` at the start of the sim (to see the sim create its graphics device), and only
one file can have that name. Mods that also use `dxgi.dll` can be loaded another way:

- **ReShade (for its effects):** can't be `dxgi.dll` at the same time. Load it through an ASI loader (as
  `ReShade64.asi`) or through OptiScaler's `LoadReshade` option. ReShade's effects then work as usual on top of the fix.
  Don't also install the ReShade add-on version of the fix.
- **OptiScaler / DLSS Enabler:** rename OptiScaler's `dxgi.dll` to another name it supports (e.g. `winmm.dll` or
  `version.dll`) and keep the fix as `dxgi.dll`. Works with any upscaler selected in OptiScaler (DLSS, FSR 2/3/4, XeSS),
  including on AMD and Intel GPUs with DLSS selected in the sim.
- **Multi Frame Generation unlocks for RTX 40:** [RTX40MFG-Unlock](https://github.com/dashdogy/RTX40MFG-Unlock) uses
  `winmm.dll` / `version.dll`, so it can stay as it is. The fix follows its DLSS redirect.
- **DLSS 5 / Neural Rendering add-ons (RenoDX):** these are ReShade add-ons, so they need ReShade loaded as above.
  With `renodx-dlss.addon64` installed the sim can freeze when a Fenix aircraft loads (also without this fix).
- **Extra DLSS passes:** if a mod or the sim runs a second DLSS pass at the internal resolution, the fix stays on the
  sim's real upscale (the one with the largest output).
- **Standalone DLSS Glass Cockpit Refresh** (WeSimGlide): a package of the ReShade add-on with ReShade built in. Don't
  use it together with this (the fix would run twice).
- **An ASI loader instead of `dxgi.dll`:** don't. An ASI loader usually loads the DLL after the sim has set up its
  graphics, and then the fix can't see what it needs: screens will most likely stay unfixed (the log says so).

## Troubleshooting

Open `glass-cockpit-dlss-fix-status.txt` next to the DLL first. It shows what works and what doesn't (GPU, upscaler
running, cockpit shader found, screens recorded, fix drawn), explains any problem in plain words and ends with a report
to paste into bug reports. It is updated every 10 seconds while the sim runs.

| Problem | Send |
|---|---|
| The fix doesn't work at all, the status file shows a problem, a screen is never fixed, a crash or freeze | **Both logs**: `glass-cockpit-dlss-fix.log` and `glass-cockpit-dlss-fix.old.log` (next to the DLL). For screens that are never fixed, press **Ctrl+Shift+F12** while looking at them first |
| Something you can see on fixed screens: wrong or changing colours, flicker, lines, jagged or blurry edges, trails | A **capture**: with the problem visible, press **Ctrl+Shift+F8**, keep the screens in view for a few seconds, then attach the `glass-capture-....zip` that appears next to the logs. It already contains both logs |

Always mention the aircraft, your DLSS/FSR mode, Frame Generation on/off and other mods (OptiScaler, ReShade, MFG
unlocks...). Open an [issue in this repository](../../issues) for problems with this standalone version, not in the
ReShade add-on's repository.

The **logs** are written every session: `glass-cockpit-dlss-fix.log` next to the DLL, and the previous session as
`glass-cockpit-dlss-fix.old.log` (if the sim crashed or you restarted it, the problem is in the `.old.log`). The
**capture** saves a few frames as pictures, cropped to the cockpit screens: what the sim drew, the upscaled frame
before and after the fix, and the frames sent to your monitor, plus a summary. It is only made when you press it and
costs nothing otherwise; nothing is uploaded anywhere.

The log lists your GPU, driver, the DLSS/FSR files the sim loaded and other mods, followed by milestones in order:

1. `milestone DLSS runtime found` / `FSR runtime found`
2. `milestone cockpit display shader found`
3. `milestone first DLSS frame` / `milestone first FSR frame`
4. `milestone first cockpit screen recorded`
5. `milestone first overlay frame drawn (fix is active)`

The first missing milestone shows where it stopped. Lines starting with `WARNING` or `ERROR` explain common problems in
plain words.

| Problem | Try |
|---|---|
| No `glass-cockpit-dlss-fix.log` appears | The DLL isn't loaded. Check that it is named exactly `dxgi.dll` and is in the same folder as `FlightSimulator2024.exe` (Windows may hide the `.dll` extension: it must not be `dxgi.dll.dll`) |
| Log says the device was not seen, or "loaded after the sim created its graphics device" | The DLL was loaded too late, usually because it was loaded as `.asi` or another mod renamed it. Install it as `dxgi.dll` |
| Nothing changes, no green tint | Check that DLSS or FSR is selected, then read the status file and the log |
| Status file says "Only DLSS Frame Generation is running" | Frame Generation is on but Anti-Aliasing isn't DLSS or FSR (e.g. TAA). Set Anti-Aliasing to DLSS (any mode, DLAA too) or FSR; Frame Generation can stay on |
| Some screens of an aircraft stay normal | Look at those screens in the cockpit, press **Ctrl+Shift+F12** (writes a short diagnostic to the log), then send both logs and the aircraft name |
| Screen lines look jagged / too soft | Adjust `line_smoothing` |
| Dashed light line along the edge of a screen's picture (e.g. FSS E-Jets) | Keep `seam_fix=1`. If a line remains, try `detail_clamp` (can add some flicker on DLSS Balanced/Performance) |
| Dark screens drop out of the fix (green tint goes away) in strong sun | Set `dark_screen_fix=1` |
| Screen text shimmers when the camera is still | Set `jitter_positive=0`. If it's already 0, set it back to 1 |
| Screens flicker in brightness (G-Sync / FreeSync monitor) | VRR flicker from a changing frame rate, most visible on dark screens. Turn on V-Sync, or cap the frame rate a few fps below your refresh rate |
| Crash at startup | Remove `dxgi.dll`, start once, put it back, then send both logs |

## How the fix works

DLSS and FSR build each frame from the history of previous frames, guided by motion vectors. A cockpit screen does
not move, but its *content* does, so the upscaler keeps blending old numbers into new ones. The game's own hint for
this (the animated-texture mask) isn't enough, and no DLSS preset (J, K, M) fixes it.

The fix uses the same idea that DLSS mods for other games use for HUDs: **draw the screen content after the
upscaler**.

1. When the sim draws a cockpit screen, the fix draws the same mesh once more into a small private map that records
   which part of which screen image lands on each pixel.
2. Right after DLSS or FSR, it samples the sim's own clean screen image at full output resolution (with the frame's
   camera jitter removed) and writes it over the upscaled result, so the moving content never goes through the
   upscaler's history.
3. Brightness is matched to the sim every frame, so night lighting and the brightness knobs still work. Dirt, sun
   glare and shadows on the glass are taken from the upscaled image itself, limited to what this frame actually
   shows, so they stay sharp while trails of old screen content are removed.

In VR the sim draws every view (both eyes, plus the sharp centre views with foveated rendering) in one go and then
upscales them one by one; the fix records each view separately and learns from the sim which upscale belongs to which
view.

**Without ReShade:** the ReShade add-on learned what the sim draws from ReShade's events. This version is loaded as the
sim's `dxgi.dll` (it passes every call on to Windows' own `dxgi.dll`) and hooks the few Direct3D 12 functions it needs
directly: device and pipeline creation, root signatures, views, the command list calls that bind pipelines, descriptor
tables and render targets, the draws, and the swapchain's present. Everything else goes straight to Windows.

## Known limitations

- A screen whose picture the fix can't redraw (e.g. the iFly 737 MAX EFB tablet) is left to DLSS/FSR, so it looks
  like stock.
- A thin band at each screen's edge (about one render pixel) still comes from the upscaler (`edge_fade` and
  `edge_stretch` can help on some aircraft).
- Anything that passes in front of a screen after the cockpit is drawn (e.g. hands in VR) would be covered by it.
- VR: the fix for screens briefly changing colour while moving is for monitors only so far.
- No in-game menu: settings are in the `.ini` file, status in the status file.
- Sim updates that change the cockpit display shader stop the fix (the sim then just looks like stock DLSS/FSR)
  until it is updated.

## Building from source

The full source is in this repository. See [BUILDING.md](BUILDING.md).

## License

MIT, see [LICENSE](LICENSE). Based on the ReShade add-on by IFreemz (MIT). Third-party components are listed in
[THIRD_PARTY_NOTICES.md](THIRD_PARTY_NOTICES.md).
