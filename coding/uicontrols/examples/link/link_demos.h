// link_demos.h - Declares every Link demo and registers them with the
// gallery's DemoRegistry.

#ifndef UICONTROLS_EXAMPLES_LINK_LINK_DEMOS_H_
#define UICONTROLS_EXAMPLES_LINK_LINK_DEMOS_H_

class QWidget;

namespace demo { class DemoRegistry; }

QWidget* ZLinkDemoBasic();
QWidget* ZLinkDemoDisabled();
QWidget* ZLinkDemoTypes();
QWidget* ZLinkDemoUnderline();

void RegisterLinkDemos(demo::DemoRegistry& registry);

#endif  // UICONTROLS_EXAMPLES_LINK_LINK_DEMOS_H_
