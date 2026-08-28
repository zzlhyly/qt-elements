# ZCheckbox

Element Plus reference: <https://element-plus.org/en-US/component/checkbox.html>

## Introduction

`ZCheckbox` is the Element Plus Checkbox: a `QPainter`-drawn box indicator with
an optional text label and a third `indeterminate` (partially checked) state.

`ZCheckbox` covers the standalone control only. Multi-checkbox coordination
lives in [`ZCheckboxGroup`](CheckboxGroup.md).

## Class Diagram

```
QObject
└── QWidget
    └── QAbstractButton
        └── ZCheckbox
              └── bool indeterminate_
```

Collaborators:

```
ZCheckbox ──uses──> painter::DrawBackground / DrawBorder / DrawIcon (tick / dash)
          ──uses──> theme::colorPrimary() / borderColor() / textRegular()
ZCheckboxGroup (see CheckboxGroup.md) coordinates groups of ZCheckbox instances
```

## Public API

Header: `coding/uicontrols/src/widgets/checkbox/zcheckbox.h`

### Properties (`Q_PROPERTY`)

| Property | Type | Default | Accessors |
|----------|------|---------|-----------|
| `indeterminate` | `bool` | `false` | `setIndeterminate()` / `isIndeterminate()` |

`text`, `checked`, `enabled`, `checkable` and `tristate` come from
`QAbstractButton`.

### Constructors

```cpp
explicit ZCheckbox(QWidget* parent = nullptr);
ZCheckbox(const QString& text, QWidget* parent = nullptr);
```

### Size hint

```cpp
QSize sizeHint() const override;
```

### Signals

Inherited from `QAbstractButton`: `toggled(bool)`, `clicked(bool)`,
`stateChanged(int)`, `pressed()`, `released()`.

There is **no** dedicated `indeterminateChanged()` signal.

### Reimplemented event handlers

`paintEvent`, `nextCheckState()`.

`nextCheckState()` drives unchecked -> checked -> unchecked, and leaves
indeterminate to be set explicitly.

## Demos

| Demo | Source |
|------|--------|
| Basic | [`basic.cpp`](../coding/uicontrols/examples/checkbox/basic.cpp) |
| Disabled | [`disabled.cpp`](../coding/uicontrols/examples/checkbox/disabled.cpp) |
| Indeterminate | [`indeterminate.cpp`](../coding/uicontrols/examples/checkbox/indeterminate.cpp) |
| With Borders | [`border.cpp`](../coding/uicontrols/examples/checkbox/border.cpp) |
| Button Style | [`button_style.cpp`](../coding/uicontrols/examples/checkbox/button_style.cpp) |
| Group | [`group.cpp`](../coding/uicontrols/examples/checkbox/group.cpp) |

## Supported Features

- unchecked / checked / indeterminate tri-state rendering
- optional text label
- disabled state
- keyboard activation (Space) and focus via `QAbstractButton`
- grouping through `ZCheckboxGroup` or Qt's `QButtonGroup`

Note on the `With Borders` and `Button Style` demos: the `With Borders` demo sets
`ZCheckboxGroup::setBorder(true)` with `GroupType::kButton`, while the `Button
Style` demo groups plain `ZCheckbox` instances in a `QButtonGroup`. Neither uses
a `border` property on `ZCheckbox` itself — Element Plus has that property on
each checkbox plus dedicated `el-checkbox-button` styling, so the demos only
approximate the official look.

## Unsupported Features

| Element Plus | Status |
|--------------|--------|
| `border` prop | not implemented on `ZCheckbox`; see note above |
| `size` (`large` / `default` / `small`) | not implemented |
| `true-value` / `false-value` | not implemented — model is boolean |
| `checked` as an initial-only prop | maps to `QAbstractButton::setChecked()` |
| `validate-event`, `tabindex`, `id`, `aria-*` | not applicable to Qt |
| `change` event with the new value | `toggled(bool)` is the equivalent |

The official page lists eight demos: Basic usage, Disabled State, Checkbox group,
Options attribute, Indeterminate, Minimum / Maximum items checked, Button style,
and With borders. `ZCheckbox` plus `ZCheckboxGroup` cover six; `Options
attribute` (data-driven rendering) is not supported.

## Differences from Element Plus

1. **Indeterminate is purely visual.** Element Plus documents `indeterminate` as
   style control only — it does not compute tri-state for you — and `ZCheckbox`
   matches that: no parent/child propagation is performed.
2. **No typed model values.** Element Plus 2.6+ supports `true-value` /
   `false-value` so the model can hold non-boolean values; `ZCheckbox` is always
   boolean, and a group membership is expressed with integer values in
   `ZCheckboxGroup`.
3. **No `border` property.** The Element Plus `border` prop draws a rounded box
   around each checkbox. `ZCheckbox` has no such property; the closest
   equivalent is `ZCheckboxGroup::setBorder(true)`, which applies to every child
   of the group rather than to one checkbox.
4. **No size variants.** One size, driven by `theme::`.
5. **`button_style` demo is an approximation.** It groups `ZCheckbox` instances
   in a `QButtonGroup`; the segmented look of `el-checkbox-button` is not
   reproduced. `ZCheckboxGroup::GroupType::kButton` is the closer match.

## Future Roadmap

- `border` and `size` properties
- `Button style` rendering with active `fill` / `text-color`
- `trueValue` / `falseValue` support
- `indeterminateChanged()` signal
- RTL mirroring of indicator and label order
