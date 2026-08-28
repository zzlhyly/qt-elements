#include "divider/divider_demos.h"

#include "demo/demo_registry.h"

void RegisterDividerDemos(demo::DemoRegistry& registry) {
    demo::DemoGroup group("Divider");
    group.Add("Basic", &ZDividerDemoBasic);
    group.Add("Dashed / Dotted", &ZDividerDemoDashedDotted);
    group.Add("Vertical", &ZDividerDemoVertical);
    group.Add("With Text", &ZDividerDemoWithText);
    registry.AddGroup(group);
}
