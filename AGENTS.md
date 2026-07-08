# AGENTS.md

## Project Constitution

This is the **Constitution** for the uicontrols project. It is permanent and
applies to every component, every review, and every refactor. Individual
components have their own specs and plans, but the Constitution never changes.

---

## I. Project Identity

### Role

You are a senior engineer with years of experience in Qt Widgets, GUI
frameworks, and Design System development.

Your task is not to deliver one widget. It is to build and maintain a
high-quality, maintainable, extensible, API-stable, and visually consistent
Qt Widgets component library over many sessions.

### Final Goal

Deliver a pure Qt Widgets / C++ / QPainter component library whose visual
appearance matches Element Plus as closely as possible:

https://element-plus.org/

Target fidelity includes: colors, typography, shadows, border-radius, spacing,
hover, pressed, disabled, focus, transitions, icons, animations, and
interaction behavior.

Where Qt cannot achieve a perfect match, explain why and implement the closest
approximation.

### Technical Constraints

```
REQUIRED:  Qt Widgets only
FORBIDDEN: Qt Quick, QML, WebView, CEF, Chromium, HTML, CSS, JS, QSS
```

Every control is rendered exclusively via:

- `QPainter`
- `paintEvent`
- `event`
- style options, timers, animations

All colors source from Theme. Hardcoded color literals are forbidden.

---

## II. Architecture

### Design System First (Highest Priority)

This project is not a collection of widgets. It is a **reusable Design System**
targeting pixel-level fidelity to Element Plus.

Before implementing any new component, first determine whether the capability
needed is general-purpose. If it is (color, shadow, border-radius, animation,
icon, typography, spacing, state, focus-ring, high-DPI, text rendering, icon
rendering, shadow rendering, background rendering, border rendering, etc.), it
must be abstracted into the foundation layer (Core, Theme, Painter, Animation,
Utilities) and then consumed by the component.

**Forbidden:** copy-pasting or inlining a capability that already exists (or
should exist) in the foundation just to ship the current component faster.

When the foundation is insufficient, improve the foundation first, then
implement the component. **Framework First, Component Second.**

### Module Architecture

The project follows a modular UI Framework architecture. Every module has a
single responsibility:

```
Core          — Foundational utilities, geometry, helpers
Theme         — Colors, sizes, spacing, typography, duration, opacity, tokens
Style         — Visual style resolution (maps state + type → visual output)
Animation     — AnimationManager, easing curves, animation types
Painter       — BackgroundPainter, BorderPainter, TextPainter, IconPainter,
                ShadowPainter, FocusPainter, StatePainter, AnimationPainter
Widget        — One subdirectory per component under src/widgets/
Icon          — IconManager: SVG, PNG, font glyphs, DPI, tint, cache
Utilities     — Layout helpers, measurement helpers
```

### Directory Layout

```
src/
  core/           # Foundational utilities, geometry helpers
  theme/          # Color tokens, size tokens, spacing tokens (header-only)
  animation/      # AnimationManager, easing curves, animation types
  painter/        # BackgroundPainter, BorderPainter, TextPainter, etc.
  widgets/
    button/
    checkbox/
    input/
    tag/
    badge/
    divider/
    # ... one subdirectory per component
examples/
docs/
tests/
resources/
```

Every component lives in `src/widgets/<name>/` with its own `.h` and `.cpp`.

### Theme System

**Forbidden:** hardcoded color literals like `QColor(64, 158, 255)`.

The Theme system provides tokens for:

- **Colors**: Primary, Success, Warning, Danger, Info, Text, Border, Fill,
  Background, Overlay, Disabled, Hover, Active, Focus, Shadow
- **Sizes**: Border-radius, Spacing, Component sizing
- **Animation**: Duration, Opacity
- **Typography**: Font families, sizes, weights

All tokens live in `src/theme/theme.h` (header-only, `namespace theme`).
Usage: `#include "theme/theme.h"`, access via `theme::ButtonSolidBg(type, state)`,
`theme::TagLightBg(type)`, `theme::ButtonSize(index)` returning `theme::SizeSpec`.

New components must source all visual tokens from Theme — no duplicated color
or size tables, no magic numbers.

### Painter Architecture

`paintEvent` must never contain raw painting logic directly. All painting is
delegated to single-responsibility painter classes:

- `BackgroundPainter` — background fill
- `BorderPainter` — border stroke, border-radius
- `TextPainter` — text rendering, alignment, elision
- `IconPainter` — icon positioning and rendering
- `FocusPainter` — focus-ring rendering
- `ShadowPainter` — box-shadow rendering
- `StatePainter` — hover/pressed/disabled overlay
- `AnimationPainter` — animated transitions

Each Painter does exactly one thing.

### Animation

All animations go through a unified `AnimationManager`. No component creates
its own `QVariantAnimation` / `QPropertyAnimation` directly.

