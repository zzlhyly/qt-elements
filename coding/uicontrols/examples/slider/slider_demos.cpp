#include "slider/slider_demos.h"

#include "demo/demo_registry.h"

void RegisterSliderDemos(demo::DemoRegistry& registry) {
    demo::DemoGroup group("Slider");
    group.Add("Basic", &ZSliderDemoBasic);
    group.Add("Disabled", &ZSliderDemoDisabled);
    group.Add("Range", &ZSliderDemoRange);
    group.Add("Stops", &ZSliderDemoStops);
    group.Add("Vertical", &ZSliderDemoVertical);
    registry.AddGroup(group);
}
