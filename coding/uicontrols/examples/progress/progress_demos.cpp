#include "progress/progress_demos.h"

#include "demo/demo_registry.h"

void RegisterProgressDemos(demo::DemoRegistry& registry) {
    demo::DemoGroup group("Progress");
    group.Add("Circle", &ZProgressDemoCircle);
    group.Add("Dashboard", &ZProgressDemoDashboard);
    group.Add("Indeterminate", &ZProgressDemoIndeterminate);
    group.Add("Line", &ZProgressDemoLine);
    group.Add("Show Text", &ZProgressDemoShowText);
    group.Add("Status", &ZProgressDemoStatus);
    group.Add("Stroke Width", &ZProgressDemoStrokeWidth);
    group.Add("Text Inside", &ZProgressDemoTextInside);
    registry.AddGroup(group);
}
