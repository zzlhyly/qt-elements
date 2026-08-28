#include "switch/switch_demos.h"

#include "demo/demo_registry.h"

void RegisterSwitchDemos(demo::DemoRegistry& registry) {
    demo::DemoGroup group("Switch");
    group.Add("Basic", &ZSwitchDemoBasic);
    group.Add("Active Text", &ZSwitchDemoActiveText);
    group.Add("Disabled", &ZSwitchDemoDisabled);
    group.Add("Loading", &ZSwitchDemoLoading);
    group.Add("Sizes", &ZSwitchDemoSizes);
    group.Add("With Label", &ZSwitchDemoWithLabel);
    registry.AddGroup(group);
}
