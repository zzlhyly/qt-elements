// divider_demos.h - Declares every Divider demo and registers them with the
// gallery's DemoRegistry.

#ifndef UICONTROLS_EXAMPLES_DIVIDER_DIVIDER_DEMOS_H_
#define UICONTROLS_EXAMPLES_DIVIDER_DIVIDER_DEMOS_H_

class QWidget;

namespace demo { class DemoRegistry; }

QWidget* ZDividerDemoBasic();
QWidget* ZDividerDemoDashedDotted();
QWidget* ZDividerDemoVertical();
QWidget* ZDividerDemoWithText();

void RegisterDividerDemos(demo::DemoRegistry& registry);

#endif  // UICONTROLS_EXAMPLES_DIVIDER_DIVIDER_DEMOS_H_
