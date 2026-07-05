# QtProject

Qt5 C++ 练习项目集合，使用 CMake 和 vcpkg 构建。

## 环境要求

- **Visual Studio 2026** (Community)，需安装 C++ 工作负载
- **CMake** 4.0+
- **Qt 5.15.18**，通过 vcpkg 管理（triplet: `x86-windows`、`x64-windows`）
- **vcpkg** 位于 `D:/code/github/vcpkg`

## 快速开始

```powershell
# 克隆仓库
git clone <repo-url> qtproject
cd qtproject

# 配置 (x64)
cmake -S coding -B build -G "Visual Studio 18 2026"

# 配置 (Win32/x86)
cmake -S coding -B debug -G "Visual Studio 18 2026" -A Win32

# 构建
cmake --build build --config Debug
cmake --build debug --config Debug
```

> **注意：** `debug/` 目录是 Win32 (x86) 的构建目录，不仅仅是 Debug 配置。

## 运行

构建产物位于 `<build-dir>/product/<project-name>/`。运行前需要将 Qt DLL 和插件（platforms、imageformats、styles）部署到 exe 同级目录。

已部署的可运行文件：`debug/product/practice/practice.exe`。

插件部署逻辑参考 `3rd/Qt5/debug/plugins/qtdeploy.ps1`。

## 项目列表

| 项目 | 描述 |
|------|------|
| `coding/practice/` | 基础 Qt5 应用：自定义控件、信号/槽示例 |
| `coding/uicontrols/` | 自定义控件练习场（ZButton：多种尺寸、圆角样式） |

## 项目结构

```
qtproject/
├── coding/                  # 源码根目录（CMake 入口）
│   ├── CMakeLists.txt       # 顶层 CMake（vcpkg、Qt5 配置）
│   ├── practice/            # 练习项目
│   ├── uicontrols/          # UI 控件项目
│   └── todolist             # 计划功能清单
├── debug/                   # Win32 (x86) 构建目录
├── build/                   # x64 构建目录
├── 3rd/Qt5/                 # 预编译的 Qt5 二进制文件（部署用）
├── AGENTS.md                # 开发者/Agent 速查手册
└── README.md
```

## 添加新项目

1. 参考 `practice` 模版创建 `coding/<name>/CMakeLists.txt`
2. 在 `coding/CMakeLists.txt` 中添加 `add_subdirectory(<name>)`

## 许可证

[MIT](LICENSE)

---

[English](README.md)
