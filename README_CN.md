# qt-elements

基于 Qt5 原生绘制（QPainter）的个人 UI 组件库，视觉对标 [Element Plus](https://element-plus.org/)，力求像素级还原。

## 环境要求

- **Visual Studio 2026** (Community)，需安装 C++ 工作负载
- **CMake** 4.0+
- **Qt 5.15.18**，通过 vcpkg 管理（triplet: `x86-windows`）
- **vcpkg** 位于 `D:/code/github/vcpkg`

## 快速开始

```powershell
# 克隆仓库
git clone <repo-url> qt-elements
cd qt-elements

# 配置 & 构建
cmake -S coding -B build -G "Visual Studio 18 2026" -A Win32
cmake --build build --config Debug
```

## 运行

构建产物位于 `build/product/<project-name>/`。Qt DLL 和插件由 CMake 自动部署。

已部署的可运行文件：`build/product/uicontrols/uicontrols.exe`。

## 组件列表

| 组件 | 状态 | 描述 |
|------|------|------|
| ZButton | ✅ 完成 | 完整 Element Plus 按钮：6 种类型、3 种尺寸、solid/plain/text 变体、圆角/圆形 |
| ZTag | ✅ 完成 | 完整 Element Plus 标签：5 种类型、3 种效果、3 种尺寸、可关闭/圆角/边框 |
| ZBadge | ✅ 完成 | 徽章组件：5 种类型、圆点模式、最大值显示 |
| ZDivider | ✅ 完成 | 分割线组件：水平/垂直方向、文字位置、边框样式 |
| ZLink | ✅ 完成 | 链接组件：6 种类型、悬停状态、下划线、点击信号 |
| ZText | ✅ 完成 | 文本组件：6 种类型、3 种尺寸、截断显示 |
| ZInput | ✅ 完成 | 输入框组件：3 种尺寸、可清空、密码切换、悬停/聚焦状态 |
| ZRadio | ✅ 完成 | 单选框组件：选中/悬停/禁用状态 |
| ZCheckbox | ✅ 完成 | 复选框组件：勾选标记、选中/悬停/禁用状态 |
| ZSwitch | ✅ 完成 | 开关组件：平滑滑块动画、禁用状态 |
| ZSlider | ✅ 完成 | 滑块组件：鼠标拖拽、数值范围、禁用状态 |
| ZProgress | ✅ 完成 | 进度条组件：线条/圆环、4 种状态色 |
| ZProgress | ✅ 完成 | 进度条组件：线条/圆环模式、4 种状态颜色、百分比文字 |

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
├── build/                     # 构建目录（Win32, Debug）
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
