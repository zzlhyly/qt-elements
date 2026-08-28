# ZInput

Element Plus reference: <https://element-plus.org/en-US/component/input.html>

## Introduction

`ZInput` is the Element Plus Input. It is a `QWidget` that owns its own internal
layout and wraps either a `QLineEdit` (single line) or a `QPlainTextEdit`
(`setTextarea()`), adding:

- a clear button
- a password reveal toggle
- prefix / suffix icons
- prepended / appended widgets (the "mixed input" look)
- an optional word-limit counter
- textarea autosize between a min and max row count

Because the internal layout is self-managed, `ZInput` is dropped into any parent
layout without extra plumbing.

## Class Diagram

```
QObject
└── QWidget
    └── ZInput
          ├── QLineEdit*      edit_
          ├── QPlainTextEdit* textarea_
          ├── QPushButton*    clear_btn_
          ├── QPushButton*    password_btn_
          ├── QWidget*        prepend_widget_ / append_widget_
          ├── QLabel*         word_limit_label_
          ├── InputSize       size_
          ├── QChar           prefix_icon_ / suffix_icon_
          └── statemachine::StateTracker* state_tracker_
```

Collaborators:

```
ZInput ──uses──> statemachine::StateTracker  hover / focused / disabled border state
       ──uses──> painter::DrawBackground / DrawBorder / DrawIcon
       ──uses──> theme::input*()             border / fill / text tokens
```

## Public API

Header: `coding/uicontrols/src/widgets/input/zinput.h`

### Enums

| Enum | Values |
|------|--------|
| `InputSize` | `kLarge`, `kDefault`, `kSmall` |

### Properties (`Q_PROPERTY`)

| Property | Type | Default | Accessors |
|----------|------|---------|-----------|
| `inputSize` | `InputSize` | `kDefault` | `setInputSize()` / `inputSize()` |
| `clearable` | `bool` | `false` | `setClearable()` / `isClearable()` |
| `passwordMode` | `bool` | `false` | `setPasswordMode()` / `isPasswordMode()` |
| `placeholderText` | `QString` | empty | `setPlaceholderText()` / `placeholderText()` |
| `autosize` | `bool` | `false` | `setAutosize()` / `isAutosize()` |
| `showWordLimit` | `bool` | `false` | `setShowWordLimit()` / `isShowWordLimit()` |

### Constructors

```cpp
explicit ZInput(QWidget* parent = nullptr);
```

### Content

```cpp
void setText(const QString& text);
QString text() const;
void setPlaceholderText(const QString& text);
QString placeholderText() const;
void setMaxLength(int len);
```

### Appearance and mode

```cpp
void setInputSize(InputSize size);
void setClearable(bool clearable);
void setPasswordMode(bool password);
void setTextarea(int rows);
void setPrefixIcon(const QChar& icon);
void setSuffixIcon(const QChar& icon);
void setPrependWidget(QWidget* widget);
void setAppendWidget(QWidget* widget);
int rows() const;
```

### Autosize and word limit

```cpp
void setAutosize(bool autosize);
void setAutosizeMinRows(int rows);   // default 2
void setAutosizeMaxRows(int rows);   // default 6
void setShowWordLimit(bool show);
```

### Escape hatch

```cpp
QLineEdit* lineEdit() const;
```

Returns the internal editor so native Qt features (validators, input masks,
`QCompleter`) can be attached. It is `nullptr` in textarea mode.

### Signals

| Signal | Emitted when |
|--------|--------------|
| `textChanged(const QString&)` | the text changes, from typing or from `setText()` |

### Reimplemented event handlers

`paintEvent`, `eventFilter`, `changeEvent`.

## Demos

