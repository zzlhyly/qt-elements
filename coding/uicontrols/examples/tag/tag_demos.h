// tag_demos.h - Declares every Tag demo and registers them with the
// gallery's DemoRegistry.

#ifndef UICONTROLS_EXAMPLES_TAG_TAG_DEMOS_H_
#define UICONTROLS_EXAMPLES_TAG_TAG_DEMOS_H_

class QWidget;

namespace demo { class DemoRegistry; }

QWidget* ZTagDemoBasic();
QWidget* ZTagDemoClosable();
QWidget* ZTagDemoRound();
QWidget* ZTagDemoSizes();
QWidget* ZTagDemoThemeDark();
QWidget* ZTagDemoThemeLight();
QWidget* ZTagDemoThemePlain();

void RegisterTagDemos(demo::DemoRegistry& registry);

#endif  // UICONTROLS_EXAMPLES_TAG_TAG_DEMOS_H_
