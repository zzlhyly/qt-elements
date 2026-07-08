# ZSlider

## Introduction

ZSlider is a horizontal range slider with draggable thumb, step snapping, and optional stop markers.

## Public API

- `void setMinimum(int)`, `int minimum()`
- `void setMaximum(int)`, `int maximum()`
- `void setValue(int)`, `int value()`
- `void setStep(int)`, `int step()`
- `void setShowStops(bool)`, `bool isShowStops()`
- Signal: `valueChanged(int)`
- Q_PROPERTY: minimum, maximum, value, step, showStops

## Demos
| Demo | File |
|------|------|
| Basic | `examples/slider/basic.cpp` |
| Disabled | `examples/slider/disabled.cpp` |
| Range | `examples/slider/range.cpp` |
| Stops | `examples/slider/stops.cpp` |
