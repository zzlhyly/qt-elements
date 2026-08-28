// alert_demos.h - Declares every Alert demo and registers them with the
// gallery's DemoRegistry.

#ifndef UICONTROLS_EXAMPLES_ALERT_ALERT_DEMOS_H_
#define UICONTROLS_EXAMPLES_ALERT_ALERT_DEMOS_H_

class QWidget;

namespace demo { class DemoRegistry; }

QWidget* ZAlertDemoBasic();
QWidget* ZAlertDemoCenter();
QWidget* ZAlertDemoClosable();
QWidget* ZAlertDemoDescription();
QWidget* ZAlertDemoShowIcon();
QWidget* ZAlertDemoTheme();

void RegisterAlertDemos(demo::DemoRegistry& registry);

#endif  // UICONTROLS_EXAMPLES_ALERT_ALERT_DEMOS_H_
