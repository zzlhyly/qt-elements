// slider_demos.h - Declares every Slider demo and registers them with the
// gallery's DemoRegistry.

#ifndef UICONTROLS_EXAMPLES_SLIDER_SLIDER_DEMOS_H_
#define UICONTROLS_EXAMPLES_SLIDER_SLIDER_DEMOS_H_

class QWidget;

namespace demo { class DemoRegistry; }

QWidget* ZSliderDemoBasic();
QWidget* ZSliderDemoDisabled();
QWidget* ZSliderDemoRange();
QWidget* ZSliderDemoStops();
QWidget* ZSliderDemoVertical();

void RegisterSliderDemos(demo::DemoRegistry& registry);

#endif  // UICONTROLS_EXAMPLES_SLIDER_SLIDER_DEMOS_H_
