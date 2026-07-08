# qt-elements

[![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](LICENSE)
[![C++17](https://img.shields.io/badge/C%2B%2B-17-blue.svg)](https://en.cppreference.com/w/cpp/17)
[![Qt 5.15](https://img.shields.io/badge/Qt-5.15-green.svg)](https://www.qt.io/)
[![Platform: Windows](https://img.shields.io/badge/Platform-Windows-lightgrey.svg)]()

A personal UI component library for Qt5, built entirely with native QPainter rendering. Every component is designed to visually match [Element Plus](https://element-plus.org/) with pixel-level fidelity — no QSS, no CSS, pure Qt native APIs.

## ✨ Why qt-elements?

Most Qt custom widgets rely on stylesheets or hybrid approaches to achieve modern looks. qt-elements takes a different path: every pixel is drawn by `QPainter`, with exact color tokens sourced from Element Plus SCSS. The result is a component library that looks identical to Element Plus but runs natively in any Qt5 application.

## 🧩 Components

| Component | Description |
|-----------|-------------|
| **ZButton** | 6 types, 3 sizes, 5 variants (solid/plain/text/link/dashed), round, circle, loading, disabled |
| **ZTag** | 5 types, 3 effects (light/dark/plain), 3 sizes, closable, round, hit |
| **ZBadge** | 5 types, dot mode, max value display, hidden state |
| **ZDivider** | Horizontal/vertical, solid/dashed/dotted, text with left/center/right positioning |
| **ZLink** | 6 types, underline on hover/always, hover state, click signal |
| **ZText** | 6 types, 3 sizes, text truncation |
| **ZInput** | 3 sizes, clearable, password toggle, focus/hover states, custom border rendering |
| **ZRadio** | Circular indicator with checked dot, hover/disabled states |
| **ZCheckbox** | Square indicator with checkmark, hover/disabled states |
| **ZSwitch** | Animated thumb slide (200ms InOutCubic), ON/OFF color states |
| **ZSlider** | Horizontal slider with drag-to-value, configurable range |
| **ZProgress** | Line bar + circle ring modes, 4 status colors, percentage text |
| **ZAlert** | 4 types, light/dark effects, closable, icon toggle |
| **ZTooltip** | Hover tooltip with 500ms delay, static showText, popup overlay engine |

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
│       └── src/
│           ├── theme/theme.h       # Global color & size token system
│           ├── style/style.h        # Visual style resolution
│           ├── statemachine/        # StateTracker
│           ├── painter/             # Painter helper functions
│           ├── animation/           # AnimationManager
│           ├── icon/                # IconManager
│           ├── widgets/
│           │   ├── button/          # ZButton
│           │   ├── tag/             # ZTag
│           │   ├── input/           # ZInput
│           │   ├── link/            # ZLink
│           │   ├── alert/           # ZAlert
│           │   ├── text/            # ZText
│           │   ├── badge/           # ZBadge
│           │   └── divider/         # ZDivider
│           ├── radio/               # ZRadio
│           ├── checkbox/            # ZCheckbox
│           ├── switch/              # ZSwitch
│           ├── slider/              # ZSlider
│           ├── progress/            # ZProgress
│           ├── popup/               # ZPopup
│           └── tooltip/             # ZTooltip
├── build/                          # Build output (Win32, Debug)
├── scripts/                        # Utility scripts
│   └── fix-encoding.ps1            # UTF-8 BOM + CRLF converter
├── COMPONENTS.md                   # Tiered roadmap (40+ planned)
├── AGENTS.md                       # Developer quick reference
├── LICENSE                         # MIT
└── README.md
```

## 🎨 Design Principles

- **Zero QSS** — All visuals rendered with `QPainter`. No stylesheets, period.
- **Element Plus fidelity** — Colors, sizes, states, and effects match the [official component docs](https://element-plus.org/zh-CN/component/button.html) pixel-for-pixel.
- **Header-only theme** — `theme/theme.h` provides all color tokens and size specs. Every component references it — no duplicated color tables.
- **Google C++ Style** — `trailing_underscore_` members, `kEnumValue` naming, `DIRNAME_FILENAME_H_` guards, all-lowercase filenames.

## 🛠 Adding a Component

1. Create `coding/uicontrols/src/<name>/<name>.h` and `<name>.cpp`
2. Add both files to `coding/uicontrols/CMakeLists.txt` under `SRC_FILES`
3. Build a demo page function `createXxxPage()` in `testwidget.cpp`
4. Register it in the sidebar and stacked widget in `TestWidget` constructor
5. Update `COMPONENTS.md` and both READMEs

## 📄 License

MIT — see [LICENSE](LICENSE) for details.

---

[中文文档](README_CN.md)
