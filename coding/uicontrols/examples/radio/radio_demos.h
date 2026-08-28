// radio_demos.h - Declares every Radio demo and registers them with the
// gallery's DemoRegistry.

#ifndef UICONTROLS_EXAMPLES_RADIO_RADIO_DEMOS_H_
#define UICONTROLS_EXAMPLES_RADIO_RADIO_DEMOS_H_

class QWidget;

namespace demo { class DemoRegistry; }

QWidget* ZRadioDemoBasic();
QWidget* ZRadioDemoBorder();
QWidget* ZRadioDemoDisabled();
QWidget* ZRadioDemoVertical();

void RegisterRadioDemos(demo::DemoRegistry& registry);

#endif  // UICONTROLS_EXAMPLES_RADIO_RADIO_DEMOS_H_
