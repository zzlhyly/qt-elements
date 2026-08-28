#include "tooltip/tooltip_demos.h"

#include "demo/demo_registry.h"

void RegisterTooltipDemos(demo::DemoRegistry& registry) {
    demo::DemoGroup group("Tooltip");
    group.Add("Delay", &ZTooltipDemoDelay);
    group.Add("Hover", &ZTooltipDemoHover);
    group.Add("Manual", &ZTooltipDemoManual);
    group.Add("Placement", &ZTooltipDemoPlacement);
    group.Add("Static", &ZTooltipDemoStatic);
    registry.AddGroup(group);
}
