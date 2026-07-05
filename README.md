# qt-elements

A personal UI component library built with Qt5 native drawing (QPainter), visually matching [Element Plus](https://element-plus.org/) with pixel-level fidelity.

## Prerequisites

- **Visual Studio 2026** (Community) with C++ workload
- **CMake** 4.0+
- **Qt 5.15.18** via vcpkg (triplets: `x86-windows`, `x64-windows`)
- **vcpkg** at `D:/code/github/vcpkg`

## Quick Start

```powershell
# Clone
git clone <repo-url> qt-elements
cd qt-elements

# Configure (x64)
cmake -S coding -B build -G "Visual Studio 18 2026"

# Configure (Win32/x86)
cmake -S coding -B debug -G "Visual Studio 18 2026" -A Win32

# Build
cmake --build build --config Debug
cmake --build debug --config Debug
```

> **Note:** `debug/` is the Win32 (x86) build directory, not just a debug configuration.

## Running

Built executables are placed under `<build-dir>/product/<project-name>/`. Qt DLLs and plugins (platforms, imageformats, styles) must be deployed alongside the executable before running.

A pre-deployed runnable exists at `debug/product/uicontrols/uicontrols.exe`.

For plugin deployment logic, see `3rd/Qt5/debug/plugins/qtdeploy.ps1`.

## Components

| Component | Status | Description |
|-----------|--------|-------------|
| ZButton | ✅ Done | Full Element Plus button: 6 types, 3 sizes, solid/plain/text variants, round/circle |
| ZTag | ✅ Done | Full Element Plus tag: 5 types, 3 effects, 3 sizes, closable/round/hit |

## Project Structure

```
qt-elements/
├── coding/                    # Source root (CMake entry point)
│   ├── CMakeLists.txt         # Top-level CMake (vcpkg, Qt5 config)
│   └── uicontrols/            # UI component library
│       ├── CMakeLists.txt
│       └── src/
│           ├── main.cpp
│           ├── testwidget.h/cpp  # Component demo/showcase window
│           └── button/
│               ├── zbutton.h
│               └── zbutton.cpp
├── debug/                     # Win32 (x86) build directory
├── build/                     # x64 build directory
├── 3rd/Qt5/                   # Pre-built Qt5 binaries for deployment
├── AGENTS.md                  # Agent/contributor quick reference
├── README.md
├── README_CN.md
└── LICENSE
```

## Design

- Components use only Qt native APIs (QPainter, QStyle) — no QSS/CSS stylesheets
- Design reference: [Element Plus](https://element-plus.org/en-US/component/button.html)
- Each component lives in its own subdirectory under `src/<name>/`

## Code Style

Follows [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html):
- PascalCase class names, `trailing_underscore_` member variables
- `k` prefix for enum values (`kPrimary`, `kLarge`)
- `DIRNAME_FILENAME_H_` include guards
- All-lowercase file names

## Adding a New Component

1. Create `coding/uicontrols/src/<name>/<name>.h` and `<name>.cpp`
2. Add source files to `coding/uicontrols/CMakeLists.txt` `SRC_FILES`
3. Add demo usage in `coding/uicontrols/src/testwidget.cpp`

## License

[MIT](LICENSE)

---

[中文版](README_CN.md)
