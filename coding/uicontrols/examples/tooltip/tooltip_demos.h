// tooltip_demos.h - Declares every Tooltip demo and registers them with the
// gallery's DemoRegistry.

#ifndef UICONTROLS_EXAMPLES_TOOLTIP_TOOLTIP_DEMOS_H_
#define UICONTROLS_EXAMPLES_TOOLTIP_TOOLTIP_DEMOS_H_

class QWidget;

namespace demo { class DemoRegistry; }

QWidget* ZTooltipDemoDelay();
QWidget* ZTooltipDemoHover();
QWidget* ZTooltipDemoManual();
QWidget* ZTooltipDemoPlacement();
QWidget* ZTooltipDemoStatic();

void RegisterTooltipDemos(demo::DemoRegistry& registry);

#endif  // UICONTROLS_EXAMPLES_TOOLTIP_TOOLTIP_DEMOS_H_
