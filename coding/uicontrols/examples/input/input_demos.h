// input_demos.h - Declares every Input demo and registers them with the
// gallery's DemoRegistry.

#ifndef UICONTROLS_EXAMPLES_INPUT_INPUT_DEMOS_H_
#define UICONTROLS_EXAMPLES_INPUT_INPUT_DEMOS_H_

class QWidget;

namespace demo { class DemoRegistry; }

QWidget* ZInputDemoBasic();
QWidget* ZInputDemoAutosize();
QWidget* ZInputDemoClearable();
QWidget* ZInputDemoDisabled();
QWidget* ZInputDemoPassword();
QWidget* ZInputDemoPrependAppend();
QWidget* ZInputDemoSize();
QWidget* ZInputDemoTextarea();
QWidget* ZInputDemoWithIcon();
QWidget* ZInputDemoWordLimit();

void RegisterInputDemos(demo::DemoRegistry& registry);

#endif  // UICONTROLS_EXAMPLES_INPUT_INPUT_DEMOS_H_
