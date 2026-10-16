# Glass Cockpit DLSS Fix for MSFS 2024 (DLSS, FSR and VR)

Removes **upscaler ghosting and smearing from glass cockpit displays** in Microsoft Flight Simulator 2024: speed and
altitude tapes, moving maps, ECAM pages and so on stay sharp and readable with **DLSS or FSR**, in every quality mode,
on a monitor and in VR.

It comes in two versions with the same fix inside; pick one:

- **ReShade add-on** (`glass-cockpit-dlss-fix.addon64`): for ReShade users. Status and settings in a tab of the ReShade
  menu.
- **Standalone** (`dxgi.dll`): no ReShade needed, one file next to the sim. Settings in a text file.

![Fenix A320 PFD in DLSS Performance: 8 s of stock DLSS smearing the altitude readout, then 8 s with the fix](docs/comparison.webp)

*Fenix A320 at 4K, DLSS Performance (1080p internal, upscaled to 4K), climbing at about 6,700 ft/min.
[Watch in full quality on YouTube](https://www.youtube.com/watch?v=Hcz8hwFndoc).*

It works with every aircraft that uses the simulator's cockpit display shaders, so it should cover most glass
cockpits. See [Compatibility](#compatibility) for the tested aircraft, VR headsets and GPUs.

> Unofficial community mod. Not affiliated with Microsoft, Asobo, NVIDIA, AMD or any aircraft developer.
> **Beta:** please report problems (see [Troubleshooting](#troubleshooting)). The standalone version is the newer of
> the two.

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

- Microsoft Flight Simulator 2024, DirectX 12 (Steam or Microsoft Store / Xbox app). **MSFS 2020 is not supported**
  (see [Game versions](#game-versions)).
- **DLSS Super Resolution** (NVIDIA RTX) or **FSR** (any GPU) selected in the sim's graphics settings.
- ReShade add-on only: [ReShade](https://reshade.me) 6.7 or newer **with full add-on support** (the "with full add-on
  support" download)

## Installation

Install **one** of the two versions. If both are installed, the standalone version stays off.

The game folder is the one that contains `FlightSimulator2024.exe`:

- Steam: `...\steamapps\common\MSFS2024\`. To find it, right-click the game in Steam, then **Manage → Browse local
  files**.
- Microsoft Store / Xbox app: usually `C:\XboxGames\Microsoft Flight Simulator 2024\Content\`. To find it, open the
  Xbox app, right-click the game, then **Manage → Files → Browse**.

### ReShade add-on

1. Install ReShade **with full add-on support** for MSFS 2024 (DirectX 10/11/12). You don't need any effects.
   In the ReShade setup, use **Browse...** and pick `FlightSimulator2024.exe` in the game folder.
   Microsoft Store / Xbox app: try `FlightSimulator2024.exe` first; if Windows refuses ("You don't have permission to
   open this file"), pick **`gamelaunchhelper.exe`** in the same folder instead: ReShade lands in the same place and
   loads with the sim. If setup says `dxgi.dll` already exists and doesn't belong to ReShade, another mod (e.g.
   OptiScaler or DLSS Enabler) is installed as `dxgi.dll`; see [Other mods](#other-mods) to load ReShade alongside it.
2. Download `glass-cockpit-dlss-fix.addon64` from the [latest release](../../releases/latest).
3. Copy it into the same folder as ReShade's DLL (the game folder).
4. Start the sim with DLSS or FSR selected and load a flight.

To check that it's working, open the ReShade menu (**Home** key) and go to the **Glass Cockpit DLSS Fix** tab: it
says "Working: fixing N screens" and shows a checklist. Or press **Ctrl+Shift+F11** in the cockpit: every screen it
fixes turns green-tinted. Press it again to turn the tint off.

**Update:** replace the `.addon64` file with the new one. **Uninstall:** delete `glass-cockpit-dlss-fix.addon64`
(and the `glass-cockpit-dlss-fix.*` files next to it).

### Standalone (no ReShade)

1. Download `dxgi.dll` from the [latest release](../../releases/latest).
2. Copy it into the game folder.
3. Start the sim with DLSS or FSR selected and load a flight.

If Windows asks whether to replace an existing `dxgi.dll` there, **don't**: another mod (usually ReShade or
OptiScaler) is already using that name. See [Other mods](#other-mods).

To check that it's working, press **Ctrl+Shift+F11** in the cockpit: every screen it fixes turns green-tinted. Press it
again to turn the tint off. The file `glass-cockpit-dlss-fix-status.txt` next to the DLL also says
"Working: fixing N screens" and shows a checklist.

**Switching from the add-on?** Delete `glass-cockpit-dlss-fix.addon64`. If you used ReShade only for the fix,
uninstall ReShade too (its `dxgi.dll` is in the same folder). Your settings carry over: both versions use the same
`glass-cockpit-dlss-fix.ini`.

**Update:** replace `dxgi.dll` with the new one. **Uninstall:** delete `dxgi.dll` and the `glass-cockpit-dlss-fix.*`
files next to it.

## Settings

The add-on has all settings in its tab in the ReShade menu (**Home**). Both versions keep them in
`glass-cockpit-dlss-fix.ini` next to the add-on or DLL, which is created on the first start with a comment on every
setting; with the standalone version, edit it with Notepad while the sim runs: saved changes apply within a second.

| Setting (ReShade tab / `.ini`) | What it does |
|---|---|
| Fix enabled / `enabled` (Ctrl+Shift+F9) | Fix on/off, for comparison |
| Line smoothing / `line_smoothing` (0-50 %, default 35 %) | Smooths stair steps on thin slanted lines in the screens, like the upscaler did. 0 = sharpest, 50 = softest. In the tab, Ctrl+click to type a value. Tick **Extra** next to it (`extra_smoothing=1`) to go up to 100 % (blurs the whole screen; for screens with very jagged lines) |
| Green tint (Ctrl+Shift+F11) | Tints every screen the fix covers (for checking, not remembered) |

Under **Troubleshooting → Advanced** in the tab, `[advanced]` and `jitter_positive` in the `.ini` (only change these if
asked to in a bug report; "Reset to defaults" in the tab puts them back):

| Setting (ReShade tab / `.ini`) | What it does |
|---|---|
| Flip jitter direction / `jitter_positive=0` | Only needed if the screen text shimmers when the camera is still |
| Glass layer / `glass_strength` (0-100 %, default 100 %) | How much of the sim's glass effects (dirt, glare, reflections, shadows) is kept on fixed screens. Lower values can help if quickly changing numbers leave a milky trail |

Under **Troubleshooting → Experimental fixes** in the tab, `[experimental]` in the `.ini` (**all off by default except
UV seam fix**; for problems that only some aircraft have, "Reset experimental fixes" in the tab puts them all back to
default):

| Setting (ReShade tab / `.ini`) | What it does |
|---|---|
| Dark screen fix / `dark_screen_fix` (off) | Keeps very dark screens fixed in strong sunlight (e.g. the F/A-18E Super Hornet). Off by default since 0.8.3, because it made some other screens drop out of the fix (e.g. the iFly EFB) |
| UV seam fix / `seam_fix` (on) | Removes thin dashed lines where a screen's picture meets a part of the same screen that uses another area of its image (FSS E-Jets: the line between the picture and its bezel band), and keeps those edges smooth on low DLSS modes. If a screen edge looks worse with it on, turn it off and please report the aircraft |
| Detail clamp / `detail_clamp` (0-100 %) | Keeps the fixed screens within the brightness the sim itself draws around each pixel. Hides texture detail too thin for the sim to show. **Can make screens flicker**, the more the lower the DLSS render resolution: almost none with DLAA and Quality, more with Balanced and Performance. Lower it if that bothers you, or if small text looks duller than with the fix off |
| Edge fade / `edge_fade` (0-250) | Fades screen edges into the sim's own picture, in hundredths of a render pixel (100 = 1 pixel). Can calm jaggy or crawling screen edges. Above about 200 it can flicker |
| Angle softening / `angle_softening` (0-100 %) | Draws screens seen at a steep angle softer, like the sim does. Screens seen straight on are unchanged |
| Edge stretcher / `edge_stretch` (0-400) | Extends screens outwards over their frame, in hundredths of a render pixel, continuing their picture. For screens that don't quite reach their frame |

The tab and the status file say "Experimental fixes changed" while any of them is on.

ReShade presets and effects keep working as usual on top of the fix.

## Compatibility

Both versions run the same fix; the results below were tested with the ReShade add-on unless noted. The standalone
version gets into the sim differently, so please report how it works for you.

### Aircraft

| Aircraft | Status |
|---|---|
| Fenix A320 family | Tested |
| iFly 737 MAX 8 | Tested (0.7.5 or newer; the EFB tablet is left to DLSS/FSR, see [Known limitations](#known-limitations)) |
| iniBuilds A220 | Tested |
| iniBuilds A330 | Tested |
| iniBuilds A340 | Tested (0.7.2 or newer; in VR 0.7.3 or newer) |
| iniBuilds A350 | Tested |
| iniBuilds A380 | Tested |
| PMDG 737 | Tested by the community (also in VR) |
| PMDG 777 | Tested by the community (also in VR) |
| FlightFX C750 | Tested by the community (0.7.6 or newer) |
| Default DA62 | Tested |
| Default Cessna Longitude | Tested by the community (in VR) |
| FSS E-Jets (ERJ-170/175/190/195) | Tested (0.8.3 or newer removes the dashed line at the screens' edges) |
| Default F/A-18E Super Hornet | Tested (if its dark screens drop out of the fix in strong sun, turn on Dark screen fix, see [Settings](#settings)) |

Other glass cockpits should work too. If some screens of an aircraft don't turn green with Ctrl+Shift+F11, please
report it (see [Troubleshooting](#troubleshooting)).

### VR

No special install for VR: install either version exactly as for a monitor (for the add-on: ReShade for DirectX 12 with
full add-on support). The fix works inside the sim's own rendering, so it covers the headset views automatically.
ReShade's OpenXR / VR option is only for showing ReShade's own effects and menu in the headset and isn't needed.

| Headset | Status |
|---|---|
| Meta Quest 3 through Virtual Desktop | Tested with DLSS and FSR, foveated rendering on and off |
| Pimax Crystal Light | Tested by the community (DLSS) |

Other headsets and runtimes should work the same; reports welcome.

### GPUs and upscalers

| Setup | Status |
|---|---|
| NVIDIA RTX, DLSS Super Resolution | Tested, including DLSS Frame Generation up to 6x Multi Frame Generation |
| NVIDIA, FSR | Tested |
| AMD, FSR | Tested by the community on an RX 6800 XT and an RX 7800 XT (0.7.6 or newer runs much lighter on AMD and Intel) |
| Intel, FSR | Untested, reports welcome |
| Any GPU, upscaler chosen in OptiScaler | Tested on NVIDIA with DLSS, FSR 2/3 and XeSS, and by the community on an AMD RX 9070 XT with DLSS selected and FSR 4 underneath (0.8.0 or newer), see [Other mods](#other-mods) |

### Game versions

Tested on the Microsoft Store / Xbox app (Game Pass) version and by the community on Steam.

**MSFS 2020 is not supported.** The fix finds the cockpit screens by how MSFS 2024 draws them, and I don't have
2020 to test or port it. The source is open (MIT), so a 2020 port by someone who has it is welcome.

### Other mods

- **ReShade presets and effects:** work as usual with the add-on. With the standalone version, ReShade can't be
  `dxgi.dll` at the same time: load it through an ASI loader (as `ReShade64.asi`) or through OptiScaler's
  `LoadReshade` option. Its effects then work as usual on top of the fix. (If you use ReShade anyway, the add-on is the
  simpler choice.)
- **DLSS 5 / Neural Rendering add-ons:** tested alongside the RenoDX DLSS 5 add-on. **Freeze warning:** with
  `renodx-dlss.addon64` installed, the sim can freeze when a Fenix aircraft loads. This happens with this fix removed
  too, so it's between RenoDX and the Fenix; if you get it, remove `renodx-dlss.addon64` (OptiScaler or OptiShade also
  offer Neural Rendering).
- **Extra DLSS passes:** if a mod or the sim runs a second DLSS pass at the internal resolution, 0.8.3 or newer keeps
  the fix on the sim's real upscale (the one with the largest output).
- **Standalone DLSS Glass Cockpit Refresh** ([wesimglide.org](https://wesimglide.org/otherdata/tools/Standalone-DLSS-Glass-Cockpit-Refresh.html)):
  a third-party package of this add-on with ReShade built in, by WeSimGlide. For problems with it, follow the support
  steps on its page. Don't use it together with either version of this fix (the fix would run twice).
- **OptiShade:** the OptiShade developer is building this fix into OptiShade.
- **Multi Frame Generation unlocks for RTX 40:**
  - **RenoDX MFG unlock add-on:** tested, works together with this fix.
  - **[RTX40MFG-Unlock](https://github.com/dashdogy/RTX40MFG-Unlock) by dashdogy:** tested with v1.4.2 (installed as
    `winmm.dll` next to an ASI loader's `version.dll`; `version.dll` alone works too), so it can stay as it is with
    either version. It redirects DLSS, and 0.7.5 or newer follows that redirect; older versions log "could not hook
    DLSS evaluate". Its Backspace menu doesn't show up when ReShade is loaded, with or without this fix, so set the
    multiplier in the sim's frame generation setting or in its `RTXMFG-Universal.json`.
- **OptiScaler:** works with any upscaler selected in OptiScaler (DLSS, FSR 2/3/4, XeSS; 0.8.0 or newer for anything
  but DLSS), including OptiScaler's DLSS 5 Neural Rendering. On AMD and Intel GPUs this also lets you select DLSS in
  the sim and have OptiScaler run FSR or XeSS (0.8.0 or newer; tested on NVIDIA, and by the community on an AMD RX 9070 XT
  with FSR 4). If ReShade says "There were errors loading some add-ons", update to 0.7.4 or newer. OptiScaler is
  usually installed as `dxgi.dll`:
  - with the add-on, load ReShade through an ASI loader or through OptiScaler's `LoadReshade` option instead;
  - with the standalone version, rename OptiScaler's `dxgi.dll` to another name it supports (e.g. `winmm.dll` or
    `version.dll`) and keep the fix as `dxgi.dll`.
- **DLSS Enabler:** built on OptiScaler, so it should work the same way (0.8.0 or newer). Not tested yet, reports
  welcome.
- **Standalone version through an ASI loader instead of as `dxgi.dll`:** don't. An ASI loader usually loads the DLL
  after the sim has set up its graphics, and then the fix can't see what it needs: screens will most likely stay
  unfixed (the log says so).

## Troubleshooting

First look at what the fix reports about itself: the add-on's **Glass Cockpit DLSS Fix** tab in the ReShade menu
(**Home**), or with the standalone version `glass-cockpit-dlss-fix-status.txt` next to the DLL (updated every 10 seconds
while the sim runs). Both show what works and what doesn't (GPU, upscaler running, cockpit shader found, screens
recorded, fix drawn), explain any problem in plain words and give a report for bug reports (the tab's **Copy report**
button, the end of the status file). The tab also has an **Open log folder** button.

### What to send with a bug report

| Problem | Send |
|---|---|
| The fix doesn't work at all, the tab or status file shows a problem, a screen is never fixed, a crash or freeze | **Both logs**: `glass-cockpit-dlss-fix.log` and `glass-cockpit-dlss-fix.old.log` (next to the add-on or DLL; button **Open log folder** in the tab). For screens that are never fixed, press **Ctrl+Shift+F12** while looking at them first |
| Something you can see on fixed screens: wrong or changing colours, flicker, lines, jagged or blurry edges, trails | A **capture**: with the problem visible, press **Ctrl+Shift+F8** (or **Capture screens** in the tab), keep the screens in view for a few seconds, then attach the `glass-capture-....zip` that appears next to the logs. It already contains both logs |

Always mention which version you use (add-on or standalone), the aircraft, your DLSS/FSR mode, Frame Generation on/off
and other mods (OptiScaler, ReShade, RenoDX, MFG unlocks...).

The **logs** are written every session: `glass-cockpit-dlss-fix.log` next to the add-on or DLL, and the previous
session as `glass-cockpit-dlss-fix.old.log` (if the sim crashed or you restarted it, the problem is in the `.old.log`).
The **capture** saves a few frames as pictures, cropped to the cockpit screens: what the sim drew, the upscaled frame
before and after the fix, and the frames sent to your monitor, plus a summary. It is only made when you press it and
costs nothing otherwise; nothing is uploaded anywhere.

The log lists which version it is, your GPU, driver, ReShade version (add-on), the DLSS/FSR files the sim loaded and
other mods, followed by milestones in order:

1. `milestone DLSS runtime found` / `FSR runtime found`
2. `milestone cockpit display shader found`
3. `milestone first DLSS frame` / `milestone first FSR frame`
4. `milestone first cockpit screen recorded`
5. `milestone first overlay frame drawn (fix is active)`

In VR also `milestone VR cockpit display shader found`, `milestone first VR cockpit screen recorded` and
`vr view order` lines.

The first missing milestone shows where it stopped. Lines starting with `WARNING` or `ERROR` explain common
problems in plain words, e.g. no upscaler selected, or a sim update that changed the display shader.

| Problem | Try |
|---|---|
| Add-on: no "Glass Cockpit DLSS Fix" tab in the ReShade menu | The add-on isn't loaded. If the ReShade menu has no **Add-ons** tab, reinstall ReShade with the *full add-on support* download. Check that the file is next to the ReShade DLL, and that **Settings → Add-on search path** in the ReShade menu points to that folder. |
| Standalone: no `glass-cockpit-dlss-fix.log` appears | The DLL isn't loaded. Check that it is named exactly `dxgi.dll` and is in the same folder as `FlightSimulator2024.exe` (Windows may hide the `.dll` extension: it must not be `dxgi.dll.dll`) |
| Standalone: log says the device was not seen, or "loaded after the sim created its graphics device" | The DLL was loaded too late, usually because it was loaded as `.asi` or another mod renamed it. Install it as `dxgi.dll` |
| Nothing changes, no green tint | Check that DLSS or FSR is selected (add-on: that ReShade is the *full add-on support* build and the file is next to the ReShade DLL). Then read the tab or status file, and the log. |
| Picture freezes or turns black with Frame Generation on (fine when alt-tabbed) | Update to 0.8.1 or newer (0.8.0 only) |
| Sim freezes when a Fenix aircraft loads, with RenoDX's DLSS add-on installed | Remove `renodx-dlss.addon64`; see [Other mods](#other-mods) |
| "Only DLSS Frame Generation is running" | Frame Generation is on but Anti-Aliasing isn't DLSS or FSR (e.g. TAA). Set Anti-Aliasing to DLSS (any mode, DLAA too) or FSR; Frame Generation can stay on |
| Some screens of an aircraft stay normal | Look at those screens in the cockpit, press **Ctrl+Shift+F12** (writes a short diagnostic to the log), then send both logs and the aircraft name |
| Screen lines look jagged / too soft | Adjust Line smoothing |
| Dashed light line along the edge of a screen's picture (e.g. FSS E-Jets) | Update to 0.8.3 or newer and keep **UV seam fix** on. If a line remains, try **Detail clamp** (can add some flicker on DLSS Balanced/Performance) |
| Dark screens drop out of the fix (green tint goes away) in strong sun | Turn on **Dark screen fix** |
| Screens change colour for a moment while the camera or aircraft moves (most often with Frame Generation) | Update to 0.8.3 or newer (on a monitor; the VR version of this fix comes later) |
| Screen text shimmers when the camera is still | Turn on **Flip jitter direction** (`jitter_positive=0`). If it's already on (the tab or status file says "Advanced settings changed"), turn it off again |
| Screens flicker in brightness (G-Sync / FreeSync monitor) | VRR flicker from a changing frame rate, most visible on dark screens. Turn on V-Sync, or cap the frame rate a few fps below your refresh rate |
| Crash at startup | Remove the add-on or `dxgi.dll`, start once, put it back, then send both logs |

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

To see what the sim draws, the fix hooks the few Direct3D 12 functions it needs: device and pipeline creation, root
signatures, views, the command list calls that bind pipelines, descriptor tables and render targets, the draws, and the
swapchain's present. Everything else goes straight to Windows. The two versions differ only in how the fix gets into
the sim: ReShade loads the add-on and tells it about the sim's graphics device and swapchain; the standalone version is
loaded by Windows as the sim's `dxgi.dll` (it passes every call on to Windows' own `dxgi.dll`) and sees the device being
created.

It works at any resolution and in any quality mode, and costs one extra draw per screen plus a few small GPU passes:
no measurable FPS difference with the fix on or off in testing.

## Known limitations

- A screen whose picture the fix can't redraw (e.g. the iFly 737 MAX EFB tablet) is left to DLSS/FSR, so it looks
  like stock.
- A thin band at each screen's edge (about one render pixel) still comes from the upscaler (Edge fade and Edge
  stretcher under Experimental fixes can help on some aircraft).
- Anything that passes in front of a screen after the cockpit is drawn (e.g. hands in VR) would be covered by it.
- VR: the 0.8.3 fix for screens briefly changing colour while moving is for monitors only so far. It will come to VR
  in a later version.
- Standalone: no in-game menu. Settings are in the `.ini` file, status in the status file.
- Sim updates that change the cockpit display shader stop the fix (the sim then just looks like stock DLSS/FSR)
  until it is updated.

## Building from source

The full source is in this repository. See [BUILDING.md](BUILDING.md) to build both versions yourself.

## License

MIT, see [LICENSE](LICENSE). Third-party components are listed in [THIRD_PARTY_NOTICES.md](THIRD_PARTY_NOTICES.md).
