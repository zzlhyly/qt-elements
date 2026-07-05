# AGENTS.md

## Build system

- **CMake source root**: `coding/` — configure from there, not the repo root
- **C++17**, CMake 4.0 minimum
- **Generator**: Visual Studio 18 2026 (VS 2026 Community)
- **Two build dirs serve different architectures**:
  - `debug/` — Win32 (x86), Debug config, `/machine:X86`
  - `build/` — x64, no explicit platform set (uses host default)
- **vcpkg-managed Qt5**: vcpkg root at `D:/code/github/vcpkg`
- **Qt5 version**: 5.15.18, triplets: `x86-windows` for Win32, `x64-windows` for x64
- `CMAKE_BUILD_TYPE` defaults to `Debug` if not set

## Configure

```powershell
cmake -S coding -B build -G "Visual Studio 18 2026"
cmake -S coding -B debug -G "Visual Studio 18 2026" -A Win32
```

## Build

```powershell
cmake --build build --config Debug
cmake --build debug --config Debug
```

## Projects

- `coding/practice/` — basic Qt5 app (QApplication + custom widget)
- `coding/uicontrols/` — Qt5 UI controls playground (buttons, test widgets)
- `coding/todolist` — planned features (Chinese)
- Build outputs go to `<build-dir>/product/<project-name>/`

## Qt plugin deployment

- Reference: `3rd/Qt5/debug/plugins/qtdeploy.ps1` (PowerShell `deployPluginsIfQt`)
- To run a built exe, you need matching Qt DLLs + plugins (platforms, imageformats, styles) next to it
- Existing deployed runnable: `debug/product/practice/practice.exe`
- `qt.conf` at exe location needs `[Paths]` line for plugin discovery

## Adding a new sub-project

1. Create `coding/<name>/CMakeLists.txt` following the `practice` template
2. Add `add_subdirectory(<name>)` to `coding/CMakeLists.txt`
