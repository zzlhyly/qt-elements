// progress_demos.h - Declares every Progress demo and registers them with the
// gallery's DemoRegistry.

#ifndef UICONTROLS_EXAMPLES_PROGRESS_PROGRESS_DEMOS_H_
#define UICONTROLS_EXAMPLES_PROGRESS_PROGRESS_DEMOS_H_

class QWidget;

namespace demo { class DemoRegistry; }

QWidget* ZProgressDemoCircle();
QWidget* ZProgressDemoDashboard();
QWidget* ZProgressDemoIndeterminate();
QWidget* ZProgressDemoLine();
QWidget* ZProgressDemoShowText();
QWidget* ZProgressDemoStatus();
QWidget* ZProgressDemoStrokeWidth();
QWidget* ZProgressDemoTextInside();

void RegisterProgressDemos(demo::DemoRegistry& registry);

#endif  // UICONTROLS_EXAMPLES_PROGRESS_PROGRESS_DEMOS_H_