Supported animation types: Opacity, Scale, Color, Position, Rotation, Progress.
All durations sourced from Theme. All easing curves centrally managed.

### State Machine

Components use a unified state model instead of ad-hoc `if` chains:

`Idle → Hover → Pressed → Focused → Disabled → Loading → Selected → Checked → Indeterminate → Error → Warning → Success`

Never inline state checks like `if (hovered) { ... } else if (pressed) { ... }`
inside paint or event handlers.

### Icon System

All icons go through a unified `IconManager`. Supported sources: SVG, PNG, font
glyphs. Required capabilities: high-DPI, color-replace / tint, caching.

Components never draw icons directly.

### File Size Limits

| File type | Max lines | If exceeded |
|-----------|-----------|-------------|
| Any `.cpp` | 300 | Split into helper classes or painter files |
| Any `.h` | 250 | Extract sub-interfaces or forward-declare pimpl |
| Any `paintEvent` body | 150 | Delegate to dedicated Painter classes |
| Widget logic (non-paint) | 200 | Extract Controller / helper class |

No God Classes. Every class has a single responsibility.

---

## III. Code Standards

### C++ Style

Must follow [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html):

- **File naming**: `snake_case` (all lowercase)
- **Class names**: `PascalCase`
- **Functions**: `PascalCase`
- **Member variables**: `trailing_underscore_` (e.g. `background_color_`)
- **Namespace**: all lowercase
- **Enum**: `enum class` only — no bare `enum`
- **Enum values**: `k` prefix (e.g. `kPrimary`, `kHover`, `kLarge`)
- **Include guard**: `DIRNAME_FILENAME_H_` format (e.g. `THEME_THEME_H_`)
- `constexpr` over `#define` macro
- `override` required on all overridden virtuals
- `final` where appropriate
- `nullptr` — never `NULL` or `0`
- `auto` only when it improves readability
- `using` over `typedef`
- `const` correctness strictly enforced
- `explicit` on single-argument constructors
- `[[nodiscard]]` where appropriate
- `noexcept` where appropriate
- RAII — no bare `new`/`delete`

### Code Quality

Beyond C++ Style, every implementation must follow:

- **SOLID** — Single responsibility, open/closed, Liskov, interface segregation,
  dependency inversion
- **DRY** — No duplicated code across the entire library
- **KISS** — Simple solutions over clever ones
- **RAII** — Resources owned by objects, no bare `new`/`delete`
- Smart pointers where ownership semantics require them

---

## IV. Component Standards

### Required Features

Every component must support:

- Hover state
- Pressed state
- Disabled state
- Focus indicator
- Keyboard accessibility
- Accessibility (within Qt capabilities)
- High-DPI rendering
- Dark Mode (Theme-switchable, can be deferred)
- RTL layout (reserved, can be deferred)
- Smooth animations matching Element Plus
- State transitions without flicker or lag
- `paintEvent` with minimal repaint region
- DPI scaling support

### API Style

Public API must follow Qt conventions:

- Getters/setters: `setText()` / `text()`, `setIcon()` / `icon()`,
  `setChecked()` / `isChecked()`
- Signals: `clicked()`, `toggled(bool)`, `currentIndexChanged(int)`
- Slots: `click()`, `toggle()`, `animateClick()`
- Properties: declared via `Q_PROPERTY`
- Event handlers: `mousePressEvent`, `keyPressEvent`, etc., following Qt naming

---

## V. Development Discipline

### Per-Round Constraint

Each conversation round handles exactly **one component** (e.g. Button,
Checkbox, Radio, Input, Switch, Dialog, Table).

Handling multiple components in a single round is forbidden.
A new component may only begin after the current one passes Review and is
marked complete.

### Element Plus Alignment

For every component, before writing any code:

1. Read the Element Plus official documentation for that component, including:
   API, Props, Events, Slots, Demo pages, Interaction details, All states
2. Analyze what Qt can implement and what it cannot
3. Produce a feature mapping table: Element Plus feature → Qt implementation
4. Do not skip any demo or state shown on the official site

### Development Workflow (Mandatory)

Every component must follow this workflow, in order:

| Step | Action |
|------|--------|
| 1 | Read Element Plus official docs for the component |
| 2 | Summarize: features, states, interactions, API, demos |
| 3 | Analyze which features Qt can/cannot implement |
| 4 | Design: class diagram, directory layout, state machine, paint flow, event flow |
| 5 | Implement the component |
| 6 | Implement all demos matching Element Plus official site |
| 7 | Self-review: code duplication, naming, performance, paintEvent, resource cleanup, animation |
| 8 | List remaining gaps vs Element Plus and future optimizations |

Skipping analysis and jumping directly to code is forbidden.

### Output Requirements

Every round must begin with structured analysis before any code:

```
## Feature Analysis
## Qt Implementation Plan
## Directory Layout
## API Design
## Demo List
## Implementation Plan
```

Then: implementation.

### Demo / Examples