| Demo | Source |
|------|--------|
| Basic | [`basic.cpp`](../coding/uicontrols/examples/input/basic.cpp) |
| Disabled | [`disabled.cpp`](../coding/uicontrols/examples/input/disabled.cpp) |
| Clearable | [`clearable.cpp`](../coding/uicontrols/examples/input/clearable.cpp) |
| Password | [`password.cpp`](../coding/uicontrols/examples/input/password.cpp) |
| Textarea | [`textarea.cpp`](../coding/uicontrols/examples/input/textarea.cpp) |
| Autosize | [`autosize.cpp`](../coding/uicontrols/examples/input/autosize.cpp) |
| Prepend / Append | [`prepend_append.cpp`](../coding/uicontrols/examples/input/prepend_append.cpp) |
| Size | [`size.cpp`](../coding/uicontrols/examples/input/size.cpp) |
| Word Limit | [`word_limit.cpp`](../coding/uicontrols/examples/input/word_limit.cpp) |
| With Icon | [`with_icon.cpp`](../coding/uicontrols/examples/input/with_icon.cpp) |

## Supported Features

- single-line and textarea modes
- 3 sizes
- clearable with an inline clear button
- password mode with a reveal toggle
- prefix / suffix icons (font glyphs via `QChar`)
- prepend / append widgets
- textarea autosize clamped between min and max rows
- word-limit counter
- hover / focus / disabled border states from `theme::`

## Unsupported Features

The official page lists thirteen demos. The following have no `ZInput`
equivalent:

| Element Plus | Status |
|--------------|--------|
| `formatter` / `parser` | not implemented; use a `QValidator` on `lineEdit()` |
| Custom clear icon (`clear-icon`) | not implemented |
| Count graphemes (`count-graphemes`) | not implemented — `QChar` counting only |
| `type` (`text` / `textarea` / others) | covered by `setTextarea()`, other types unsupported |
| `resize`, `autofocus`, `form`, `name`, `readonly` | use `lineEdit()` |
| `maxlength` / `minlength` | only `setMaxLength()`; no minimum |
| `word-limit-position` | counter is always inside |
| `label` / `aria-label` | accessibility metadata not exposed |
| `clear` event | not emitted separately |

## Differences from Element Plus

1. **Single text signal.** Element Plus distinguishes `input` (every keystroke)
   from `change` (on blur or Enter, only when the value actually changed), and
   additionally emits `clear`, `focus`, `blur` and `keydown`. `ZInput` emits
   only `textChanged()`.
2. **Icons are `QChar` glyphs, not SVG components, and `IconManager` is not
   used.** Element Plus accepts an icon component for `prefix-icon` /
   `suffix-icon`. `ZInput::setPrefixIcon()` takes a `QChar` code point that is
   drawn directly with the widget font, so only glyphs present in the active
   font can be used, and no tinting or caching applies.
3. **Prepend / append are widget slots, not slots in the Vue sense.**
   `setPrependWidget()` / `setAppendWidget()` accept any `QWidget`, which is
   more flexible than the Element Plus `prepend` / `append` content slots.
4. **`autosize` is two properties.** Element Plus accepts `boolean | object`
   (`{ minRows, maxRows }`); `ZInput` uses `setAutosize()` plus
   `setAutosizeMinRows()` / `setAutosizeMaxRows()`.
5. **The word counter needs a non-zero `setMaxLength()`.** `showWordLimit` only
   renders the `count / max` label once a positive maximum length is set;
   otherwise the counter stays hidden even though `isShowWordLimit()` is `true`.
6. **The password toggle is `passwordMode`.** Element Plus uses
   `show-password`, which keeps the value masked but adds a reveal control.
   `ZInput::setPasswordMode(true)` switches the underlying echo mode directly.
7. **No exposed imperative methods.** Element Plus exposes `focus()`, `blur()`,
   `select()`, `clear()` and `resizeTextarea()`; `ZInput` only exposes
   `lineEdit()`, which already provides all of them.

## Future Roadmap

- `focus()` / `blur()` / `select()` / `clear()` forwarding helpers
- `input` vs `change` signal split, plus a dedicated `cleared()` signal
- Formatter / parser hooks
- Custom clear and password icons through `IconManager`
- Grapheme-aware counting for the word-limit counter
