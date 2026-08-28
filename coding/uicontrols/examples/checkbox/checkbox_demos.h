// checkbox_demos.h - Declares every Checkbox demo and registers them with the
// gallery's DemoRegistry.

#ifndef UICONTROLS_EXAMPLES_CHECKBOX_CHECKBOX_DEMOS_H_
#define UICONTROLS_EXAMPLES_CHECKBOX_CHECKBOX_DEMOS_H_

class QWidget;

namespace demo { class DemoRegistry; }

QWidget* ZCheckboxDemoBasic();
QWidget* ZCheckboxDemoBorder();
QWidget* ZCheckboxDemoButtonStyle();
QWidget* ZCheckboxDemoDisabled();
QWidget* ZCheckboxDemoGroup();
QWidget* ZCheckboxDemoIndeterminate();

void RegisterCheckboxDemos(demo::DemoRegistry& registry);

#endif  // UICONTROLS_EXAMPLES_CHECKBOX_CHECKBOX_DEMOS_H_
