# ZBadge

## Introduction

ZBadge is a small notification indicator displayed as a colored circle or dot, typically positioned as a superscript on another element.

## Public API

### Enums
| Enum | Values |
|------|--------|
| `BadgeType` | `kPrimary`, `kSuccess`, `kInfo`, `kWarning`, `kDanger` |

### Methods
- `void setValue(int)`, `int value()`
- `void setBadgeType(BadgeType)`, `BadgeType badgeType()`
- `void setMax(int)`, `int max()` — values above max display as "N+"
- `void setDot(bool)`, `bool isDot()` — dot mode (8px circle, no text)
- `void setBadgeHidden(bool)`, `bool isBadgeHidden()`

## Demos
| Demo | File |
|------|------|
| Basic | `examples/badge/basic.cpp` |
| Dot | `examples/badge/dot.cpp` |
| Max | `examples/badge/max.cpp` |
