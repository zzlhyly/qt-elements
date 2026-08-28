# ZCheckboxGroup

Element Plus reference: <https://element-plus.org/en-US/component/checkbox.html>

## Introduction

`ZCheckboxGroup` is the Element Plus Checkbox Group: a container that owns a
`QList<int>` model of selected values, coordinates its `ZCheckbox` children, and
enforces `min` / `max` selection counts.

It is the only group container in the library so far. Unlike Element Plus, there
is no group-level `border` on the group itself — `setBorder()` propagates to the
child checkboxes.

## Class Diagram

```
QObject
└── QWidget
    └── ZCheckboxGroup
          ├── QList<int>        value_
          ├── GroupType         type_
          ├── Size              size_
          ├── bool              border_ / disabled_
          ├── int               min_ / max_
          ├── QVBoxLayout*      layout_
          ├── QList<ZCheckbox*> checkboxes_
          └── QList<int>        checkbox_values_
```

Collaborators:

```
ZCheckboxGroup ──owns──> QVBoxLayout  child arrangement
               ──owns──> ZCheckbox[]  registered via addCheckbox()
```

## Public API

Header: `coding/uicontrols/src/widgets/checkboxgroup/zcheckboxgroup.h`

### Enums

| Enum | Values |
|------|--------|
| `GroupType` | `kDefault`, `kButton` |
| `Size` | `kDefault`, `kLarge`, `kSmall` |

Both are `enum class`, so values are scoped: `ZCheckboxGroup::GroupType::kButton`.

### Properties (`Q_PROPERTY`)

| Property | Type | Default | Accessors |
|----------|------|---------|-----------|
| `value` | `QList<int>` | empty | `setValue()` / `value()` |
| `type` | `GroupType` | `kDefault` | `setType()` / `type()` |
| `border` | `bool` | `false` | `setBorder()` / `border()` |
| `min` | `int` | `0` | `setMin()` / `min()` |
| `max` | `int` | `0` | `setMax()` / `max()` |
| `disabled` | `bool` | `false` | `setDisabled()` / `isDisabled()` |

`size` has a setter/getter pair (`setSize()` / `size()`) but is not declared as a
`Q_PROPERTY`.

### Constructors

```cpp
explicit ZCheckboxGroup(QWidget* parent = nullptr);
```

### Population

```cpp
void addCheckbox(ZCheckbox* checkbox, int checkboxValue);
```

Takes ownership of the checkbox (reparents it into the group's internal
`QVBoxLayout`) and associates it with the integer value used in the model.

### Signals

| Signal | Emitted when |
|--------|--------------|
| `valueChanged(const QList<int>&)` | the selected set changes |

## Demos

| Demo | Source |
|------|--------|
| Group | [`group.cpp`](../coding/uicontrols/examples/checkbox/group.cpp) |
| Button Style | [`button_style.cpp`](../coding/uicontrols/examples/checkbox/button_style.cpp) |

Related: the individual [`ZCheckbox`](Checkbox.md) demos cover the child control.

## Supported Features

- integer-valued multi-selection model
- `min` / `max` selection constraints
- `kButton` group type for button-style rendering
- border propagation to children
- group-level disabled state and size
- `valueChanged` notification

## Unsupported Features

| Element Plus | Status |
|--------------|--------|
| `options` / `props` data-driven rendering | not implemented — `addCheckbox()` only |
| `text-color` / `fill` (active button colours) | not implemented; use `theme::` |
| `tag` (render as a different element) | not applicable to Qt |
| Horizontal arrangement | internal layout is a `QVBoxLayout` only |
| `validate-event`, `aria-label` | not applicable to Qt |

## Differences from Element Plus

1. **Model values are `int`.** Element Plus supports `string | number | object`
   values plus `true-value` / `false-value`. `ZCheckboxGroup` uses `QList<int>`,
   which keeps the API simple but excludes string and object models.
2. **Vertical only.** The internal layout is a `QVBoxLayout`; `ZCheckboxGroup`
   cannot lay its children out horizontally. Element Plus renders inline and
   lets CSS decide.
3. **`min` / `max` are enforced by rejection, not by disabling.** When the
   selection is at `max`, additional checkboxes are refused rather than being
   visually disabled. Element Plus behaves the same way for `max`, but with a
   disabled visual cue in some versions.
4. **`border` and `size` cascade differently.** In Element Plus, `size` and
   `border` are props of each checkbox and can be set on the group as a
   convenience. Here they live on the group only and are pushed down to
   children.
5. **`type` is `kDefault` / `kButton`.** Element Plus has separate
   `el-checkbox` and `el-checkbox-button` child components; here the same
   `ZCheckbox` child is restyled by the group's `GroupType`.

## Future Roadmap

- Horizontal and grid arrangement (`setDirection()`, `setColumns()`)
- `options` / `props` style bulk population from a data model
- `textColor` / `fill` for button style
- Templated value type, or a `QVariant`-based model, to support string values
- Disable-at-max visual cue