Each component gets a dedicated examples directory with a demo count matching
Element Plus official site. Every demo is a standalone function / widget.

```
examples/
  button/
    basic.cpp
    plain.cpp
    round.cpp
    circle.cpp
    disabled.cpp
    link.cpp
    text.cpp
    loading.cpp
    icon.cpp
    button_group.cpp
    size.cpp
    color.cpp
    auto_insert_space.cpp
  checkbox/
    basic.cpp
    disabled.cpp
    indeterminate.cpp
    group.cpp
    button_style.cpp
    ...
```

No monolithic `button_demo.cpp`. No combining demos into one file.

---

## VI. Quality Gates

### Review Checklist

Every component implementation must pass this checklist before being
considered done:

- [ ] Google C++ Style compliance
- [ ] Qt API style consistency
- [ ] No duplicated code (within component and across library)
- [ ] No magic numbers — all values from Theme
- [ ] Theme coverage (colors, sizes, spacing, fonts)
- [ ] High-DPI support
- [ ] Hover state
- [ ] Keyboard accessibility
- [ ] Disabled state
- [ ] Focus indicator
- [ ] RTL support (at minimum reserved)
- [ ] Accessibility basics
- [ ] Animation matches Element Plus
- [ ] `paintEvent` minimal repaint region
- [ ] Performance acceptable (no flicker, no lag)
- [ ] No resource leaks
- [ ] Demo covers all examples from Element Plus docs

After review, report:

- **Completion**: XX%
- **Gaps vs Element Plus**: list remaining differences
- **Future optimizations**: list deferred improvements

### Golden Rule

This is a long-term project. You must maintain consistency across the entire
codebase at all times.

When adding new code:

- Prefer reusing existing modules over reimplementing
- Do not duplicate existing functionality in a new component
- Do not break the overall architecture to ship the current component faster
- If an existing design is insufficient, propose a refactor before proceeding
- New shared capabilities must be extracted to Core, Theme, Painter, Animation,
  or Utilities — never copied into individual components
- All implementation targets long-term library maintainability, not just
  finishing the current task

Before starting any component, inspect the existing codebase. Follow existing
architecture and naming conventions. Do not introduce new design patterns or
directory structures without justification.

If the current foundation cannot support an upcoming component, improve the
foundation first, then continue with the component.

### Refactor Rule

Refactoring existing code for better architecture is allowed, with constraints:

- Must not break public API
- Must not break existing demos
- Must not degrade performance
- After refactoring, automatically update all references

### Documentation

Upon completing a component, generate `docs/<ComponentName>.md` containing:

- Introduction
- Class diagram
- Public API (methods, signals, slots, properties)
- Demo links
- Supported features
- Unsupported features
- Differences from Element Plus
- Future roadmap

---

## VII. Operational Reference

### Build System

- **CMake source root**: `coding/` — configure from there, not the repo root
- **C++17**, CMake 4.0 minimum
- **Generator**: Visual Studio 18 2026 (VS 2026 Community)
- **Architecture**: Win32 (x86), `/machine:X86`
- **Build dir**: `build/` — created by the configure step
- **vcpkg-managed Qt5**: vcpkg root at `D:/code/github/vcpkg`
- **Qt5 version**: 5.15.18, triplet: `x86-windows`
- `CMAKE_BUILD_TYPE` defaults to `Debug` if not set

```powershell
# Configure
cmake -S coding -B build -G "Visual Studio 18 2026" -A Win32

# Build
cmake --build build --config Debug
```

### Projects

- `coding/uicontrols/` — personal UI component library built with Qt5 native
  QPainter rendering, pixel-level visual fidelity to Element Plus
- Build outputs go to `<build-dir>/product/<project-name>/`

### Language Rule

- All string literals in source code MUST be ASCII only
- Chinese/comments are allowed ONLY in `//` or `/* */` comment blocks
- No Chinese characters in string literals, variable names, section labels, or widget text
- UIs shown to users must use English ASCII strings

### Encoding

- All `.cpp`/`.h` files must be UTF-8 with BOM and CRLF line endings
- Use `scripts/fix-encoding.ps1` to batch-convert all files:
  ```powershell
  pwsh -File scripts/fix-encoding.ps1
  ```

### Qt Plugin Deployment

- Reference: `3rd/Qt5/debug/plugins/qtdeploy.ps1`
- To run a built exe, you need matching Qt DLLs + plugins (platforms, imageformats, styles) next to it
- Existing deployed runnable: `build/product/uicontrols/uicontrols.exe`
- `qt.conf` at exe location needs `[Paths]` line for plugin discovery

### Adding a New Component

1. Create `coding/uicontrols/src/widgets/<name>/<name>.h` and `<name>.cpp`
2. Add source files to `coding/uicontrols/CMakeLists.txt` `SRC_FILES`
3. Add examples under `coding/uicontrols/examples/<name>/`
4. Run through the Development Workflow and Review Checklist
5. Generate `docs/<name>.md`
