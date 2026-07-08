# ZButton

## Introduction

ZButton is a pure Qt Widgets button component rendered entirely via QPainter.
Visual appearance matches Element Plus Button component (https://element-plus.org/en-US/component/button.html).

ZButton extends `QAbstractButton` and supports all standard button interactions:
click, hover, press, focus, disabled, and loading states.

## Class Diagram

```
QAbstractButton
    └── ZButton
            ├── StateTracker (statemachine::StateTracker)
            ├── AnimationManager
            └── Style (style::ResolveButton)
```

## Public API

### Enums

| Enum | Values |
|------|--------|
| `ButtonType` | `kDefault`, `kPrimary`, `kSuccess`, `kWarning`, `kDanger`, `kInfo` |
| `ButtonSize` | `kLarge`, `kMedium`, `kSmall` |
| `ButtonVariant` | `kSolid`, `kPlain`, `kText`, `kLink`, `kDashed` |

### Methods

| Method | Description |
|--------|-------------|
| `ZButton(QWidget* parent = nullptr)` | Constructor |
| `ZButton(const QString& text, QWidget* parent = nullptr)` | Constructor with text |
| `void setButtonType(ButtonType)` | Set color type |
| `void setButtonSize(ButtonSize)` | Set size |
| `void setButtonVariant(ButtonVariant)` | Set visual variant |
| `void setRound(bool)` | Enable round shape (border-radius: 20px) |
| `void setCircle(bool)` | Enable circle shape |
| `void setLoading(bool)` | Toggle loading spinner |
| `bool isLoading() const` | Check loading state |
| `ButtonType buttonType() const` | Get current type |
| `ButtonSize buttonSize() const` | Get current size |
| `ButtonVariant buttonVariant() const` | Get current variant |
| `bool isRound() const` | Check round shape |
| `bool isCircle() const` | Check circle shape |

### Properties (Q_PROPERTY)

| Property | Type | Access |
|----------|------|--------|
| `buttonType` | `ButtonType` | READ/WRITE |
| `buttonSize` | `ButtonSize` | READ/WRITE |
| `buttonVariant` | `ButtonVariant` | READ/WRITE |
| `round` | `bool` | READ/WRITE |
| `circle` | `bool` | READ/WRITE |
| `loading` | `bool` | READ/WRITE |

### Signals (inherited from QAbstractButton)

| Signal | Description |
|--------|-------------|
| `clicked()` | Button was clicked |
| `toggled(bool)` | Toggle state changed (for checkable buttons) |

### Slots (inherited from QAbstractButton)

| Slot | Description |
|------|-------------|
| `click()` | Programmatic click |
| `toggle()` | Toggle checked state |

## Demo Links

| Demo | File |
|------|------|
| Basic | `examples/button/basic.cpp` |
| Plain | `examples/button/plain.cpp` |
| Round | `examples/button/round.cpp` |
| Circle | `examples/button/circle.cpp` |
| Dashed | `examples/button/dashed.cpp` |
| Disabled | `examples/button/disabled.cpp` |
| Link | `examples/button/link.cpp` |
| Text | `examples/button/text.cpp` |
| Loading | `examples/button/loading.cpp` |
| Size | `examples/button/size.cpp` |
| Icon | `examples/button/icon.cpp` |
| Button Group | `examples/button/button_group.cpp` |
| Color | `examples/button/color.cpp` |

## Supported Features

- [x] 6 color types (Default, Primary, Success, Warning, Danger, Info)
- [x] 5 visual variants (Solid, Plain, Text, Link, Dashed)
- [x] 3 sizes (Large 40px, Medium 32px, Small 24px)
- [x] Round and Circle shapes
- [x] Hover state (color change via Theme)
- [x] Pressed state (darker color via Theme)
- [x] Disabled state (grayed out, cursor change)
- [x] Focus indicator (keyboard focus ring)
- [x] Keyboard accessibility (Space, Enter, Return keys)
- [x] Loading spinner with rotating arc
- [x] Icon + text support (via QIcon)
- [x] High-DPI rendering (via Qt auto-scaling)
- [x] Q_PROPERTY declarations
- [x] Foundation integration (Style, Painter, StateMachine, AnimationManager)

## Unsupported Features

- [ ] Dark Mode (deferred per Constitution)
- [ ] RTL layout (reserved)
- [ ] Accessibility (ARIA equivalents not yet implemented)
- [ ] Auto-insert-space for Chinese text (Element Plus feature)
- [ ] Custom color via setColor() (uses type-based color table only)
- [ ] Smooth color transition animations (instant color change, no interpolation)

## Differences from Element Plus

| Feature | Element Plus | ZButton | Notes |
|---------|-------------|---------|-------|
| Auto-insert-space | Yes | No | Chinese text spacing, deferred |
| Icon placement | left/right | Always left (before text) | Right placement can be added |
| Native form submit | Yes | No | Qt forms use different mechanism |
| Button group | `<el-button-group>` | QButtonGroup | Qt equivalent, different API |
| Loading slot customization | Yes | No | Only spinning arc, no custom content |
| Click animation (ripple) | No (Material) | No | Not in Element Plus design |

## Future Roadmap

1. **Dark Mode** — Theme-switchable dark color palette
2. **RTL Support** — Right-to-left layout mirroring
3. **Smooth transitions** — Color interpolation on hover/press via AnimationManager
4. **Accessibility** — QAccessibleWidget integration
5. **Custom color** — Allow arbitrary color override beyond type-based table
6. **Loading customization** — Replace spinner with custom widget or icon
7. **Auto-insert-space** — Automatic spacing for CJK characters
