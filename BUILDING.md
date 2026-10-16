# Building from source

You only need this to change the fix. To use it, download the release instead (see the [README](README.md)).

Requirements: Visual Studio 2022 with the C++ x64 tools, and the Windows 10/11 SDK (provides `dxc` and `rc`).

```powershell
git clone -b standalone https://github.com/jtsorlinis/msfs2024-glass-cockpit-dlss-fix-no-reshade
cd msfs2024-glass-cockpit-dlss-fix-no-reshade
git submodule update --init --depth 1
powershell -ExecutionPolicy Bypass -File scripts\build.ps1
```

The fix is written to `build\dxgi.dll`. Copy it next to `FlightSimulator2024.exe` to try it.

## Offline test

No sim and no ReShade needed, but an NVIDIA GPU with Shader Model 6.6 is:

```powershell
powershell -ExecutionPolicy Bypass -File scripts\build.ps1 -Test
powershell -ExecutionPolicy Bypass -File scripts\test.ps1
```

The test runs the fix inside a fake `FlightSimulator2024.exe` that loads it as its `dxgi.dll` (from its own folder, as
the sim does), with stand-in display shaders and a fake DLSS that leaves worst-case ghosts, and checks the result pixel
by pixel against an unjittered reference.

## Release

```powershell
powershell -ExecutionPolicy Bypass -File scripts\package.ps1 -Version <version in src\version.h>
```

This creates `dist\dxgi.dll`, the file attached to the release. The GitHub Actions workflow
(`.github/workflows/build.yml`) builds the same file on every push and keeps it as a build artifact.
