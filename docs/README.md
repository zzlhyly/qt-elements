# Component Documentation

Reference documentation for every completed component in `coding/uicontrols`.
Each page documents the Qt API as implemented in this repository and states
precisely which Element Plus features are missing.

Component scope and ordering follow [`COMPONENTS.md`](../COMPONENTS.md).
Architecture rules live in [`AGENTS.md`](../AGENTS.md).

## Completed components

### Tier 1 — Simple leaf

| Component | Description |
|-----------|-------------|
| [ZButton](Button.md) | 6 types, 5 variants, 3 sizes, round / circle, loading |
| [ZTag](Tag.md) | 5 types, 3 effects, 3 sizes, closable, round, hit |
| [ZBadge](Badge.md) | 5 types, dot mode, max clamping, hidden state |
| [ZDivider](Divider.md) | horizontal / vertical, solid / dashed / dotted, labelled |
| [ZLink](Link.md) | 6 types, optional underline, disabled |
| [ZText](Text.md) | 6 types, 3 sizes, single-line truncation |
| [ZAlert](Alert.md) | 4 types, light / dark effect, icon, closable, centered |

### Tier 2 — Core form

| Component | Description |
|-----------|-------------|
| [ZInput](Input.md) | 3 sizes, clearable, password, textarea, autosize, word limit |
| [ZRadio](Radio.md) | radio indicator, border mode (group via `QButtonGroup`) |
| [ZCheckbox](Checkbox.md) | tri-state checkbox (checked / unchecked / indeterminate) |
| [ZCheckboxGroup](CheckboxGroup.md) | integer model, min / max constraints, button style |
| [ZSwitch](Switch.md) | 3 sizes, animated slide, loading, active / inactive text |
| [ZSlider](Slider.md) | horizontal / vertical, step snapping, stop markers |
| [ZProgress](Progress.md) | line / circle / dashboard, status colours, indeterminate |

### Tier 3 — Overlay

| Component | Description |
|-----------|-------------|
| [ZTooltip](Tooltip.md) | hover / manual trigger, dark / light effect, 4 placements |

## Shared foundation

Every component above is built on the same foundation modules; refer to them
before adding new controls.

| Module | Path | Responsibility |
|--------|------|----------------|
| Theme | `coding/uicontrols/src/theme/theme.h` | all colour, size, spacing and typography tokens |
| Style | `coding/uicontrols/src/style/style.h` | `(type x state x variant)` -> resolved visual structs |
| Painter | `coding/uicontrols/src/painter/painter.h` | `DrawBackground`, `DrawBorder`, `DrawText`, `DrawIcon`, `DrawFocusRing`, `DrawShadow`, `DrawStateOverlay` |
| State machine | `coding/uicontrols/src/statemachine/statemachine.h` | `ComponentState` + `StateTracker` |
| Animation | `coding/uicontrols/src/animation/animation_manager.h` | single owner of all `QVariantAnimation` instances |
| Icon | `coding/uicontrols/src/icon/icon_manager.h` | SVG / PNG / font glyph loading, tinting, caching |
| Popup | `coding/uicontrols/src/popup/zpopup.h` | screen-fitted positioned overlay container |

## Running the demos

Every documented demo is a standalone function in
`coding/uicontrols/examples/<component>/`, registered with the gallery through
`<component>/<component>_demos.cpp` and rendered by
`coding/uicontrols/src/gallery.cpp`.

```powershell
cmake -S coding -B build -G "Visual Studio 18 2026" -A Win32
cmake --build build --config Debug
```

The resulting `build/product/uicontrols/uicontrols.exe` shows a sidebar with one
entry per component and one titled section per demo.
