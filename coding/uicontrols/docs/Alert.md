# ZAlert

## Introduction

ZAlert is a Qt Widgets alert/banner component for displaying status messages.

## Public API

### Enums

| Enum | Values |
|------|--------|
| `AlertType` | `kSuccess`, `kInfo`, `kWarning`, `kError` |
| `AlertEffect` | `kLight`, `kDark` |

### Methods

| Method | Description |
|--------|-------------|
| `void setTitle(const QString&)` | Set alert text |
| `void setType(AlertType)` | Set alert type |
| `void setEffect(AlertEffect)` | Set visual effect |
| `void setClosable(bool)` | Show close button |
| `void setShowIcon(bool)` | Show type icon |
| `void setCenter(bool)` | Center content |
| `void closed()` signal | Emitted when close button clicked |

## Demo Links

| Demo | File |
|------|------|
| Basic | `examples/alert/basic.cpp` |
| Theme | `examples/alert/theme.cpp` |
| Closable | `examples/alert/closable.cpp` |
| Show Icon | `examples/alert/show_icon.cpp` |
| Center | `examples/alert/center.cpp` |
| Description | `examples/alert/description.cpp` |

## Supported Features

- [x] 4 types (success/info/warning/error)
- [x] 2 effects (light/dark)
- [x] Closable with hover effect
- [x] Type-specific icons
- [x] Center/left alignment
- [x] Foundation integration (Style, Painter, StateTracker)
- [x] Q_PROPERTY declarations
