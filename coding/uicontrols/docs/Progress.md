# ZProgress

## Introduction

ZProgress visualizes completion percentage with line, circle, and dashboard modes.

## Public API

### Enums
| Enum | Values |
|------|--------|
| `ProgressType` | `kLine`, `kCircle`, `kDashboard` |
| `ProgressStatus` | `kNormal`, `kSuccess`, `kException`, `kWarning` |

- `void setPercentage(int)`, `int percentage()`
- `void setType(ProgressType)`, `ProgressType type()`
- `void setStrokeWidth(int)`, `int strokeWidth()`
- `void setStatus(ProgressStatus)`, `ProgressStatus status()`
- `void setShowText(bool)`, `bool isShowText()`
- `void setIndeterminate(bool)`, `bool isIndeterminate()`
- `void setTextInside(bool)`, `bool isTextInside()`

Q_PROPERTY: percentage, type, strokeWidth, status, showText, indeterminate, textInside

## Demos
| Demo | File |
|------|------|
| Line | `examples/progress/line.cpp` |
| Circle | `examples/progress/circle.cpp` |
| Dashboard | `examples/progress/dashboard.cpp` |
| Status | `examples/progress/status.cpp` |
| Indeterminate | `examples/progress/indeterminate.cpp` |
| Text Inside | `examples/progress/text_inside.cpp` |
