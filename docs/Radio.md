# ZRadio

Element Plus reference: <https://element-plus.org/en-US/component/radio.html>

## Introduction

`ZRadio` is the Element Plus Radio button: a `QPainter`-drawn radio indicator
with an optional text label, plus an optional `border` mode that renders the
control inside a rounded box.

Exclusive selection is **not** implemented inside `ZRadio`; use Qt's
`QButtonGroup` (auto-exclusive by default) for that.

## Class Diagram

```
QObject
└── QWidget
    └── QAbstractButton
        └── ZRadio
              └── bool border_
```

Collaborators:

```
ZRadio ──uses──> painter::DrawBackground / DrawBorder / drawEllipse (indicator)
       ──uses──> theme::colorPrimary() / borderColor() / textRegular()
QButtonGroup (Qt, external) provides exclusive selection across ZRadio instances
```

## Public API

Header: `coding/uicontrols/src/widgets/radio/zradio.h`

### Properties (`Q_PROPERTY`)

| Property | Type | Default | Accessors |
|----------|------|---------|-----------|
| `border` | `bool` | `false` | `setBorder()` / `isBorder()` |

`text`, `checked`, `enabled` and `checkable` come from `QAbstractButton`.

### Constructors

```cpp
explicit ZRadio(QWidget* parent = nullptr);
ZRadio(const QString& text, QWidget* parent = nullptr);
```

### Size hint

```cpp
QSize sizeHint() const override;
```

### Signals

Inherited from `QAbstractButton`: `toggled(bool)`, `clicked(bool)`,
`pressed()`, `released()`.

### Reimplemented event handlers

`paintEvent`.

Keyboard activation (Space) and focus handling come from `QAbstractButton`.

## Demos

| Demo | Source |
|------|--------|
| Basic | [`basic.cpp`](../coding/uicontrols/examples/radio/basic.cpp) |
| Disabled | [`disabled.cpp`](../coding/uicontrols/examples/radio/disabled.cpp) |
| Vertical | [`vertical.cpp`](../coding/uicontrols/examples/radio/vertical.cpp) |
| With Borders | [`border.cpp`](../coding/uicontrols/examples/radio/border.cpp) |

## Supported Features

- checked / unchecked indicator drawn with `QPainter`
- optional text label
- `border` mode (boxed radio)
- disabled state
- keyboard activation and focus
- exclusive selection when placed in a `QButtonGroup`

## Unsupported Features

| Element Plus | Status |
|--------------|--------|
| `size` (`large` / `default` / `small`) | not implemented — one size |
| `value` / `label` as typed model values | model values live in `QButtonGroup` ids |
| Radio Button style (`el-radio-button`) | not implemented — see `ZCheckboxGroup` for the button-style pattern |
| `RadioGroup.fill` / `text-color` | not applicable without a group widget |
| `options` / `props` data-driven rendering | not implemented |
| `border` + group-level `size` cascading | no group widget, so no cascade |
| `name`, `validate-event`, `aria-label` | not applicable to Qt |

The official page lists six demos: Basic usage, Disabled, Radio Group, With
borders, Options attribute, and Radio Button. `ZRadio` covers three fully
(Basic, Disabled, With borders) and one via `QButtonGroup` (Radio Group).

## Differences from Element Plus

1. **No `ZRadioGroup`.** Element Plus has `<el-radio-group>` owning the model and
   cascading `size` / `disabled`. Qt already provides `QButtonGroup` for
   exclusivity and `QVBoxLayout` / `QHBoxLayout` for arrangement, so the
   composition is done by the caller instead of a library widget.
2. **Model values are integers.** Element Plus binds the radio's `value` into
   the group model; with `QButtonGroup`, each `ZRadio` is registered with an
   integer id via `QButtonGroup::addButton(button, id)`.
3. **No size variants.** The Element Plus `size` prop resizes the indicator and
   font; `ZRadio` has a single size driven by `theme::`.
4. **No button style.** `<el-radio-button>` renders a segmented control; the
   closest analogue in this library is `ZCheckboxGroup` with
   `GroupType::kButton`, which is a checkbox (multi-select) control.
5. **Border mode height.** `sizeHint()` accounts for the border box, but the
   box does not stretch to fill a layout like the CSS flex version does.

## Future Roadmap

- Size variants (`kLarge` / `kDefault` / `kSmall`)
- A `ZRadioGroup` container cascading `size`, `disabled` and `border`, with a
  `valueChanged(int)` signal
- Button style (`ZRadioButton`) rendering as a segmented control
- RTL mirroring of indicator and label order
