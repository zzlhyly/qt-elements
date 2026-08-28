# ZLink

Element Plus reference: <https://element-plus.org/en-US/component/link.html>

## Introduction

`ZLink` renders an Element Plus text link: coloured inline text with an optional
underline and hover feedback. It is a `QWidget` (not a `QAbstractButton`) because
the control is a text run rather than a button-like target; it emits `clicked()`
directly from its mouse handler.

## Class Diagram

```
QObject
└── QWidget
    └── ZLink
          ├── QString  text_
          ├── LinkType type_
          ├── bool     underline_
          └── statemachine::StateTracker* state_tracker_
```

Collaborators:

```
ZLink ──uses──> statemachine::StateTracker  hover / pressed
      ──uses──> painter::DrawText / DrawBackground
      ──uses──> theme::colorPrimary() …     type colour tokens
```

## Public API

Header: `coding/uicontrols/src/widgets/link/zlink.h`

### Enums

| Enum | Values |
|------|--------|
| `LinkType` | `kDefault`, `kPrimary`, `kSuccess`, `kWarning`, `kDanger`, `kInfo` |

### Properties (`Q_PROPERTY`)

| Property | Type | Default | Accessors |
|----------|------|---------|-----------|
| `linkType` | `LinkType` | `kDefault` | `setLinkType()` / `linkType()` |
| `underline` | `bool` | `false` | `setUnderline()` / `isUnderline()` |

### Constructors

```cpp
explicit ZLink(QWidget* parent = nullptr);
ZLink(const QString& text, QWidget* parent = nullptr);
```

### Accessors

```cpp
void setText(const QString& text);
QString text() const;
QSize sizeHint() const override;
```

### Signals

| Signal | Emitted when |
|--------|--------------|
| `clicked()` | the link is pressed and released inside its bounds |

### Reimplemented event handlers

`paintEvent`, `enterEvent`, `leaveEvent`, `mousePressEvent`.

Note: `mouseReleaseEvent` is **not** overridden, so the click is emitted from
`mousePressEvent` and there is no press-then-cancel gesture.

## Demos

| Demo | Source |
|------|--------|
| Basic | [`basic.cpp`](../coding/uicontrols/examples/link/basic.cpp) |
| Types | [`types.cpp`](../coding/uicontrols/examples/link/types.cpp) |
| Underline | [`underline.cpp`](../coding/uicontrols/examples/link/underline.cpp) |
| Disabled | [`disabled.cpp`](../coding/uicontrols/examples/link/disabled.cpp) |

## Supported Features

- 6 colour types
- optional underline
- hover feedback through `StateTracker`
- disabled state (via `setEnabled(false)`, painted with `theme::textDisabled()`)
- high-DPI rendering

## Unsupported Features

| Element Plus | Status |
|--------------|--------|
| `href` / `target` (real navigation) | not applicable to Qt; use `QDesktopServices::openUrl()` |
| `underline` tri-state (`always` / `hover` / `never`) | boolean only — see below |
| `icon` attribute and `icon` slot | not implemented |
| `disabled` as a distinct attribute | maps to `QWidget::setEnabled(false)` |

## Differences from Element Plus

1. **Underline is a boolean.** Element Plus accepts `'always' | 'hover' | 'never'`
   since 2.9.9 (a plain boolean is deprecated and removed in 3.0.0). `ZLink`
   only has on/off: `setUnderline(true)` behaves like `always`, `false` like
   `never`. There is no hover-only underline mode.
2. **No keyboard focus.** Element Plus `<el-link>` is an `<a>` element and is
   therefore focusable and reachable by Tab. `ZLink` does not set
   `Qt::StrongFocus` and has no `FocusIn` handling, so it is mouse-only. This is
   an accessibility gap.
3. **No icon support.** The official `Icon` demo (icon before the text) has no
   `ZLink` equivalent.
4. **Click semantics.** `clicked()` fires on mouse *press*, whereas a web link
   navigates on release. Pressing and dragging away still triggers the signal.

## Future Roadmap

- Tri-state underline (`kAlways` / `kHover` / `kNever`)
- Keyboard focus + focus ring, so the link is reachable by Tab
- Optional leading icon via `IconManager`
- Emit `clicked()` on release to match web link semantics
