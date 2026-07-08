# ZTooltip

## Introduction

ZTooltip displays hover-triggered or static text popups via ZPopup.

## Public API

- `void setTarget(QWidget*)` — widget to monitor for hover
- `void setText(const QString&)`, `QString text()`
- `void setPlacement(ZPopup::Placement)` — top/bottom/left/right
- `static void showText(QWidget*, const QString&, int duration = 3000)` — instant popup
- `static void install(QWidget*, const QString&, ZPopup::Placement)` — hover-configured tooltip
- Q_PROPERTY: text

## Demos
| Demo | File |
|------|------|
| Hover | `examples/tooltip/hover.cpp` |
| Static | `examples/tooltip/static.cpp` |
