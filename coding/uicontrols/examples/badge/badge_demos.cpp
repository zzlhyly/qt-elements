#include "badge/badge_demos.h"

#include "demo/demo_registry.h"

void RegisterBadgeDemos(demo::DemoRegistry& registry) {
    demo::DemoGroup group("Badge");
    group.Add("Basic", &ZBadgeDemoBasic);
    group.Add("Dot", &ZBadgeDemoDot);
    group.Add("Max", &ZBadgeDemoMax);
    registry.AddGroup(group);
}
