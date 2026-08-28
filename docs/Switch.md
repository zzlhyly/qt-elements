# ZSwitch

Element Plus reference: <https://element-plus.org/en-US/component/switch.html>

## Introduction

`ZSwitch` is the Element Plus Switch: a `QAbstractButton` whose knob slides
between the off and on positions with an easing animation driven by
`AnimationManager`, plus a loading spinner and optional active/inactive text
labels.

## Class Diagram

```
QObject
└── QWidget
    └── QAbstractButton
        └── ZSwitch
              ├── qreal       offset_          0..1 slide progress
              ├── SwitchSize  size_
              ├── bool        loading_
              ├── QString     active_text_ / inactive_text_
              ├── qreal       loading_angle_
              └── AnimHandle  slide_anim_ / loading_anim_
```

Collaborators:

```
ZSwitch ──uses──> AnimationManager   slide transition + loading rotation
        ──uses──> painter::DrawBackground / DrawBorder / drawEllipse
        ──uses──> theme::colorPrimary() / borderColor() / colorWhite()
```

## Public API

Header: `coding/uicontrols/src/widgets/switch/zswitch.h`

### Enums

| Enum | Values |
|------|--------|
| `SwitchSize` | `kLarge`, `kDefault`, `kSmall` |

### Properties (`Q_PROPERTY`)

| Property | Type | Default | Accessors |
|----------|------|---------|-----------|
| `switchSize` | `SwitchSize` | `kDefault` | `setSwitchSize()` / `switchSize()` |
| `loading` | `bool` | `false` | `setLoading()` / `isLoading()` |
| `activeText` | `QString` | empty | `setActiveText()` / `activeText()` |
| `inactiveText` | `QString` | empty | `setInactiveText()` / `inactiveText()` |

`checked` comes from `QAbstractButton`; `enabled` from `QWidget`.

### Constructors

```cpp
explicit ZSwitch(QWidget* parent = nullptr);
```

### Size hint

```cpp
QSize sizeHint() const override;
```

### Signals

Inherited from `QAbstractButton`: `toggled(bool)`, `clicked(bool)`.

### Reimplemented event handlers

`paintEvent`, `nextCheckState()`, `checkStateSet()`.

## Demos

| Demo | Source |
|------|--------|
| Basic | [`basic.cpp`](../coding/uicontrols/examples/switch/basic.cpp) |
| Sizes | [`sizes.cpp`](../coding/uicontrols/examples/switch/sizes.cpp) |
| Active Text | [`active_text.cpp`](../coding/uicontrols/examples/switch/active_text.cpp) |
| Disabled | [`disabled.cpp`](../coding/uicontrols/examples/switch/disabled.cpp) |
| Loading | [`loading.cpp`](../coding/uicontrols/examples/switch/loading.cpp) |
| With Label | [`with_label.cpp`](../coding/uicontrols/examples/switch/with_label.cpp) |

## Supported Features

- animated slide transition between states
- 3 sizes
- loading state with a rotating arc
- active / inactive text labels drawn outside the track
- disabled state
- keyboard activation (Space) and focus via `QAbstractButton`

## Unsupported Features

The official page lists ten demos. Four have no `ZSwitch` equivalent:

| Element Plus | Status |
|--------------|--------|
| `before-change` (async guard that can abort the toggle) | not implemented |
| `active-icon` / `inactive-icon` | not implemented — text only |
| `active-action-icon` / `inactive-action-icon` (icon inside the knob) | not implemented |
| `active-value` / `inactive-value` (non-boolean model) | not implemented |
| `inline-prompt` (text inside the knob) | not implemented |
| `active-color` / `inactive-color` / `border-color` | deprecated upstream; use `theme::` |
| `width` | not implemented — width follows size and text |
| `active-action` / `inactive-action` / `active` / `inactive` slots | not applicable to Qt |
| `focus()` expose | `QWidget::setFocus()` already provides it |

## Differences from Element Plus

1. **The model is boolean.** Element Plus can bind `active-value` /
   `inactive-value` to strings or numbers; `ZSwitch` is always a checked /
   unchecked boolean.
2. **Text is always outside the knob.** Element Plus has `active-text` /
   `inactive-text` outside the track **and** `inline-prompt`, which puts text
   inside the knob and renders only its first character. Only the outside form
   is implemented.
3. **No `before-change`.** Element Plus can delay or veto a toggle by returning
   `false` or a rejected promise from `before-change`, usually paired with
   `loading`. `ZSwitch` toggles immediately; the veto has to be implemented in
   the slot connected to `toggled(bool)`.
4. **No icons.** The `active-icon` family and the two action-icon props are all
   missing, so the knob is always a plain circle.
5. **Animation duration is fixed by `theme::`** rather than configurable per
   instance.
6. **`loading` also blocks toggling.** `nextCheckState()` returns early while
   `loading` is `true`, so a loading switch ignores clicks. Element Plus reaches
   the same visual outcome through the `before-change` + `loading` pairing, but
   it is an explicit user hook there rather than built-in behaviour.

## Future Roadmap

- `before-change` hook (veto / async confirmation)
- `inline-prompt` text inside the knob
- `activeIcon` / `inactiveIcon` through `IconManager`
- Non-boolean active / inactive values (`QVariant`)
- Configurable animation duration
