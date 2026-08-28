// badge_demos.h - Declares every Badge demo and registers them with the
// gallery's DemoRegistry.

#ifndef UICONTROLS_EXAMPLES_BADGE_BADGE_DEMOS_H_
#define UICONTROLS_EXAMPLES_BADGE_BADGE_DEMOS_H_

class QWidget;

namespace demo { class DemoRegistry; }

QWidget* ZBadgeDemoBasic();
QWidget* ZBadgeDemoDot();
QWidget* ZBadgeDemoMax();

void RegisterBadgeDemos(demo::DemoRegistry& registry);

#endif  // UICONTROLS_EXAMPLES_BADGE_BADGE_DEMOS_H_
