# AGENTS.md

## Build system

- **CMake source root**: `coding/` — configure from there, not the repo root
- **C++17**, CMake 4.0 minimum
- **Generator**: Visual Studio 18 2026 (VS 2026 Community)
- **Architecture**: Win32 (x86), `/machine:X86`
- **Build dir**: `build/` — created by the configure step
- **vcpkg-managed Qt5**: vcpkg root at `D:/code/github/vcpkg`
- **Qt5 version**: 5.15.18, triplet: `x86-windows`
- `CMAKE_BUILD_TYPE` defaults to `Debug` if not set

## Configure

```powershell
cmake -S coding -B build -G "Visual Studio 18 2026" -A Win32
```

## Build

```powershell
cmake --build build --config Debug
```

## Projects

- `coding/uicontrols/` — **Primary project**: personal UI component library built with Qt5 native QPainter rendering, pixel-level visual fidelity to [Element Plus](https://element-plus.org/)
- Build outputs go to `<build-dir>/product/<project-name>/`

## Design

- Components use only Qt native APIs (QPainter, QStyle) — no QSS/CSS stylesheets
- Design reference: Element Plus official docs https://element-plus.org/zh-CN/component/button.html
- All new components use this site for API, visual effects, and state definitions
- Each component lives in its own subdirectory (e.g. `src/button/`), with `.h`/`.cpp`

## Theme System

- Global color/size tokens located in `src/theme/theme.h` (header-only)
- Usage: `#include "theme/theme.h"`, access via `theme::` namespace
- Color examples: `theme::buttonSolidBg(type, theme::kHover)`, `theme::tagLightBg(type)`
- Size examples: `theme::buttonSize(size)` returns `theme::SizeSpec`
- New components should source colors and sizes from theme to avoid duplicated color tables

## Language Rule

- All string literals in source code MUST be ASCII only
- Chinese/comments are allowed ONLY in `//` or `/* */` comment blocks
- No Chinese characters in string literals, variable names, section labels, or widget text
- UIs shown to users (testwidget demo pages, component labels, etc.) must use English ASCII strings

## Code style

- Follows [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html)
- PascalCase class names, `trailing_underscore_` member variables
- `k` prefix for enum values (`kPrimary`, `kLarge`)
- Include guard: `DIRNAME_FILENAME_H_` format
- File names all lowercase

## Encoding

- All `.cpp`/`.h` files must be UTF-8 with BOM and CRLF line endings
- Use `scripts/fix-encoding.ps1` to batch-convert all files:
  ```powershell
  pwsh -File scripts/fix-encoding.ps1
  ```

## Qt plugin deployment

- Reference: `3rd/Qt5/debug/plugins/qtdeploy.ps1` (PowerShell `deployPluginsIfQt`)
- To run a built exe, you need matching Qt DLLs + plugins (platforms, imageformats, styles) next to it
- Existing deployed runnable: `build/product/uicontrols/uicontrols.exe`
- `qt.conf` at exe location needs `[Paths]` line for plugin discovery

## Adding a new component

1. Create `coding/uicontrols/src/<name>/<name>.h` and `<name>.cpp`
2. Add source files to `coding/uicontrols/CMakeLists.txt` `SRC_FILES`
3. Add demo usage in `coding/uicontrols/src/testwidget.cpp`
