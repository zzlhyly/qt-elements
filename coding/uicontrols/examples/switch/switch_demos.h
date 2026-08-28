// switch_demos.h - Declares every Switch demo and registers them with the
// gallery's DemoRegistry.

#ifndef UICONTROLS_EXAMPLES_SWITCH_SWITCH_DEMOS_H_
#define UICONTROLS_EXAMPLES_SWITCH_SWITCH_DEMOS_H_

class QWidget;

namespace demo { class DemoRegistry; }

QWidget* ZSwitchDemoBasic();
QWidget* ZSwitchDemoActiveText();
QWidget* ZSwitchDemoDisabled();
QWidget* ZSwitchDemoLoading();
QWidget* ZSwitchDemoSizes();
QWidget* ZSwitchDemoWithLabel();

void RegisterSwitchDemos(demo::DemoRegistry& registry);

#endif  // UICONTROLS_EXAMPLES_SWITCH_SWITCH_DEMOS_H_
