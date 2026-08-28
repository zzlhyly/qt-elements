# ZProgress

Element Plus reference: <https://element-plus.org/en-US/component/progress.html>

## Introduction

`ZProgress` is the Element Plus Progress bar: a line, circle or dashboard gauge
with status colouring, an optional percentage label inside or outside the bar,
and an indeterminate sweep animation.

## Class Diagram

```
QObject
└── QWidget
    └── ZProgress
          ├── int            percentage_ / strokeWidth_
          ├── ProgressType   type_
          ├── ProgressStatus status_
          ├── bool           showText_ / indeterminate_ / textInside_
          ├── int            ind_pos_ / ind_dir_
          └── AnimHandle     ind_anim_
```

Collaborators:

```
ZProgress ──uses──> AnimationManager   indeterminate sweep
          ──uses──> painter::DrawBackground / drawArc / DrawText
          ──uses──> theme::colorPrimary() / colorSuccess() / colorWarning() / colorDanger()
```

## Public API

Header: `coding/uicontrols/src/widgets/progress/zprogress.h`

### Enums

| Enum | Values |
|------|--------|
| `ProgressType` | `kLine`, `kCircle`, `kDashboard` |
| `ProgressStatus` | `kNormal`, `kSuccess`, `kException`, `kWarning` |

### Properties (`Q_PROPERTY`)

| Property | Type | Default | Accessors |
|----------|------|---------|-----------|
| `percentage` | `int` | `0` | `setPercentage()` / `percentage()` |
| `type` | `ProgressType` | `kLine` | `setType()` / `type()` |
| `strokeWidth` | `int` | `6` | `setStrokeWidth()` / `strokeWidth()` |
| `status` | `ProgressStatus` | `kNormal` | `setStatus()` / `status()` |
| `showText` | `bool` | `true` | `setShowText()` / `isShowText()` |
| `indeterminate` | `bool` | `false` | `setIndeterminate()` / `isIndeterminate()` |
| `textInside` | `bool` | `false` | `setTextInside()` / `isTextInside()` |

### Constructors

```cpp
explicit ZProgress(QWidget* parent = nullptr);
```

### Size hint

```cpp
QSize sizeHint() const override;
```

### Signals

None. `ZProgress` is a display-only indicator.

## Demos

| Demo | Source |
|------|--------|
| Line | [`line.cpp`](../coding/uicontrols/examples/progress/line.cpp) |
| Status | [`status.cpp`](../coding/uicontrols/examples/progress/status.cpp) |
| Text Inside | [`text_inside.cpp`](../coding/uicontrols/examples/progress/text_inside.cpp) |
| Stroke Width | [`stroke_width.cpp`](../coding/uicontrols/examples/progress/stroke_width.cpp) |
| Show Text | [`show_text.cpp`](../coding/uicontrols/examples/progress/show_text.cpp) |
| Circle | [`circle.cpp`](../coding/uicontrols/examples/progress/circle.cpp) |
| Dashboard | [`dashboard.cpp`](../coding/uicontrols/examples/progress/dashboard.cpp) |
| Indeterminate | [`indeterminate.cpp`](../coding/uicontrols/examples/progress/indeterminate.cpp) |

## Supported Features

- line, circle and dashboard types
- 4 status colourings; a check glyph replaces the label at 100% with `kSuccess`
- configurable stroke width (clamped to a minimum of 1)
- text inside the bar (line type) or beside it
- indeterminate sweep animation driven by `AnimationManager`
- high-DPI rendering

## Unsupported Features

The official page lists eight demos. Two have no `ZProgress` equivalent:

| Element Plus | Status |
|--------------|--------|
| `color` (custom colour: string, function, or array gradient) | not implemented — `status` tokens only |
| `striped` / `striped-flow` | not implemented |
| `format` (custom percentage text) | not implemented |
| `width` (circle/dashboard diameter) | not implemented — size comes from the layout |
| `duration` (animation speed) | not implemented — duration comes from `theme::` |
| `stroke-linecap` | always round |
| `default` slot (custom content) | not implemented |

## Differences from Element Plus

1. **No custom colour.** Element Plus `color` accepts a string, a function of
   the percentage, or an array for a gradient, and it overrides `status`.
   `ZProgress` colours strictly from `status`, so a gradient or a
   percentage-driven ramp is not possible.
2. **No striped mode.** The `striped` and `striped-flow` props animate diagonal
   stripes along the bar; there is no equivalent.
3. **Percentage label is fixed format.** Element Plus accepts a `format`
   function returning any string; `ZProgress` always renders `"{n}%"`, or a
   status icon when `status` is not `kNormal` and the type is line.
4. **Size is layout-driven.** Element Plus sizes circles via `width` (default
   `126`); `ZProgress` derives its size from `sizeHint()` and the parent layout,
   with a minimum width guard.
5. **Out-of-range `percentage` is silently clamped.** Element Plus documents
   `0`-`100` as a requirement; `setPercentage()` applies `qBound(0, p, 100)`, so
   an out-of-range value is accepted and clamped without any warning.
6. **Indeterminate duration is fixed.** Element Plus exposes `duration` (shared
   between indeterminate and striped-flow); here the duration comes from
   `theme::` and is not per-instance.

## Future Roadmap

- Custom `color` support (solid and gradient)
- `format` hook for the label text
- `striped` / `striped-flow` rendering
- Explicit `width` for circle and dashboard types
- Configurable animation duration
- `percentage` range validation
