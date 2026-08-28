# ZDivider

Element Plus reference: <https://element-plus.org/en-US/component/divider.html>

## Introduction

`ZDivider` is the Element Plus divider: a horizontal or vertical rule, optionally
interrupted by a text label whose position can be left, center or right. The
line style is solid, dashed or dotted.

## Class Diagram

```
QObject
└── QWidget
    └── ZDivider
          ├── QString          text_
          ├── Direction        direction_
          ├── ContentPosition  contentPos_
          └── BorderStyle      borderStyle_
```

Collaborators:

```
ZDivider ──uses──> painter::DrawText / custom line stroking
         ──uses──> theme::borderLight() / textRegular()
```

## Public API

Header: `coding/uicontrols/src/widgets/divider/zdivider.h`

### Enums

| Enum | Values |
|------|--------|
| `Direction` | `kHorizontal`, `kVertical` |
| `ContentPosition` | `kLeft`, `kCenter`, `kRight` |
| `BorderStyle` | `kSolid`, `kDashed`, `kDotted` |

### Properties (`Q_PROPERTY`)

| Property | Type | Default | Accessors |
|----------|------|---------|-----------|
| `direction` | `Direction` | `kHorizontal` | `setDirection()` / `direction()` |
| `contentPosition` | `ContentPosition` | `kCenter` | `setContentPosition()` / `contentPosition()` |
| `borderStyle` | `BorderStyle` | `kSolid` | `setBorderStyle()` / `borderStyle()` |

`text` is a plain setter/getter pair, not a `Q_PROPERTY`, mirroring `QLabel`
naming rather than Qt property conventions.

### Constructors

```cpp
explicit ZDivider(QWidget* parent = nullptr);
ZDivider(const QString& text, QWidget* parent = nullptr);
```

### Accessors

```cpp
void setText(const QString& text);
QString text() const;
QSize sizeHint() const override;
```

### Signals

None.

## Demos

| Demo | Source |
|------|--------|
| Basic | [`basic.cpp`](../coding/uicontrols/examples/divider/basic.cpp) |
| With Text | [`with_text.cpp`](../coding/uicontrols/examples/divider/with_text.cpp) |
| Dashed / Dotted | [`dashed_dotted.cpp`](../coding/uicontrols/examples/divider/dashed_dotted.cpp) |
| Vertical | [`vertical.cpp`](../coding/uicontrols/examples/divider/vertical.cpp) |

## Supported Features

- horizontal and vertical orientation
- solid, dashed and dotted line styles
- optional text label with left / center / right placement
- high-DPI rendering

## Unsupported Features

| Element Plus | Status |
|--------------|--------|
| `border-style` as an arbitrary CSS value (`double`, `groove`, …) | only `kSolid` / `kDashed` / `kDotted` |
| `default` slot holding arbitrary widget content | text only; see below |

## Differences from Element Plus

1. **Element Plus demos.** The official page shows four demos: Basic usage,
   Custom content, dashed line, and Vertical divider. `ZDivider` covers all four
   behaviours; the "Custom content" demo is covered by our `With Text` demo
   because the slot is limited to text.
2. **Content is text, not a slot.** Element Plus accepts arbitrary markup in the
   default slot (an icon, a button, rich text). `ZDivider::setText()` accepts a
   `QString`; richer content has to be composed in a parent layout.
3. **Vertical size.** In vertical mode `sizeHint()` returns a fixed-width hint
   and the height is driven by the layout, whereas Element Plus relies on CSS
   sizing. A vertical divider inside a `QHBoxLayout` needs enough stretch room
   from its siblings.

## Future Roadmap

- Arbitrary widget content in place of text (would need a layout inside the
  divider and a `setContentWidget()` API)
- Additional line styles (`double`)
- RTL-aware content position mapping (`kLeft` / `kRight` swap under RTL)
