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

- `coding/uicontrols/` — **主项目**：使用 Qt5 原生绘制开发的个人 UI 组件库，视觉对标 [Element Plus](https://element-plus.org/)，力求像素级还原
- `coding/practice/` — 早期练习项目，无实际作用，忽略即可
- `coding/todolist` — 计划功能清单（中文）
- Build outputs go to `<build-dir>/product/<project-name>/`

## Design

- 组件开发仅使用 Qt 原生 API（QPainter、QStyle），不依赖 QSS 外部样式表
- 设计参考：Element Plus 官方文档 https://element-plus.org/en-US/component/button.html
- 每个组件独立在一个子目录（如 `src/button/`），含 `.h`/`.cpp`

## Qt plugin deployment

- Reference: `3rd/Qt5/debug/plugins/qtdeploy.ps1` (PowerShell `deployPluginsIfQt`)
- To run a built exe, you need matching Qt DLLs + plugins (platforms, imageformats, styles) next to it
- Existing deployed runnable: `debug/product/practice/practice.exe`
- `qt.conf` at exe location needs `[Paths]` line for plugin discovery

## Adding a new sub-project

1. Create `coding/<name>/CMakeLists.txt` following the `practice` template
2. Add `add_subdirectory(<name>)` to `coding/CMakeLists.txt`
