# ZSwitch

## Introduction

ZSwitch is a toggle switch with animated thumb slide, loading spinner, and label support.

## Public API

### Enums
| Enum | Values |
|------|--------|
| `SwitchSize` | `kLarge`, `kDefault`, `kSmall` |

- `void setSwitchSize(SwitchSize)`, `SwitchSize switchSize()`
- `void setLoading(bool)`, `bool isLoading()`
- `void setActiveText(const QString&)`, `QString activeText()`
- `void setInactiveText(const QString&)`, `QString inactiveText()`
- Q_PROPERTY: `switchSize`, `loading`, `activeText`, `inactiveText`

## Demos
| Demo | File |
|------|------|
| Basic | `examples/switch/basic.cpp` |
| Disabled | `examples/switch/disabled.cpp` |
| With Label | `examples/switch/with_label.cpp` |
| Sizes | `examples/switch/sizes.cpp` |
| Loading | `examples/switch/loading.cpp` |
