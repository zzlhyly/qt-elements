# ZTooltip

Element Plus reference: <https://element-plus.org/en-US/component/tooltip.html>

Header: `coding/uicontrols/src/widgets/tooltip/ztooltip.h`
Popup engine: [`ZPopup`](../coding/uicontrols/src/popup/zpopup.h)

## Introduction

`ZTooltip` attaches a tooltip to any `QWidget`. It is a `QObject`, not a widget:
it installs an event filter on a target widget and shows a `ZPopup` on hover or
on demand.

The official Element Plus page lists eleven demos; `ZTooltip` covers basic hover,
light/dark theme, placement, show delay, and manual (controlled) triggering.

## Class Diagram

```
QObject
└── ZTooltip
      ├── QWidget*           target_
      ├── QString            text_
      ├── ZPopup*            popup_
      ├── ZPopup::Placement  placement_
      ├── Effect             effect_
      ├── Trigger            trigger_
      ├── int                showDelay_ / hideDelay_
      └── QTimer*            show_timer_ / hide_timer_
```

Collaborators:

```
ZTooltip ──uses──> ZPopup             positioned, screen-fitted popup container
         ──uses──> QTimer             show / hide scheduling
         ──installs──> QObject::eventFilter on target_  (hover detection)
```

`ZPopup` placements: `kBottom`, `kTop`, `kLeft`, `kRight`. `ZPopup::showAt()`
fits the popup to screen boundaries automatically.

## Public API

### Enums

| Enum | Values |
|------|--------|
| `Effect` | `kDark`, `kLight` |
| `Trigger` | `kHover`, `kManual` |

### Properties (`Q_PROPERTY`)

| Property | Type | Default | Accessors |
|----------|------|---------|-----------|
| `text` | `QString` | empty | `setText()` / `text()` |
| `showDelay` | `int` | `500` (ms) | `setShowDelay()` / `showDelay()` |
| `hideDelay` | `int` | `0` (ms) | `setHideDelay()` / `hideDelay()` |
| `effect` | `Effect` | `kDark` | `setEffect()` / `effect()` |
| `trigger` | `Trigger` | `kHover` | `setTrigger()` / `trigger()` |

### Constructors

```cpp
explicit ZTooltip(QObject* parent = nullptr);
~ZTooltip() override;
```

### Binding and appearance

```cpp
void setTarget(QWidget* widget);
void setText(const QString& text);
void setPlacement(ZPopup::Placement p);
void setShowDelay(int ms);
void setHideDelay(int ms);
void setEffect(Effect e);
void setTrigger(Trigger t);
```

### Manual control

```cpp
void show();
void hide();
```

### Static helpers

```cpp
static void showText(QWidget* target, const QString& text,
                     Effect effect = kDark, int duration = 3000);

static void install(QWidget* target, const QString& text,
                    ZPopup::Placement placement = ZPopup::kTop,
                    Effect effect = kDark);
```

`showText()` displays a one-shot tooltip that auto-hides after `duration` ms.
`install()` creates a persistent hover tooltip as a child of `target`.

### Signals

None.

## Demos

| Demo | Source |
|------|--------|
| Hover | [`hover.cpp`](../coding/uicontrols/examples/tooltip/hover.cpp) |
| Static | [`static.cpp`](../coding/uicontrols/examples/tooltip/static.cpp) |
| Delay | [`delay.cpp`](../coding/uicontrols/examples/tooltip/delay.cpp) |
| Placement | [`placement.cpp`](../coding/uicontrols/examples/tooltip/placement.cpp) |
| Manual | [`manual.cpp`](../coding/uicontrols/examples/tooltip/manual.cpp) |

## Supported Features

- hover and manual triggers
- dark and light effects
- four placements with automatic screen fitting
- configurable show and hide delays
- one-shot `showText()` with an auto-hide duration
- convenience `install()` for the common hover case

## Unsupported Features

| Element Plus | Status |
|--------------|--------|
| `raw-content` (HTML content) | not implemented — plain text only |
| `content` / `default` slots (arbitrary widget content) | not implemented |
| `virtual-triggering` / `virtual-ref` | not implemented |
| `persistent` | not implemented (the popup is always kept alive) |
| `enterable` (mouse may enter the tooltip) | not implemented |
| `show-arrow` control | the popup always draws its arrow |
| `transition` / `popper-class` / `popper-style` | not applicable to Qt |
| `trigger-keys` | not implemented — no keyboard trigger |
| `offset` / `arrow-offset` | fixed in `ZPopup` |
| `auto-close` | not implemented; use `showText()`'s duration |
| `fallback-placements` | `ZPopup` fits to screen but has no placement fallback |
| `append-to` / `teleported` | not applicable to Qt |
| `before-show` / `show` / `before-hide` / `hide` events | not emitted |
| `disabled` | not implemented; detach or destroy the `ZTooltip` instead |

## Differences from Element Plus

1. **No visibility signal or state query.** Element Plus exposes `visible`
   (`v-model`) plus `before-show`, `show`, `before-hide` and `hide` events, and
   `updatePopper()` / `hide()` as exposed methods. `ZTooltip` has `show()` /
   `hide()` but no `isVisible()` and no lifecycle signals.
2. **`trigger` has two values instead of an enum or array.** Element Plus
   accepts `hover | click | focus | contextmenu` (or an array). `ZTooltip`
   supports `kHover` and `kManual` only; click and focus triggers must be wired
   by the application calling `show()` / `hide()`.
3. **Controlled mode is partial.** Element Plus documents that in controlled
   mode `trigger`, `show-after`, `hide-after` and `auto-close` are invalid.
   With `ZTooltip::kManual` the delays simply never apply, which gives the same
   outcome but is not enforced.
4. **Hover detection uses an event filter, not real `QEvent::ToolTip`.** Qt has
   a native tooltip channel; `ZTooltip` bypasses it so it can control delay and
   appearance. A widget can therefore have both a native `QToolTip` and a
   `ZTooltip`.
5. **No rich content.** Element Plus supports HTML content with an explicit XSS
   warning; `ZTooltip::text` is a `QString` rendered as plain text, so no
   sanitisation concerns arise.
6. **One tooltip per target.** `install()` creates a new `ZTooltip` parented to
   the target each time; calling it twice on the same widget yields two
   tooltips.

## Future Roadmap

- `clicked` and `focus` trigger modes
- Arbitrary widget content (`setContentWidget()`)
- Lifecycle signals (`aboutToShow()`, `aboutToHide()`) and `isVisible()`
- Configurable offset and arrow visibility
- Guard against duplicate `install()` on the same target
- Keyboard trigger support (`trigger-keys` equivalent)
