# ZButton

Element Plus reference: <https://element-plus.org/en-US/component/button.html>

## Introduction

`ZButton` is the Element Plus Button control rendered entirely with `QPainter`.
It is a `QAbstractButton` subclass, so it inherits Qt's `clicked()`, keyboard
activation (Space / Enter), and focus handling, while all pixels are drawn by
the painter layer.

A button is described by three orthogonal axes plus two shape flags:

| Axis | Values |
|------|--------|
| `ButtonType` | `kDefault`, `kPrimary`, `kSuccess`, `kWarning`, `kDanger`, `kInfo` |
| `ButtonVariant` | `kSolid`, `kPlain`, `kText`, `kLink`, `kDashed` |
| `ButtonSize` | `kLarge`, `kMedium`, `kSmall` |
| shape | `round` (pill), `circle` (square, icon-only) |

Visual resolution is a pure function of `(type, state, variant, shape, size)` in
`style::ResolveButton()`; `paintEvent` contains no colour or layout logic.

## Class Diagram

```
QObject
└── QWidget
    └── QAbstractButton
        └── ZButton
              ├── ButtonType    type_
              ├── ButtonVariant variant_
              ├── ButtonSize    size_
              ├── bool          round_ / circle_ / loading_
              └── qreal         loading_angle_
```

Collaborators:

```
ZButton ──uses──> statemachine::StateTracker  hover / pressed / focused / disabled
        ──uses──> style::ResolveButton()      (type x state x variant) -> ButtonVisuals
        ──uses──> painter::DrawBackground / DrawBorder / DrawText / DrawIcon / DrawFocusRing
        ──uses──> theme::buttonSolidBg() …    all colour tokens
        ──uses──> AnimationManager            loading spinner rotation
```

## Public API

Header: `coding/uicontrols/src/widgets/button/zbutton.h`

### Enums

| Enum | Values |
|------|--------|
| `ButtonType` | `kDefault`, `kPrimary`, `kSuccess`, `kWarning`, `kDanger`, `kInfo` |
| `ButtonSize` | `kLarge`, `kMedium`, `kSmall` |
| `ButtonVariant` | `kSolid`, `kPlain`, `kText`, `kLink`, `kDashed` |

### Properties (`Q_PROPERTY`)

| Property | Type | Accessors |
|----------|------|-----------|
| `buttonType` | `ButtonType` | `setButtonType()` / `buttonType()` |
| `buttonSize` | `ButtonSize` | `setButtonSize()` / `buttonSize()` |
| `buttonVariant` | `ButtonVariant` | `setButtonVariant()` / `buttonVariant()` |
| `round` | `bool` | `setRound()` / `isRound()` |
| `circle` | `bool` | `setCircle()` / `isCircle()` |
| `loading` | `bool` | `setLoading()` / `isLoading()` |

`text`, `icon`, `enabled`, `checkable` and `checked` are inherited from
`QAbstractButton`.

### Constructors

```cpp
explicit ZButton(QWidget* parent = nullptr);
ZButton(const QString& text, QWidget* parent = nullptr);
```

### Size hints

```cpp
QSize sizeHint() const override;
QSize minimumSizeHint() const override;
```

### Signals

Inherited from `QAbstractButton`: `clicked(bool)`, `pressed()`, `released()`,
`toggled(bool)`.

### Slots

Inherited from `QAbstractButton`: `click()`, `animateClick()`, `toggle()`,
`setChecked()`, `setEnabled()`.

### Reimplemented event handlers

`paintEvent`, `enterEvent`, `leaveEvent`, `focusInEvent`, `mousePressEvent`,
`keyPressEvent`, `changeEvent`.

## Demos

| Demo | Source |
|------|--------|
| Basic | [`basic.cpp`](../coding/uicontrols/examples/button/basic.cpp) |
| Plain | [`plain.cpp`](../coding/uicontrols/examples/button/plain.cpp) |
| Round | [`round.cpp`](../coding/uicontrols/examples/button/round.cpp) |
| Circle | [`circle.cpp`](../coding/uicontrols/examples/button/circle.cpp) |
| Dashed | [`dashed.cpp`](../coding/uicontrols/examples/button/dashed.cpp) |
| Disabled | [`disabled.cpp`](../coding/uicontrols/examples/button/disabled.cpp) |
| Link | [`link.cpp`](../coding/uicontrols/examples/button/link.cpp) |
| Text | [`text.cpp`](../coding/uicontrols/examples/button/text.cpp) |
| Loading | [`loading.cpp`](../coding/uicontrols/examples/button/loading.cpp) |
| Size | [`size.cpp`](../coding/uicontrols/examples/button/size.cpp) |
| Icon | [`icon.cpp`](../coding/uicontrols/examples/button/icon.cpp) |
| Button Group | [`button_group.cpp`](../coding/uicontrols/examples/button/button_group.cpp) |
| Color | [`color.cpp`](../coding/uicontrols/examples/button/color.cpp) |

## Supported Features

- 6 types x 5 variants x 3 sizes
- round and circle shapes
- loading state with a continuously rotating arc, width preserved
- hover / pressed / focus-ring / disabled states via `StateTracker`
- keyboard activation (Space / Enter) and focus outline
- high-DPI rendering; all metrics and colours from `theme::`
- `QButtonGroup` interoperability for grouped toggle buttons

## Unsupported Features

Features present in Element Plus but **not** implemented:

| Element Plus | Status |
|--------------|--------|
| `auto-insert-space` (space between two CJK glyphs) | not implemented |
| `tag` (render as a non-`button` element) | not applicable to Qt |
| `native-type` (`submit` / `reset`) | not applicable to Qt |
| `loading-icon` / `icon` as SVG component references | use `setIcon(QIcon)` instead |
| `dark` (auto dark-mode derivation of a custom `color`) | not implemented |
| `bg` (solid background in `text` variant) | not implemented |
| `ButtonGroup.direction` (vertical groups) | use `QButtonGroup` + a `QVBoxLayout` |

## Differences from Element Plus

1. **Variant modelled as an enum, not booleans.** Element Plus uses independent
   `plain` / `text` / `link` / `bg` / `dashed` booleans that can be combined;
   `ZButton` uses one exclusive `ButtonVariant`, so combinations such as
   `plain + text` are not expressible.
2. **No dedicated group widget.** Element Plus has `<el-button-group>`; Qt
   already provides `QButtonGroup` for the behavioural part and any layout for
   the visual part, so no `ZButtonGroup` is planned.
3. **Custom `color` is a Qt colour, not a CSS colour string**, and it does not
   auto-derive hover / active / dark variants.
4. **Transitions.** Element Plus animates background/border changes over ~100 ms
   with the `el-fade-in` timing function. `ZButton` switches colours
   immediately; only the loading spinner is animated.
5. **Focus ring** is drawn by `painter::DrawFocusRing()` at the widget bounds;
   CSS `:focus-visible` semantics (ring only after keyboard navigation) are
   approximated by Qt's focus policy.

## Future Roadmap

- Colour transition animation through `AnimationManager` for state changes
- `bg` variant support for `text` buttons
- Icon-only auto-sizing polish when `circle` is set
- RTL mirroring of the icon / text gap (currently reserved, see
  `AGENTS.md` §IV)
