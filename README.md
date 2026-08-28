# qt-elements

[![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](LICENSE)
[![C++17](https://img.shields.io/badge/C%2B%2B-17-blue.svg)](https://en.cppreference.com/w/cpp/17)
[![Qt 5.15](https://img.shields.io/badge/Qt-5.15-green.svg)](https://www.qt.io/)
[![Platform: Windows](https://img.shields.io/badge/Platform-Windows-lightgrey.svg)]()

A personal UI component library for Qt5, built entirely with native QPainter rendering. Every component is designed to visually match [Element Plus](https://element-plus.org/) with pixel-level fidelity — no QSS, no CSS, pure Qt native APIs.

📖 **[Component Documentation](docs/README.md)** — per-component API reference, demo index, and a precise list of Element Plus features that are not implemented.

## ✨ Why qt-elements?

Most Qt custom widgets rely on stylesheets or hybrid approaches to achieve modern looks. qt-elements takes a different path: every pixel is drawn by `QPainter`, with exact color tokens sourced from Element Plus SCSS. The result is a component library that looks identical to Element Plus but runs natively in any Qt5 application.

## 🧩 Components

Full API reference for each: **[docs/README.md](docs/README.md)**.

| Component | Description |
|-----------|-------------|
| **[ZButton](docs/Button.md)** | 6 types, 5 variants (solid/plain/text/link/dashed), 3 sizes, round, circle, loading, disabled |
| **[ZTag](docs/Tag.md)** | 5 types, 3 effects (light/dark/plain), 3 sizes, closable, round, hit |
| **[ZBadge](docs/Badge.md)** | 5 types, dot mode, max value clamping, hidden state |
| **[ZDivider](docs/Divider.md)** | Horizontal/vertical, solid/dashed/dotted, text with left/center/right positioning |
| **[ZLink](docs/Link.md)** | 6 types, optional underline, hover state, click signal |
| **[ZText](docs/Text.md)** | 6 types, 3 sizes, single-line truncation |
| **[ZAlert](docs/Alert.md)** | 4 types, light/dark effects, closable, icon toggle, centered text |
| **[ZInput](docs/Input.md)** | 3 sizes, clearable, password toggle, textarea + autosize, prefix/suffix icons, prepend/append widgets, word limit |
| **[ZRadio](docs/Radio.md)** | Circular indicator with checked dot, border mode, hover/disabled states |
| **[ZCheckbox](docs/Checkbox.md)** | Square indicator with checkmark, indeterminate state, hover/disabled |
| **[ZCheckboxGroup](docs/CheckboxGroup.md)** | Integer multi-select model, min/max constraints, button style |
| **[ZSwitch](docs/Switch.md)** | Animated thumb slide, 3 sizes, loading spinner, active/inactive text |
| **[ZSlider](docs/Slider.md)** | Horizontal/vertical, drag-to-value, step snapping, stop markers |
| **[ZProgress](docs/Progress.md)** | Line/circle/dashboard, 4 status colors, text inside, indeterminate |
| **[ZTooltip](docs/Tooltip.md)** | Hover/manual trigger, dark/light effect, 4 placements, show/hide delays |

## 🚀 Quick Start

### Prerequisites

- **Visual Studio 2026** (Community) — C++ desktop workload
- **CMake 4.0+**
- **Qt 5.15.18** — managed via [vcpkg](https://github.com/microsoft/vcpkg)
- **vcpkg** root at `D:/code/github/vcpkg` (configurable in `CMakeLists.txt`)

### Build

```powershell
git clone https://github.com/zzlhyly/qt-elements.git
cd qt-elements

# Configure (Win32)
cmake -S coding -B build -G "Visual Studio 18 2026" -A Win32

# Build
cmake --build build --config Debug
```

The built executable is at `build/product/uicontrols/uicontrols.exe`. Qt DLLs and plugins are auto-deployed by CMake.

## 📁 Project Structure

```
qt-elements/
├── coding/                         # CMake source root
│   ├── CMakeLists.txt              # Top-level: vcpkg, Qt5, compiler config
│   └── uicontrols/                 # Component library
│       ├── CMakeLists.txt
│       ├── src/                    # Library + gallery shell
│       └── examples/               # One file per Element Plus demo
├── docs/                           # Per-component API documentation
├── build/                          # Build output (Win32, Debug)
├── scripts/                        # Utility scripts
│   └── fix-encoding.ps1            # UTF-8 BOM + CRLF converter
├── COMPONENTS.md                   # Tiered roadmap (40+ planned)
├── AGENTS.md                       # Project constitution & workflow
├── LICENSE                         # MIT
└── README.md
```

`src/` in detail:

```
src/
├── theme/theme.h       # Global color & size token system
├── style/style.h       # Visual style resolution
├── statemachine/       # StateTracker
├── painter/            # Painter helper functions
├── animation/          # AnimationManager
├── icon/               # IconManager
├── popup/              # ZPopup positioning engine
├── widgets/
│   ├── button/         # ZButton
│   ├── tag/            # ZTag
│   ├── input/          # ZInput
│   ├── link/           # ZLink
│   ├── alert/          # ZAlert
│   ├── text/           # ZText
│   ├── badge/          # ZBadge
│   ├── divider/        # ZDivider
│   ├── checkbox/       # ZCheckbox
│   ├── checkboxgroup/  # ZCheckboxGroup
│   ├── radio/          # ZRadio
│   ├── switch/         # ZSwitch
│   ├── progress/       # ZProgress
│   ├── slider/         # ZSlider
│   └── tooltip/        # ZTooltip
├── gallery.cpp         # Demo gallery shell (sidebar + stacked pages)
└── main.cpp
```

## 🎨 Design Principles

- **Zero QSS** — All visuals rendered with `QPainter`. No stylesheets, period.
- **Element Plus fidelity** — Colors, sizes, states, and effects match the [official component docs](https://element-plus.org/zh-CN/component/button.html) pixel-for-pixel.
- **Header-only theme** — `theme/theme.h` provides all color tokens and size specs. Every component references it — no duplicated color tables.
- **Google C++ Style** — `trailing_underscore_` members, `kEnumValue` naming, `DIRNAME_FILENAME_H_` guards, all-lowercase filenames.

## 🛠 Adding a Component

1. Create `coding/uicontrols/src/widgets/<name>/<name>.h` and `<name>.cpp`
2. Add both files to `coding/uicontrols/CMakeLists.txt` under `SRC_FILES`
3. Add one file per Element Plus demo to `coding/uicontrols/examples/<name>/`, each exposing a single `QWidget* Z<Name>Demo<Title>()` function — these are globbed into the build automatically, so no CMake edit is needed for demos
4. Add `<name>_demos.h` / `<name>_demos.cpp` in that same directory to register the demos with `DemoRegistry`, then call `Register<Name>Demos()` from `src/gallery.cpp`
5. Write `docs/<Name>.md` following the section template used by the existing pages
6. Update `COMPONENTS.md`, `docs/README.md` and both READMEs

See [`AGENTS.md`](AGENTS.md) for the mandatory per-component workflow and review checklist.

## 📄 License

MIT — see [LICENSE](LICENSE) for details.

---

[中文文档](README_CN.md)
