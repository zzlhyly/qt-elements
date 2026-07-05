# qt-elements

基于 Qt5 原生绘制（QPainter）的个人 UI 组件库，视觉对标 [Element Plus](https://element-plus.org/)，力求像素级还原。

## 环境要求

- **Visual Studio 2026** (Community)，需安装 C++ 工作负载
- **CMake** 4.0+
- **Qt 5.15.18**，通过 vcpkg 管理（triplet: `x86-windows`、`x64-windows`）
- **vcpkg** 位于 `D:/code/github/vcpkg`

## 快速开始

```powershell
# 克隆仓库
git clone <repo-url> qt-elements
cd qt-elements

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

已部署的可运行文件：`debug/product/uicontrols/uicontrols.exe`。

插件部署逻辑参考 `3rd/Qt5/debug/plugins/qtdeploy.ps1`。

## 组件列表

| 组件 | 状态 | 描述 |
|------|------|------|
| ZButton | ✅ 完成 | 完整 Element Plus 按钮：6 种类型、3 种尺寸、solid/plain/text 变体、圆角/圆形 |
| ZTag | ✅ 完成 | 完整 Element Plus 标签：5 种类型、3 种效果、3 种尺寸、可关闭/圆角/边框 |

## 项目结构

```
qt-elements/
├── coding/                    # 源码根目录（CMake 入口）
│   ├── CMakeLists.txt         # 顶层 CMake（vcpkg、Qt5 配置）
│   └── uicontrols/            # UI 组件库
│       ├── CMakeLists.txt
│       └── src/
│           ├── main.cpp
│           ├── testwidget.h/cpp  # 组件验收/展示窗口
│           └── button/
│               ├── zbutton.h
│               └── zbutton.cpp
├── debug/                     # Win32 (x86) 构建目录
├── build/                     # x64 构建目录
├── 3rd/Qt5/                   # 预编译的 Qt5 二进制文件（部署用）
├── AGENTS.md                  # 开发者速查手册
├── README.md
├── README_CN.md
└── LICENSE
```

## 设计理念

- 仅使用 Qt 原生 API（QPainter、QStyle），不依赖 QSS/CSS 样式表
- 设计参考：[Element Plus](https://element-plus.org/en-US/component/button.html)
- 每个组件独立存放于 `src/<name>/` 目录下

## 代码风格

遵循 [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html)：
- 类名 PascalCase，成员变量 `trailing_underscore_`
- 枚举值 `k` 前缀（`kPrimary`、`kLarge`）
- Include guard：`DIRNAME_FILENAME_H_` 格式
- 文件名全小写

## 添加新组件

1. 创建 `coding/uicontrols/src/<name>/<name>.h` 和 `<name>.cpp`
2. 将源文件加入 `coding/uicontrols/CMakeLists.txt` 的 `SRC_FILES`
3. 在 `coding/uicontrols/src/testwidget.cpp` 中添加展示代码

## 许可证

[MIT](LICENSE)

---

[English](README.md)
