# Component Roadmap

Element Plus 组件适配路线图，按 Tier 0-5 依赖关系排列。

## Legend

| 标记 | 含义 |
|------|------|
| ✅ | 已完成 |
| 🔴 | 高优先级（下一批） |
| 🟡 | 中优先级 |
| 🟢 | 低优先级 |
| ⬜ | 尚未开始 |

---

## Tier 0 — Infrastructure（基础设施，所有组件依赖）

| 组件 | 参考 | 优先级 | 状态 | 依赖 | 预估 |
|------|------|--------|------|------|------|
| Theme System (色彩/尺寸令牌) | — | 🔴 | ✅ | — | 2h |
| Icon System | — | 🟡 | ⬜ | — | 2h |

## Tier 1 — Simple Leaf（简单叶节点，无依赖或仅依赖 Theme）

| 组件 | 参考 | 优先级 | 状态 | 依赖 | 预估 |
|------|------|--------|------|------|------|
| [Button](https://element-plus.org/en-US/component/button.html) | 按钮 | — | ✅ | — | — |
| [Tag](https://element-plus.org/en-US/component/tag.html) | 标签 | 🔴 | ⬜ | Theme | 2h |
| [Badge](https://element-plus.org/en-US/component/badge.html) | 徽章 | 🟡 | ⬜ | Theme | 1h |
| [Divider](https://element-plus.org/en-US/component/divider.html) | 分割线 | 🟢 | ⬜ | — | 0.5h |
| [Link](https://element-plus.org/en-US/component/link.html) | 链接 | 🟢 | ⬜ | — | 1h |
| [Text](https://element-plus.org/en-US/component/text.html) | 文本 | 🟢 | ⬜ | — | 1h |
| [Alert](https://element-plus.org/en-US/component/alert.html) | 警告 | 🟡 | ⬜ | Theme, Icon | 2h |
| [Avatar](https://element-plus.org/en-US/component/avatar.html) | 头像 | 🟢 | ⬜ | Theme | 1.5h |

## Tier 2 — Core Form（核心表单，依赖 Theme + Icon）

| 组件 | 参考 | 优先级 | 状态 | 依赖 | 预估 |
|------|------|--------|------|------|------|
| [Input](https://element-plus.org/en-US/component/input.html) | 输入框 | 🔴 | ⬜ | Theme, Icon | 8h |
| [Radio](https://element-plus.org/en-US/component/radio.html) | 单选框 | 🔴 | ⬜ | Theme | 3h |
| [Checkbox](https://element-plus.org/en-US/component/checkbox.html) | 多选框 | 🔴 | ⬜ | Theme | 3h |
| [Switch](https://element-plus.org/en-US/component/switch.html) | 开关 | 🟡 | ⬜ | Theme | 3h |
| [Slider](https://element-plus.org/en-US/component/slider.html) | 滑块 | 🟢 | ⬜ | Theme | 4h |
| [Rate](https://element-plus.org/en-US/component/rate.html) | 评分 | 🟢 | ⬜ | Theme, Icon | 3h |
| [Upload](https://element-plus.org/en-US/component/upload.html) | 上传 | 🟡 | ⬜ | Button, Icon | 6h |
| [Progress](https://element-plus.org/en-US/component/progress.html) | 进度条 | 🟢 | ⬜ | Theme | 2h |

## Tier 3 — Overlay System（浮层系统，依赖 Popup 定位引擎）

| 组件 | 参考 | 优先级 | 状态 | 依赖 | 预估 |
|------|------|--------|------|------|------|
| Popup/Overlay 定位引擎 | — | 🔴 | ⬜ | Theme | 4h |
| [Select](https://element-plus.org/en-US/component/select.html) | 选择器 | 🔴 | ⬜ | Input, Popup | 8h |
| [Tooltip](https://element-plus.org/en-US/component/tooltip.html) | 提示 | 🟡 | ⬜ | Popup | 3h |
| [Popover](https://element-plus.org/en-US/component/popover.html) | 气泡卡片 | 🟡 | ⬜ | Popup | 3h |
| [Dropdown](https://element-plus.org/en-US/component/dropdown.html) | 下拉菜单 | 🟡 | ⬜ | Popup, Button | 4h |
| [Menu](https://element-plus.org/en-US/component/menu.html) | 导航菜单 | 🟡 | ⬜ | Popup | 6h |
| [Cascader](https://element-plus.org/en-US/component/cascader.html) | 级联选择 | 🟢 | ⬜ | Select, Popup | 8h |
| [DatePicker](https://element-plus.org/en-US/component/date-picker.html) | 日期选择 | 🟡 | ⬜ | Input, Popup | 12h |
| [TimePicker](https://element-plus.org/en-US/component/time-picker.html) | 时间选择 | 🟢 | ⬜ | Input, Popup | 8h |
| [ColorPicker](https://element-plus.org/en-US/component/color-picker.html) | 颜色选择 | 🟢 | ⬜ | Popup | 6h |

## Tier 4 — Composite（组合容器，依赖 Tier 1-3）

| 组件 | 参考 | 优先级 | 状态 | 依赖 | 预估 |
|------|------|--------|------|------|------|
| [Dialog](https://element-plus.org/en-US/component/dialog.html) | 对话框 | 🔴 | ⬜ | Button, Popup | 4h |
| [Drawer](https://element-plus.org/en-US/component/drawer.html) | 抽屉 | 🟡 | ⬜ | Popup | 4h |
| [Tabs](https://element-plus.org/en-US/component/tabs.html) | 标签页 | 🔴 | ⬜ | Theme | 4h |
| [Card](https://element-plus.org/en-US/component/card.html) | 卡片 | 🟢 | ⬜ | Theme | 2h |
| [Collapse](https://element-plus.org/en-US/component/collapse.html) | 折叠面板 | 🟢 | ⬜ | Theme | 3h |
| [Timeline](https://element-plus.org/en-US/component/timeline.html) | 时间线 | 🟢 | ⬜ | Theme | 3h |
| [Steps](https://element-plus.org/en-US/component/steps.html) | 步骤条 | 🟡 | ⬜ | Theme | 3h |
| [Breadcrumb](https://element-plus.org/en-US/component/breadcrumb.html) | 面包屑 | 🟢 | ⬜ | — | 2h |
| [Pagination](https://element-plus.org/en-US/component/pagination.html) | 分页 | 🟡 | ⬜ | Button, Input | 4h |

## Tier 5 — Complex（重量级，多子系统协作）

| 组件 | 参考 | 优先级 | 状态 | 依赖 | 预估 |
|------|------|--------|------|------|------|
| [Table](https://element-plus.org/en-US/component/table.html) | 表格 | 🟡 | ⬜ | Checkbox, Pagination, Popup | 20h |
| [Tree](https://element-plus.org/en-US/component/tree.html) | 树形控件 | 🟢 | ⬜ | Checkbox | 12h |
| [Transfer](https://element-plus.org/en-US/component/transfer.html) | 穿梭框 | 🟢 | ⬜ | Checkbox, Button, Input | 8h |
| [Form](https://element-plus.org/en-US/component/form.html) | 表单 | 🔴 | ⬜ | Input, Radio, Checkbox, Switch | 8h |
| [Carousel](https://element-plus.org/en-US/component/carousel.html) | 走马灯 | 🟢 | ⬜ | — | 6h |
| [Skeleton](https://element-plus.org/en-US/component/skeleton.html) | 骨架屏 | 🟢 | ⬜ | Theme | 3h |
| [Calendar](https://element-plus.org/en-US/component/calendar.html) | 日历 | 🟢 | ⬜ | DatePicker | 12h |
| [Empty](https://element-plus.org/en-US/component/empty.html) | 空状态 | 🟢 | ⬜ | Theme | 1h |
| [Result](https://element-plus.org/en-US/component/result.html) | 结果 | 🟢 | ⬜ | Theme, Icon | 1h |
| [Descriptions](https://element-plus.org/en-US/component/descriptions.html) | 描述列表 | 🟢 | ⬜ | Theme | 3h |

---

## 不在计划内 (Not Applicable)

以下 Element Plus 组件在 Qt 环境下由原生控件直接覆盖，不需要自定义实现：

| 组件 | 原因 |
|------|------|
| Container / Layout | Qt 布局系统 (QVBoxLayout 等) 原生支持 |
| Scrollbar | QScrollArea 原生滚动条 |
| Space | QSpacerItem / layout spacing |
| Image | QLabel + QPixmap 即可 |
| InfiniteScroll | 应用层逻辑，非控件 |
| ConfigProvider | CMake / 代码配置替代 |
| Watermark | 应用层叠加，非独立控件 |
| Tour | 应用层引导逻辑 |
| Affix / Backtop | 滚动联动逻辑，非独立控件 |
