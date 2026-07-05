# QtProject

A collection of Qt5 C++ practice projects using CMake and vcpkg.

## Prerequisites

- **Visual Studio 2026** (Community) with C++ workload
- **CMake** 4.0+
- **Qt 5.15.18** via vcpkg (triplets: `x86-windows`, `x64-windows`)
- **vcpkg** at `D:/code/github/vcpkg`

## Quick Start

```powershell
# Clone
git clone <repo-url> qtproject
cd qtproject

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

A pre-deployed runnable exists at `debug/product/practice/practice.exe`.

For plugin deployment logic, see `3rd/Qt5/debug/plugins/qtdeploy.ps1`.

## Projects

| Project | Description |
|---------|-------------|
| `coding/practice/` | Basic Qt5 app with custom widget, signal/slot demo |
| `coding/uicontrols/` | Custom UI controls playground (ZButton: sizes, shapes) |

## Project Structure

```
qtproject/
├── coding/                  # Source root (CMake entry point)
│   ├── CMakeLists.txt       # Top-level CMake (vcpkg, Qt5 config)
│   ├── practice/            # Practice project
│   ├── uicontrols/          # UI controls project
│   └── todolist             # Planned features
├── debug/                   # Win32 (x86) build directory
├── build/                   # x64 build directory
├── 3rd/Qt5/                 # Pre-built Qt5 binaries for deployment
├── AGENTS.md                # Agent/contributor quick reference
└── README.md
```

## Adding a New Project

1. Create `coding/<name>/CMakeLists.txt` following the `practice` template
2. Add `add_subdirectory(<name>)` to `coding/CMakeLists.txt`

## License

[MIT](LICENSE)

---

[中文版](README_CN.md)
