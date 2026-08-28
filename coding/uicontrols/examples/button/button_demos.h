// button_demos.h - Declares every Button demo and registers them with the
// gallery's DemoRegistry.

#ifndef UICONTROLS_EXAMPLES_BUTTON_BUTTON_DEMOS_H_
#define UICONTROLS_EXAMPLES_BUTTON_BUTTON_DEMOS_H_

class QWidget;

namespace demo { class DemoRegistry; }

QWidget* ZButtonDemoBasic();
QWidget* ZButtonDemoButtonGroup();
QWidget* ZButtonDemoCircle();
QWidget* ZButtonDemoColor();
QWidget* ZButtonDemoDashed();
QWidget* ZButtonDemoDisabled();
QWidget* ZButtonDemoIcon();
QWidget* ZButtonDemoLink();
QWidget* ZButtonDemoLoading();
QWidget* ZButtonDemoPlain();
QWidget* ZButtonDemoRound();
QWidget* ZButtonDemoSize();
QWidget* ZButtonDemoText();

void RegisterButtonDemos(demo::DemoRegistry& registry);

#endif  // UICONTROLS_EXAMPLES_BUTTON_BUTTON_DEMOS_H_
