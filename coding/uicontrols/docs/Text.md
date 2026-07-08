# ZText

## Introduction

ZText is a lightweight text display component with configurable color type and size.

## Public API

### Enums
| Enum | Values |
|------|--------|
| `TextType` | `kDefault`, `kPrimary`, `kSuccess`, `kInfo`, `kWarning`, `kDanger` |
| `TextSize` | `kLarge`, `kMedium`, `kSmall` |

### Methods
- `void setText(const QString&)`, `QString text()`
- `void setTextType(TextType)`, `TextType textType()`
- `void setTextSize(TextSize)`, `TextSize textSize()`
- `void setTruncated(bool)`, `bool isTruncated()`

## Demos
| Demo | File |
|------|------|
| Types | `examples/text/types.cpp` |
| Sizes | `examples/text/sizes.cpp` |
| Truncated | `examples/text/truncated.cpp` |
