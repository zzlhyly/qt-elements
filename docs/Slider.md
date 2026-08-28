# ZSlider

Element Plus reference: <https://element-plus.org/en-US/component/slider.html>

## Introduction

`ZSlider` is the Element Plus Slider: a single-thumb track control with step
snapping, optional stop markers, and horizontal or vertical orientation. Track,
fill and thumb are all drawn with `QPainter`.

## Class Diagram

```
QObject
└── QWidget
    └── ZSlider
          ├── int       min_ / max_ / value_ / step_
          ├── Direction direction_
          ├── bool      showStops_ / dragging_
          └── int       trackPad_
```

Collaborators:

```
ZSlider ──uses──> painter::DrawBackground / DrawBorder / drawEllipse (thumb)
        ──uses──> theme::colorPrimary() / borderLight() / colorWhite()
```

## Public API

Header: `coding/uicontrols/src/widgets/slider/zslider.h`

### Enums

| Enum | Values |
|------|--------|
| `Direction` | `kHorizontal`, `kVertical` |

### Properties (`Q_PROPERTY`)

| Property | Type | Default | Accessors |
|----------|------|---------|-----------|
| `minimum` | `int` | `0` | `setMinimum()` / `minimum()` |
| `maximum` | `int` | `100` | `setMaximum()` / `maximum()` |
| `value` | `int` | `0` | `setValue()` / `value()` |
| `step` | `int` | `1` | `setStep()` / `step()` |
| `showStops` | `bool` | `false` | `setShowStops()` / `isShowStops()` |
| `direction` | `Direction` | `kHorizontal` | `setDirection()` / `direction()` |

### Constructors

```cpp
explicit ZSlider(QWidget* parent = nullptr);
```

### Size hint

```cpp
QSize sizeHint() const override;
```

### Signals

| Signal | Emitted when |
|--------|--------------|
| `valueChanged(int)` | the value changes, including continuously while dragging |

### Reimplemented event handlers

`paintEvent`, `mousePressEvent`, `mouseMoveEvent`, `mouseReleaseEvent`.

There is no keyboard support: arrow keys and Page Up / Down do not move the
thumb.

## Demos

| Demo | Source |
|------|--------|
| Basic | [`basic.cpp`](../coding/uicontrols/examples/slider/basic.cpp) |
| Range | [`range.cpp`](../coding/uicontrols/examples/slider/range.cpp) |
| Stops | [`stops.cpp`](../coding/uicontrols/examples/slider/stops.cpp) |
| Vertical | [`vertical.cpp`](../coding/uicontrols/examples/slider/vertical.cpp) |
| Disabled | [`disabled.cpp`](../coding/uicontrols/examples/slider/disabled.cpp) |

## Supported Features

- single-value horizontal and vertical sliding
- step snapping
- stop markers (`showStops`)
- mouse drag with press / move / release handling
- disabled state (via `setEnabled(false)`)
- high-DPI rendering

Note on the `Range` demo: `ZSlider` models a single integer value, so the demo
shows two sliders composed side by side rather than a true dual-thumb range
control.

## Unsupported Features

The official page lists nine demos. These have no `ZSlider` equivalent:

| Element Plus | Status |
|--------------|--------|
| `range` (dual-thumb, array model) | not implemented — single thumb only |
| `show-input` (numeric input box beside the track) | not implemented |
| `marks` (labelled tick marks) | not implemented |
| `show-tooltip` / `format-tooltip` | not implemented |
| `placement`, `persistent`, `tooltip-class` | not implemented |
| `size` | not implemented |
| `height` for vertical mode | vertical height comes from the layout |
| `step="mark"` (restrict to `marks` keys) | not implemented |
| `disabled` as an attribute | maps to `QWidget::setEnabled(false)` |
| `change` vs `input` event split | only `valueChanged(int)` |

## Differences from Element Plus

1. **Single thumb.** Element Plus switches the model to a two-element array when
   `range` is set; `ZSlider` always holds one `int`. A range selection has to be
   built from two sliders plus application logic.
2. **Only `valueChanged`.** Element Plus separates `input` (emitted continuously
   while dragging) from `change` (emitted on release). `ZSlider` emits
   `valueChanged(int)` on every move, which is closer to `input`; there is no
   release-only signal.
3. **No tooltip or marks.** The Element Plus track shows a value tooltip while
   dragging (suppressible with `show-tooltip`) and can render labelled marks.
   Neither exists here, so the current value is only visible to the application.
4. **No keyboard interaction.** Element Plus supports arrow keys and Home / End.
   `ZSlider` is mouse-only, an accessibility gap.
5. **Integer model.** Element Plus values are numbers that can be fractional
   depending on `step`; `ZSlider` uses `int` for value, min, max and step, so
   fractional steps are not representable.

## Future Roadmap

- Keyboard support (arrows, Home / End, Page Up / Down)
- `marks` with labels
- `show-tooltip` via `ZPopup` / `ZTooltip`
- Separate `valueChanged` (continuous) and `valueCommitted` (on release) signals
- Dual-thumb range mode with a `QPair<int,int>` model
- Fractional steps (`qreal` value model)
