# ZTag

Element Plus reference: <https://element-plus.org/en-US/component/tag.html>

## Introduction

`ZTag` renders the Element Plus Tag: a compact inline label with a type colour,
one of three effects, an optional close button, an optional rounded shape and an
optional "hit" (highlighted) border.

Colours are resolved by `style::ResolveTag(type, effect, enabled)` and painted
through the painter layer. Closing is interactive: the close glyph has its own
`StateTracker` so it reports hover and press independently of the tag body.

## Class Diagram

```
QObject
└── QWidget
    └── ZTag
          ├── TagType  type_
          ├── TagEffect effect_
          ├── TagSize  size_
          ├── QString  text_
          ├── bool     closable_ / round_ / hit_
          └── statemachine::StateTracker* close_state_
```

Collaborators:

```
ZTag ──uses──> style::ResolveTag()          (type x effect x enabled) -> TagVisuals
     ──uses──> painter::DrawBackground / DrawBorder / DrawText / DrawIcon
     ──uses──> theme::tagLightBg() …        colour + size tokens
     ──uses──> statemachine::StateTracker   close-glyph hover / press
```

## Public API

Header: `coding/uicontrols/src/widgets/tag/ztag.h`

### Enums

| Enum | Values |
|------|--------|
| `TagType` | `kPrimary`, `kSuccess`, `kInfo`, `kWarning`, `kDanger` |
| `TagEffect` | `kLight`, `kDark`, `kPlain` |
| `TagSize` | `kLarge`, `kMedium`, `kSmall` |

### Properties (`Q_PROPERTY`)

| Property | Type | Accessors |
|----------|------|-----------|
| `tagType` | `TagType` | `setTagType()` / `tagType()` |
| `effect` | `TagEffect` | `setEffect()` / `effect()` |
| `tagSize` | `TagSize` | `setTagSize()` / `tagSize()` |
| `closable` | `bool` | `setClosable()` / `isClosable()` |
| `round` | `bool` | `setRound()` / `isRound()` |
| `hit` | `bool` | `setHit()` / `isHit()` |

### Constructors

```cpp
explicit ZTag(QWidget* parent = nullptr);
ZTag(const QString& text, QWidget* parent = nullptr);
```

### Content and size hints

```cpp
void setText(const QString& text);
QString text() const;
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
| Basic | [`basic.cpp`](../coding/uicontrols/examples/tag/basic.cpp) |
| Closable | [`closable.cpp`](../coding/uicontrols/examples/tag/closable.cpp) |
| Round | [`round.cpp`](../coding/uicontrols/examples/tag/round.cpp) |
| Sizes | [`sizes.cpp`](../coding/uicontrols/examples/tag/sizes.cpp) |
| Theme Dark | [`theme_dark.cpp`](../coding/uicontrols/examples/tag/theme_dark.cpp) |
| Theme Light | [`theme_light.cpp`](../coding/uicontrols/examples/tag/theme_light.cpp) |
| Theme Plain | [`theme_plain.cpp`](../coding/uicontrols/examples/tag/theme_plain.cpp) |

## Supported Features

- 5 types x 3 effects x 3 sizes
- closable tag with independent close-glyph hover / pressed feedback
- `round` pill shape, `hit` highlighted border
- high-DPI rendering; every metric sourced from `theme::`

## Unsupported Features

| Element Plus | Status |
|--------------|--------|
| `color` (free-form custom colour) | not implemented — 5 type tokens only |
| `disable-transitions` (fade on removal) | not implemented; removal is instant |
| Checkable tags (`el-check-tag`, `checked`, `change`) | not implemented |
| "Edit Dynamically" (double-click to edit in place) | not implemented — no `ZTagGroup` yet |
| `size` on Element Plus also accepts an empty default | `kMedium` is our default |

## Differences from Element Plus

1. **No removal animation.** Element Plus fades a tag out before removing it;
   `ZTag` emits `closed()` and leaves removal to application code.
2. **`hit` rendering is an approximation.** The Element Plus docs describe it as
   "whether Tag has a highlighted border" but do not publish the exact visual
   treatment; `ZTag` forces a 2 px border in `theme::colorPrimary()`,
   overriding the border colour that `type` and `effect` would otherwise
   resolve to.
3. **No `ZTagGroup`.** Element Plus has no group component either, but its
   "Edit Dynamically" demo relies on a parent managing a list; in Qt that is
   the application's layout, so no library-side container is planned.
4. **Text is a `QString`, not a slot.** Rich or multi-child tag content must be
   composed by the caller and passed as text, or placed in a parent layout.
5. **`click` event.** Element Plus exposes a `click` event in addition to
   `close`; `ZTag` has no `clicked()` signal. Use a `ZTag` inside a plain
   `QWidget` with a mouse handler, or request the signal (see roadmap).

## Future Roadmap

- `clicked()` signal for interactive tags
- Optional fade-out animation before `closed()` is emitted
- Custom `color` support with derived hover / border variants
- Check-tag variant (`checked` state + `type` switching)
