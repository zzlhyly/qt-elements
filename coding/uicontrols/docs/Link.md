# ZLink

## Introduction

ZLink is a Qt Widgets text link component with hover color change and optional underline.

## Public API

### Enums

| Enum | Values |
|------|--------|
| `LinkType` | `kDefault`, `kPrimary`, `kSuccess`, `kWarning`, `kDanger`, `kInfo` |

### Methods

| Method | Description |
|--------|-------------|
| `void setLinkType(LinkType)` | Set color type |
| `void setUnderline(bool)` | Enable underline |
| `void setText(const QString&)` | Set link text |
| `void clicked()` signal | Emitted on click |

## Demo Links

| Demo | File |
|------|------|
| Basic | `examples/link/basic.cpp` |
| Underline | `examples/link/underline.cpp` |
| Disabled | `examples/link/disabled.cpp` |
| Types | `examples/link/types.cpp` |

## Supported Features

- [x] 6 color types
- [x] Hover color change
- [x] Underline mode
- [x] Disabled state
- [x] Foundation integration (StateTracker, Paint)
- [x] Q_PROPERTY declarations
