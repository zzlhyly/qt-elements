# ZInput

## Introduction

ZInput is a Qt Widgets input component that wraps a native QLineEdit (or QPlainTextEdit for textarea mode) with custom border, background, focus glow, and icon rendering. Visual appearance matches Element Plus Input component.

## Public API

### Enums

| Enum | Values |
|------|--------|
| `InputSize` | `kLarge`, `kDefault`, `kSmall` |

### Methods

| Method | Description |
|--------|-------------|
| `ZInput(QWidget* parent = nullptr)` | Constructor |
| `void setText(const QString&)` | Set input text |
| `QString text() const` | Get input text |
| `void setPlaceholderText(const QString&)` | Set placeholder text |
| `QString placeholderText() const` | Get placeholder text |
| `void setInputSize(InputSize)` | Set size (Large/Default/Small) |
| `void setClearable(bool)` | Show/hide clear button |
| `void setPasswordMode(bool)` | Toggle password echo mode |
| `void setTextarea(int rows)` | Switch to textarea mode with given rows |
| `void setPrefixIcon(const QChar&)` | Set prefix icon character |
| `void setSuffixIcon(const QChar&)` | Set suffix icon character |
| `InputSize inputSize() const` | Get current size |
| `bool isClearable() const` | Check clearable state |
| `bool isPasswordMode() const` | Check password mode |
| `QLineEdit* lineEdit() const` | Get inner QLineEdit |
| `int rows() const` | Get textarea rows (0 = line edit mode) |

### Properties (Q_PROPERTY)

| Property | Type | Access |
|----------|------|--------|
| `inputSize` | `InputSize` | READ/WRITE |
| `clearable` | `bool` | READ/WRITE |
| `passwordMode` | `bool` | READ/WRITE |
| `placeholderText` | `QString` | READ/WRITE |

### Signals

| Signal | Description |
|--------|-------------|
| `textChanged(const QString&)` | Text content changed |

## Demo Links

| Demo | File |
|------|------|
| Basic | `examples/input/basic.cpp` |
| Disabled | `examples/input/disabled.cpp` |
| Clearable | `examples/input/clearable.cpp` |
| Password | `examples/input/password.cpp` |
| Size | `examples/input/size.cpp` |
| Textarea | `examples/input/textarea.cpp` |
| With Icon | `examples/input/with_icon.cpp` |

## Supported Features

- [x] 3 sizes (Large 40px, Default 32px, Small 24px) sourced from Theme
- [x] Clearable mode (× button appears when text is non-empty)
- [x] Password mode (text masked, eye toggle button)
- [x] Textarea mode (multi-line via QPlainTextEdit)
- [x] Prefix/suffix icon characters
- [x] Hover state (border color change to primary light)
- [x] Focus state (primary border + glow ring)
- [x] Disabled state (grayed background, light border)
- [x] Placeholder text (via QLineEdit/QPlainTextEdit built-in)
- [x] High-DPI (via Qt auto-scaling)
- [x] Q_PROPERTY declarations
- [x] Foundation integration (Painter, StateTracker, Theme)

## Unsupported Features

- [ ] Prepend/append content slots (Element Plus `<template #prepend>`)
- [ ] Native form validation integration
- [ ] Input groups (combined inputs with addons)
- [ ] Auto-complete / suggestion dropdown
- [ ] Input number mode (stepper buttons)

## Differences from Element Plus

| Feature | Element Plus | ZInput | Notes |
|---------|-------------|--------|-------|
| Prepend/Append slots | Yes | No | Would require custom slot widgets |
| Input group | `<el-input-group>` | No | Multiple inputs combined |
| Auto-size textarea | Yes | No | Fixed rows only |
| Show word limit | Yes | No | Counter display |
| Validate event | Yes | No | Qt uses QValidator |

## Future Roadmap

1. **Prepend/Append slots** — Support custom widgets before/after input
2. **Auto-size textarea** — Dynamic height based on content
3. **Input number** — Stepper buttons for numeric input
4. **Auto-complete** — Suggestion dropdown
5. **Dark Mode** — Theme-switchable colors
