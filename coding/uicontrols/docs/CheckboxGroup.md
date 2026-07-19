# ZCheckboxGroup

## Introduction

ZCheckboxGroup manages multiple ZCheckbox widgets as a group with exclusive/constrained selection, min/max limits, and button-style rendering.

## Public API

### Enums
| Enum | Values |
|------|--------|
| `GroupType` | `kDefault`, `kButton` |
| `Size` | `kDefault`, `kLarge`, `kSmall` |

- `void setValue(const QList<int>&)`, `QList<int> value()`
- `void addCheckbox(ZCheckbox*, int value)`
- `void setMin(int)`, `int min()` — minimum checked count
- `void setMax(int)`, `int max()` — maximum checked count
- `void setType(GroupType)`, `GroupType type()`
- `void setBorder(bool)`, `bool border()`
- `void setSize(Size)`, `Size size()`
- `void setDisabled(bool)`, `bool isDisabled()`
- Signal: `valueChanged(const QList<int>&)`

## Demos
| Demo | File |
|------|------|
| Group | `examples/checkbox/group.cpp` |
| Border | `examples/checkbox/border.cpp` |
