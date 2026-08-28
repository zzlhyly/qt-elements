# ZAlert

Element Plus reference: <https://element-plus.org/en-US/component/alert.html>

## Introduction

`ZAlert` renders the Element Plus Alert banner: a coloured panel with an optional
type icon, an optional close button, and light or dark effects. Colours are
resolved by `style::ResolveAlert(type, effect)`.

The close glyph is a real hit target with its own `StateTracker`, so hover and
pressed feedback are independent of the banner body.

## Class Diagram

```
QObject
└── QWidget
    └── ZAlert
          ├── QString      title_
          ├── AlertType    type_
          ├── AlertEffect  effect_
          ├── bool         closable_ / showIcon_ / center_
          └── statemachine::StateTracker* close_state_
```

Collaborators:

```
ZAlert ──uses──> style::ResolveAlert()      (type x effect) -> AlertVisuals
       ──uses──> painter::DrawBackground / DrawBorder / DrawText / DrawIcon
       ──uses──> theme::successLight9() …   light-effect tokens
       ──uses──> statemachine::StateTracker close-glyph hover / press
```

## Public API

Header: `coding/uicontrols/src/widgets/alert/zalert.h`

### Enums

| Enum | Values |
|------|--------|
| `AlertType` | `kSuccess`, `kInfo`, `kWarning`, `kError` |
| `AlertEffect` | `kLight`, `kDark` |

### Properties (`Q_PROPERTY`)

| Property | Type | Default | Accessors |
|----------|------|---------|-----------|
| `type` | `AlertType` | `kInfo` | `setType()` / `type()` |
| `effect` | `AlertEffect` | `kLight` | `setEffect()` / `effect()` |
| `closable` | `bool` | `false` | `setClosable()` / `isClosable()` |
| `showIcon` | `bool` | `true` | `setShowIcon()` / `isShowIcon()` |
| `center` | `bool` | `false` | `setCenter()` / `isCenter()` |
| `title` | `QString` | empty | `setTitle()` / `title()` |

### Constructors

```cpp
explicit ZAlert(QWidget* parent = nullptr);
explicit ZAlert(const QString& title, AlertType type = kInfo, QWidget* parent = nullptr);
```

### Size hints

```cpp
QSize sizeHint() const override;
QSize minimumSizeHint() const override;
```

### Signals

| Signal | Emitted when |
|--------|--------------|
| `closed()` | the close glyph is clicked while `closable` is `true` |

### Reimplemented event handlers

`paintEvent`, `mousePressEvent`, `mouseMoveEvent`, `mouseReleaseEvent`.

## Demos

| Demo | Source |
|------|--------|
| Basic | [`basic.cpp`](../coding/uicontrols/examples/alert/basic.cpp) |
| Theme | [`theme.cpp`](../coding/uicontrols/examples/alert/theme.cpp) |
| Closable | [`closable.cpp`](../coding/uicontrols/examples/alert/closable.cpp) |
| With Icon | [`show_icon.cpp`](../coding/uicontrols/examples/alert/show_icon.cpp) |
| Centered Text | [`center.cpp`](../coding/uicontrols/examples/alert/center.cpp) |
| Description | [`description.cpp`](../coding/uicontrols/examples/alert/description.cpp) |

## Supported Features

- 4 types (success / info / warning / error)
- light and dark effects
- optional type icon, optional close button
- centered text
- close-glyph hover / pressed feedback
- high-DPI rendering

## Unsupported Features

| Element Plus | Status |
|--------------|--------|
| `description` (secondary text block) | not implemented — `title` only |
| `close-text` (textual close button) | not implemented — glyph only |
| `primary` type (added in Element Plus 2.9.11) | not implemented |
| `title` / `icon` slots (arbitrary content) | not implemented |
| Close fade-out animation | not implemented; removal is caller-driven |

Because `description` is missing, the two Element Plus demos that depend on it —
"With Description" and "With Icon and Description" — have no direct equivalent.
Our `description` demo shows a long `title` in the error type as an
approximation.

## Differences from Element Plus

1. **One text block instead of title + description.** Element Plus renders a
   bold title plus a lighter description line; `ZAlert` renders a single
   `title`. Height therefore does not change when the content is long.
2. **`closable` defaults to `false`.** Element Plus defaults `closable` to
   `true`. `ZAlert` requires an explicit `setClosable(true)`.
3. **`showIcon` defaults to `true`.** Element Plus defaults `show-icon` to
   `false`. This is a deliberate deviation so the control looks right out of the
   box.
4. **`close` event vs `closed()` signal.** Element Plus fires `close` when the
   alert is closed; `ZAlert` emits `closed()` and never hides itself, so the
   application decides whether to `hide()` or `deleteLater()`.
5. **No transition.** Element Plus animates the alert out on close. `ZAlert` has
   no animation.

The official page lists seven demos: Basic Usage, Theme, Customizable Close
Button, With Icon, Centered Text, With Description, and With Icon and
Description. `ZAlert` covers four of them fully (Basic, Theme, With Icon,
Centered Text) and one partially (Customizable Close Button — glyph only).

## Future Roadmap

- `description` support (secondary text line + taller `sizeHint`)
- `closeText` for a textual close button
- `kPrimary` type
- Fade-out animation on close via `AnimationManager`
- `icon` slot for a custom leading widget
