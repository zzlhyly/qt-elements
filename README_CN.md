# qt-elements

[![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](LICENSE)
[![C++17](https://img.shields.io/badge/C%2B%2B-17-blue.svg)](https://en.cppreference.com/w/cpp/17)
[![Qt 5.15](https://img.shields.io/badge/Qt-5.15-green.svg)](https://www.qt.io/)
[![Platform: Windows](https://img.shields.io/badge/Platform-Windows-lightgrey.svg)]()

基于 Qt5 原生 QPainter 绘制的个人 UI 组件库。所有组件视觉对标 [Element Plus](https://element-plus.org/)，力求像素级还原——不使用 QSS，不使用 CSS，纯 Qt 原生 API。

## ✨ 为什么选 qt-elements？

大多数 Qt 自定义控件依赖样式表或混合方案来实现现代外观。qt-elements 走了一条不同的路线：每个像素都由 `QPainter` 绘制，颜色标记直接来源于 Element Plus 的 SCSS 源码。最终呈现的组件库在视觉效果上与 Element Plus 完全一致，但可以在任何 Qt5 应用中原生运行。

## 🧩 组件列表

| 组件 | 描述 |
|------|------|
| **ZButton** | 6 种类型、3 种尺寸、5 种变体（solid/plain/text/link/dashed）、圆角/圆形、加载中、禁用 |
| **ZTag** | 5 种类型、3 种效果（light/dark/plain）、3 种尺寸、可关闭、圆角、边框 |
| **ZBadge** | 5 种类型、圆点模式、最大值显示、隐藏状态 |
| **ZDivider** | 水平/垂直、实线/虚线/点线、文字左/中/右定位 |
| **ZLink** | 6 种类型、悬停下划线/常驻下划线、悬停变色、点击信号 |
| **ZText** | 6 种类型、3 种尺寸、文字截断 |
| **ZInput** | 3 种尺寸、可清空、密码切换、聚焦/悬停状态、自定义边框渲染 |
| **ZRadio** | 圆形指示器 + 选中圆点、悬停/禁用状态 |
| **ZCheckbox** | 方形指示器 + 对勾标记、悬停/禁用状态 |
| **ZSwitch** | 滑块动画（200ms InOutCubic）、ON/OFF 颜色切换 |
| **ZSlider** | 水平滑块、拖拽调值、可配置范围 |
| **ZProgress** | 线条/圆环模式、4 种状态色、百分比文字 |
| **ZAlert** | 4 种类型、浅色/深色效果、可关闭、图标开关 |

## 🚀 快速开始

### 环境要求

- **Visual Studio 2026** (Community) — C++ 桌面开发工作负载
- **CMake 4.0+**
- **Qt 5.15.18** — 通过 [vcpkg](https://github.com/microsoft/vcpkg) 管理
- **vcpkg** 根目录位于 `D:/code/github/vcpkg`（可在 `CMakeLists.txt` 中修改）

### 构建

```powershell
git clone https://github.com/zzlhyly/qt-elements.git
cd qt-elements

# 配置 (Win32)
cmake -S coding -B build -G "Visual Studio 18 2026" -A Win32

# 构建
cmake --build build --config Debug
```

构建产物位于 `build/product/uicontrols/uicontrols.exe`。Qt DLL 和插件由 CMake 自动部署。

## 📁 项目结构

```
qt-elements/
├── coding/                         # CMake 源码根目录
│   ├── CMakeLists.txt              # 顶层：vcpkg、Qt5、编译器配置
│   └── uicontrols/                 # 组件库
│       ├── CMakeLists.txt
│       └── src/
│           ├── theme/theme.h       # 全局色彩与尺寸令牌系统
│           ├── testwidget.h/.cpp   # 组件展示浏览器
│           ├── button/             # ZButton
│           ├── tag/                # ZTag
│           ├── badge/              # ZBadge
│           ├── divider/            # ZDivider
│           ├── link/               # ZLink
│           ├── text/               # ZText
│           ├── input/              # ZInput
│           ├── radio/              # ZRadio
│           ├── checkbox/           # ZCheckbox
│           ├── switch/             # ZSwitch
│           ├── slider/             # ZSlider
│           └── progress/           # ZProgress
├── build/                          # 构建输出（Win32, Debug）
├── scripts/                        # 工具脚本
│   └── fix-encoding.ps1            # UTF-8 BOM + CRLF 转换器
├── COMPONENTS.md                   # 分层路线图（40+ 计划组件）
├── AGENTS.md                       # 开发者速查手册
├── LICENSE                         # MIT
└── README.md
```

## 🎨 设计原则

- **零 QSS** — 所有视觉由 `QPainter` 渲染。绝对不使用样式表。
- **Element Plus 像素级对标** — 颜色、尺寸、状态和效果与[官方组件文档](https://element-plus.org/zh-CN/component/button.html)逐像素匹配。
- **Header-only 主题系统** — `theme/theme.h` 提供所有色彩标记和尺寸规格。每个组件统一引用——无重复色表。
- **Google C++ 代码规范** — `trailing_underscore_` 成员变量、`kEnumValue` 枚举命名、`DIRNAME_FILENAME_H_` include guard、全小写文件名。

## 🛠 添加新组件

1. 创建 `coding/uicontrols/src/<name>/<name>.h` 和 `<name>.cpp`
2. 将两者加入 `coding/uicontrols/CMakeLists.txt` 的 `SRC_FILES`
3. 在 `testwidget.cpp` 中编写 `createXxxPage()` 展示函数
4. 在 `TestWidget` 构造函数的侧边栏和堆叠控件中注册
5. 更新 `COMPONENTS.md` 和两份 README

## 📄 许可证

MIT — 详见 [LICENSE](LICENSE)。

---

[English](README.md)
