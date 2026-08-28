# ZText

Element Plus reference: <https://element-plus.org/en-US/component/text.html>

## Introduction

`ZText` is the Element Plus Typography `Text` component: a single run of text
with a semantic colour type, a size step, and optional single-line right-side
elision. It is a lightweight `QWidget` that paints its own text rather than
wrapping a `QLabel`.

## Class Diagram

```
QObject
└── QWidget
    └── ZText
          ├── QString  text_
          ├── TextType type_
          ├── TextSize size_
          └── bool     truncated_
```

Collaborators:

```
ZText ──uses──> painter::DrawText   alignment + elision
      ──uses──> theme::textPrimary() / colorPrimary() …  type colour tokens
```

## Public API

Header: `coding/uicontrols/src/widgets/text/ztext.h`

### Enums

| Enum | Values |
|------|--------|
| `TextType` | `kDefault`, `kPrimary`, `kSuccess`, `kInfo`, `kWarning`, `kDanger` |
| `TextSize` | `kLarge`, `kMedium`, `kSmall` |

### Properties (`Q_PROPERTY`)

| Property | Type | Default | Accessors |
|----------|------|---------|-----------|
| `textType` | `TextType` | `kDefault` | `setTextType()` / `textType()` |
| `textSize` | `TextSize` | `kSmall` | `setTextSize()` / `textSize()` |
| `truncated` | `bool` | `false` | `setTruncated()` / `isTruncated()` |

### Constructors

```cpp
explicit ZText(QWidget* parent = nullptr);
ZText(const QString& text, QWidget* parent = nullptr);
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
| Types | [`types.cpp`](../coding/uicontrols/examples/text/types.cpp) |
| All Types | [`all_types.cpp`](../coding/uicontrols/examples/text/all_types.cpp) |
| Sizes | [`sizes.cpp`](../coding/uicontrols/examples/text/sizes.cpp) |
| Truncated | [`truncated.cpp`](../coding/uicontrols/examples/text/truncated.cpp) |

## Supported Features

- 6 semantic colour types
- 3 size steps
- single-line truncation with right-side ellipsis
- high-DPI rendering

## Unsupported Features

| Element Plus | Status |
|--------------|--------|
| `line-clamp` (multi-line ellipsis) | not implemented — single line only |
| `tag` override (`p`, `b`, `i`, `sub`, `sup`, `ins`, `del`, `mark`) | not applicable to Qt; use `QLabel` with rich text |
| The `Mixed` demo (inline formatting combinations) | not implemented |
| The `Override` demo | not implemented |

The Element Plus Text page lists five demos: Basic, Sizes, Ellipsis, Override and
Mixed. Two of them (`Override`, `Mixed`) depend on HTML tag semantics and have no
Qt counterpart.

## Differences from Element Plus

1. **Three size steps instead of one plus a default.** Element Plus `size` is an
   enum whose default is `default`; `ZText` exposes `kLarge` / `kMedium` /
   `kSmall` and defaults to `kSmall`, because a bare `default` value carries no
   pixel size on its own.
2. **Truncation is single-line only.** `truncated` maps to Element Plus
   `truncated` (single-line ellipsis). The separate `line-clamp` prop for
   multi-line clamping is missing, so a `ZText` in a wrapping layout will grow
   vertically instead of clamping.
3. **Elision requires a bounded width.** Like Element Plus, truncation only
   takes effect once the widget is narrower than its text — in Qt that means the
   widget must be constrained by its layout.
4. **`size` also changes the font weight in Element Plus** for some sizes;
   `ZText` changes pixel size only.

## Future Roadmap

- `line-clamp` equivalent (`setMaxLines(int)` with multi-line elision)
- Font-weight handling per size step
- Selectable text (`Qt::TextSelectableByMouse`) for long body copy
- Rich-text mode delegating to `QLabel` when markup is needed
