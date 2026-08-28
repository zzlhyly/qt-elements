# ZBadge

Element Plus reference: <https://element-plus.org/en-US/component/badge.html>

## Introduction

`ZBadge` renders an Element Plus badge: either a numeric counter (clamped to
`{max}+`) or a small dot indicator. It is a standalone `QWidget`, so it can be
placed in any layout.

Unlike Element Plus, where the badge wraps its target and overlays the corner,
`ZBadge` draws only the badge itself. Overlay positioning is expressed with the
host layout (or by parenting the badge to the target widget and setting a
geometry), which keeps the component free of layout side effects.

## Class Diagram

```
QObject
└── QWidget
    └── ZBadge
          ├── int       value_
          ├── BadgeType type_
          ├── int       max_
          ├── bool      dot_
          └── bool      hidden_
```

Collaborators:

```
ZBadge ──uses──> painter::DrawBackground / DrawBorder / DrawText
       ──uses──> theme::colorDanger() …   badge colour + font tokens
```

## Public API

Header: `coding/uicontrols/src/widgets/badge/zbadge.h`

### Enums

| Enum | Values |
|------|--------|
| `BadgeType` | `kPrimary`, `kSuccess`, `kInfo`, `kWarning`, `kDanger` |

### Properties (`Q_PROPERTY`)

| Property | Type | Default | Accessors |
|----------|------|---------|-----------|
| `value` | `int` | `0` | `setValue()` / `value()` |
| `badgeType` | `BadgeType` | `kDanger` | `setBadgeType()` / `badgeType()` |
| `max` | `int` | `99` | `setMax()` / `max()` |
| `dot` | `bool` | `false` | `setDot()` / `isDot()` |
| `badgeHidden` | `bool` | `false` | `setBadgeHidden()` / `isBadgeHidden()` |

### Constructors

```cpp
explicit ZBadge(QWidget* parent = nullptr);
ZBadge(int value, QWidget* parent = nullptr);
```

### Size hints

```cpp
QSize sizeHint() const override;
QSize minimumSizeHint() const override;
```

### Signals

None. The badge is a display-only indicator.

## Demos

| Demo | Source |
|------|--------|
| Basic | [`basic.cpp`](../coding/uicontrols/examples/badge/basic.cpp) |
| Max Value | [`max.cpp`](../coding/uicontrols/examples/badge/max.cpp) |
| Dot | [`dot.cpp`](../coding/uicontrols/examples/badge/dot.cpp) |

## Supported Features

- numeric badge with `max` clamping rendered as `{max}+`
- dot mode
- 5 colour types
- hidden state (`badgeHidden`)
- high-DPI rendering, metrics from `theme::`

## Unsupported Features

| Element Plus | Status |
|--------------|--------|
| `value` as a string (text badge) | not implemented — `value` is `int` |
| `color` (free-form custom colour) | not implemented — 5 type tokens only |
| `show-zero` (hide when `value == 0`) | not implemented; use `setBadgeHidden()` |
| `offset` (`[left, top]` nudge) | not implemented; position via layout |
| `badge-style` / `badge-class` | not applicable to Qt |
| `content` slot (arbitrary badge content) | not implemented |
| Wrapping a target child element | not implemented — see note below |

## Differences from Element Plus

1. **No target wrapping.** Element Plus `<el-badge>` takes the target as its
   default slot and overlays the badge on the target's top-right corner. `ZBadge`
   paints only the badge; the caller positions it. To reproduce the overlay
   look, parent the badge to the target widget and set a geometry manually.
2. **`value` is typed `int`.** Element Plus accepts `string | number` and only
   applies `max` when the value is numeric; a string value is rendered verbatim.
   `ZBadge` has no text mode at all.
3. **`hidden` is renamed `badgeHidden`.** `hidden` collides with `QWidget`'s
   `isHidden()` / `setHidden()` pair, so the Qt name avoids shadowing a widget
   lifecycle method.
4. **Zero is displayed.** With the Element Plus default `show-zero = true` a
   `0` badge is visible — matching `ZBadge` — but Element Plus can suppress it,
   which `ZBadge` cannot.
5. **`type` default.** Element Plus defaults to `danger`; `ZBadge` matches.

## Future Roadmap

- Text / string badge mode
- Custom `color` with derived border
- `offset` support for overlay positioning
- Optional `ZBadgeOverlay` helper that wraps a target widget and positions the
  badge automatically
