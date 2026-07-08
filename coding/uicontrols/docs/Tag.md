# ZTag

## Introduction

ZTag is a Qt Widgets tag component for marking and categorization. Visual appearance matches Element Plus Tag component.

## Public API

### Enums

| Enum | Values |
|------|--------|
| `TagType` | `kPrimary`, `kSuccess`, `kInfo`, `kWarning`, `kDanger` |
| `TagEffect` | `kLight`, `kDark`, `kPlain` |
| `TagSize` | `kLarge`, `kMedium`, `kSmall` |

### Methods

| Method | Description |
|--------|-------------|
| `void setTagType(TagType)` | Set color type |
| `void setEffect(TagEffect)` | Set visual effect (light/dark/plain) |
| `void setTagSize(TagSize)` | Set size |
| `void setClosable(bool)` | Show close button |
| `void setRound(bool)` | Round corners |
| `void setHit(bool)` | Add primary border |
| `void closed()` signal | Emitted when close button clicked |

## Demo Links

| Demo | File |
|------|------|
| Basic | `examples/tag/basic.cpp` |
| Closable | `examples/tag/closable.cpp` |
| Sizes | `examples/tag/sizes.cpp` |
| Theme Light | `examples/tag/theme_light.cpp` |
| Theme Dark | `examples/tag/theme_dark.cpp` |
| Theme Plain | `examples/tag/theme_plain.cpp` |
| Round | `examples/tag/round.cpp` |

## Supported Features

- [x] 5 color types
- [x] 3 effects (light/dark/plain)
- [x] 3 sizes sourced from Theme
- [x] Closable with hover effect
- [x] Round shape
- [x] Hit border
- [x] Foundation integration (Style, Painter, StateTracker)
- [x] Q_PROPERTY declarations
