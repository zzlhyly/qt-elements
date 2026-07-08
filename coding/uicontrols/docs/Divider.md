# ZDivider

## Introduction

ZDivider is a horizontal or vertical visual separator with optional text and configurable line style.

## Public API

### Enums
| Enum | Values |
|------|--------|
| `Direction` | `kHorizontal`, `kVertical` |
| `ContentPosition` | `kLeft`, `kCenter`, `kRight` |
| `BorderStyle` | `kSolid`, `kDashed`, `kDotted` |

### Methods
- `void setText(const QString&)`, `QString text()`
- `void setDirection(Direction)`, `Direction direction()`
- `void setContentPosition(ContentPosition)`, `ContentPosition contentPosition()`
- `void setBorderStyle(BorderStyle)`, `BorderStyle borderStyle()`

## Demos
| Demo | File |
|------|------|
| Basic | `examples/divider/basic.cpp` |
| With Text | `examples/divider/with_text.cpp` |
| Dashed/Dotted | `examples/divider/dashed_dotted.cpp` |
