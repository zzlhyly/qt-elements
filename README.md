# qt-elements

A personal UI component library built with Qt5 native drawing (QPainter), visually matching [Element Plus](https://element-plus.org/) with pixel-level fidelity.

## Prerequisites

- **Visual Studio 2026** (Community) with C++ workload
- **CMake** 4.0+
- **Qt 5.15.18** via vcpkg (triplet: `x86-windows`)
- **vcpkg** at `D:/code/github/vcpkg`

## Quick Start

```powershell
# Clone
git clone <repo-url> qt-elements
cd qt-elements

# Configure & Build
cmake -S coding -B build -G "Visual Studio 18 2026" -A Win32
cmake --build build --config Debug
```

> **Note:** `debug/` is the Win32 (x86) build directory, not just a debug configuration.

## Running

Built executables are placed under `build/product/<project-name>/`. Qt DLLs and plugins are auto-deployed by CMake.

A pre-deployed runnable exists at `build/product/uicontrols/uicontrols.exe`.

## Components

| Component | Status | Description |
|-----------|--------|-------------|
| ZButton | ✅ Done | Full Element Plus button: 6 types, 3 sizes, solid/plain/text variants, round/circle |
| ZTag | ✅ Done | Full Element Plus tag: 5 types, 3 effects, 3 sizes, closable/round/hit |
| ZBadge | ✅ Done | Badge with 5 types, dot mode, max value display |
| ZDivider | ✅ Done | Horizontal/vertical divider with text, position, border styles |
| ZLink | ✅ Done | Link with 6 types, hover state, underline, click signal |
| ZText | ✅ Done | Text with 6 types, 3 sizes, truncation support |
| ZInput | ✅ Done | Input with 3 sizes, clearable, password toggle, focus/hover states |
| ZRadio | ✅ Done | Radio button with checked/hover/disabled states |
| ZCheckbox | ✅ Done | Checkbox with checkmark, checked/hover/disabled states |
| ZSwitch | ✅ Done | Toggle switch with smooth thumb animation, disabled state |
| ZSlider | ✅ Done | Horizontal slider with mouse drag, value range, disabled state |
| ZProgress | ✅ Done | Line and circle progress bar, 4 status colors, percentage text |

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
├── build/                     # Build directory (Win32, Debug)
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
