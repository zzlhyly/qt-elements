# qt-elements

[![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](LICENSE)
[![C++17](https://img.shields.io/badge/C%2B%2B-17-blue.svg)](https://en.cppreference.com/w/cpp/17)
[![Qt 5.15](https://img.shields.io/badge/Qt-5.15-green.svg)](https://www.qt.io/)
[![Platform: Windows](https://img.shields.io/badge/Platform-Windows-lightgrey.svg)]()

基于 Qt5 原生 QPainter 绘制的个人 UI 组件库。所有组件视觉对标 [Element Plus](https://element-plus.org/)，力求像素级还原——不使用 QSS，不使用 CSS，纯 Qt 原生 API。

📖 **[组件文档](docs/README.md)** — 逐个组件的 API 参考、Demo 索引，以及未实现的 Element Plus 特性清单。

## ✨ 为什么选 qt-elements？

大多数 Qt 自定义控件依赖样式表或混合方案来实现现代外观。qt-elements 走了一条不同的路线：每个像素都由 `QPainter` 绘制，颜色标记直接来源于 Element Plus 的 SCSS 源码。最终呈现的组件库在视觉效果上与 Element Plus 完全一致，但可以在任何 Qt5 应用中原生运行。

## 🧩 组件列表

完整 API 参考见：**[docs/README.md](docs/README.md)**。

| 组件 | 描述 |
|------|------|
| **[ZButton](docs/Button.md)** | 6 种类型、5 种变体（solid/plain/text/link/dashed）、3 种尺寸、圆角/圆形、加载中、禁用 |
| **[ZTag](docs/Tag.md)** | 5 种类型、3 种效果（light/dark/plain）、3 种尺寸、可关闭、圆角、高亮边框 |
| **[ZBadge](docs/Badge.md)** | 5 种类型、圆点模式、最大值截顶显示、隐藏状态 |
| **[ZDivider](docs/Divider.md)** | 水平/垂直、实线/虚线/点线、文字左/中/右定位 |
| **[ZLink](docs/Link.md)** | 6 种类型、可选下划线、悬停变色、点击信号 |
| **[ZText](docs/Text.md)** | 6 种类型、3 种尺寸、单行截断 |
| **[ZAlert](docs/Alert.md)** | 4 种类型、浅色/深色效果、可关闭、图标开关、文字居中 |
| **[ZInput](docs/Input.md)** | 3 种尺寸、可清空、密码切换、多行文本域与自适应高度、前缀/后缀图标、前置/后置控件、字数统计 |
| **[ZRadio](docs/Radio.md)** | 圆形指示器 + 选中圆点、边框模式、悬停/禁用状态 |
| **[ZCheckbox](docs/Checkbox.md)** | 方形指示器 + 对勾标记、半选状态、悬停/禁用 |
| **[ZCheckboxGroup](docs/CheckboxGroup.md)** | 整型多选模型、min/max 数量约束、按钮风格 |
| **[ZSwitch](docs/Switch.md)** | 滑块平移动画、3 种尺寸、加载中、开/关文字 |
| **[ZSlider](docs/Slider.md)** | 水平/垂直、拖拽调值、步进吸附、断点标记 |
| **[ZProgress](docs/Progress.md)** | 线条/圆环/仪表盘、4 种状态色、文字内置、不确定态动画 |
| **[ZTooltip](docs/Tooltip.md)** | 悬停/手动触发、深色/浅色效果、4 个方位、显示/隐藏延迟 |

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
│       ├── src/                    # 组件库 + 展示器外壳
│       └── examples/               # 每个 Element Plus 示例一个文件
├── docs/                           # 逐组件 API 文档
├── build/                          # 构建输出（Win32, Debug）
├── scripts/                        # 工具脚本
│   └── fix-encoding.ps1            # UTF-8 BOM + CRLF 转换器
├── COMPONENTS.md                   # 分层路线图（40+ 计划组件）
├── AGENTS.md                       # 项目规约与开发流程
├── LICENSE                         # MIT
└── README.md
```

`src/` 详细结构：

```
src/
├── theme/theme.h       # 全局色彩与尺寸令牌系统
├── style/style.h       # 视觉样式解析
├── statemachine/       # StateTracker 状态机
├── painter/            # Painter 辅助函数
├── animation/          # AnimationManager 动画管理
├── icon/               # IconManager 图标管理
├── popup/              # ZPopup 定位引擎
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
├── gallery.cpp         # 展示器外壳（侧边栏 + 堆叠页面）
└── main.cpp
```

## 🎨 设计原则

- **零 QSS** — 所有视觉由 `QPainter` 渲染。绝对不使用样式表。
- **Element Plus 像素级对标** — 颜色、尺寸、状态和效果与[官方组件文档](https://element-plus.org/zh-CN/component/button.html)逐像素匹配。
- **Header-only 主题系统** — `theme/theme.h` 提供所有色彩标记和尺寸规格。每个组件统一引用——无重复色表。
- **Google C++ 代码规范** — `trailing_underscore_` 成员变量、`kEnumValue` 枚举命名、`DIRNAME_FILENAME_H_` include guard、全小写文件名。

## 🛠 添加新组件

1. 创建 `coding/uicontrols/src/widgets/<name>/<name>.h` 和 `<name>.cpp`
2. 将两者加入 `coding/uicontrols/CMakeLists.txt` 的 `SRC_FILES`
3. 在 `coding/uicontrols/examples/<name>/` 下按 Element Plus 官方示例逐个建文件，每个文件只暴露一个 `QWidget* Z<Name>Demo<Title>()` 函数——示例目录由 CMake 自动 glob，无需改动 CMakeLists
4. 在同一目录补充 `<name>_demos.h` / `<name>_demos.cpp`，将示例注册进 `DemoRegistry`，并在 `src/gallery.cpp` 中调用 `Register<Name>Demos()`
5. 按既有页面的章节模板编写 `docs/<Name>.md`
6. 更新 `COMPONENTS.md`、`docs/README.md` 和两份 README

每个组件的强制开发流程与评审清单见 [`AGENTS.md`](AGENTS.md)。

## 📄 许可证

MIT — 详见 [LICENSE](LICENSE)。

---

[English](README.md)
