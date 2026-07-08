# ZCheckbox

## Introduction

ZCheckbox is a square selection indicator with checkmark and indeterminate state support.

## Public API

- `void setIndeterminate(bool)`, `bool isIndeterminate()`
- Inherits all QAbstractButton methods (setChecked, isChecked, toggled, etc.)
- Q_PROPERTY: `indeterminate`

## Demos
| Demo | File |
|------|------|
| Basic | `examples/checkbox/basic.cpp` |
| Disabled | `examples/checkbox/disabled.cpp` |
| Indeterminate | `examples/checkbox/indeterminate.cpp` |
| Button Style | `examples/checkbox/button_style.cpp` |
