// text_demos.h - Declares every Text demo and registers them with the
// gallery's DemoRegistry.

#ifndef UICONTROLS_EXAMPLES_TEXT_TEXT_DEMOS_H_
#define UICONTROLS_EXAMPLES_TEXT_TEXT_DEMOS_H_

class QWidget;

namespace demo { class DemoRegistry; }

QWidget* ZTextDemoAllTypes();
QWidget* ZTextDemoSizes();
QWidget* ZTextDemoTruncated();
QWidget* ZTextDemoTypes();

void RegisterTextDemos(demo::DemoRegistry& registry);

#endif  // UICONTROLS_EXAMPLES_TEXT_TEXT_DEMOS_H_
