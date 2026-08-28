#include "radio/radio_demos.h"

#include "demo/demo_registry.h"

void RegisterRadioDemos(demo::DemoRegistry& registry) {
    demo::DemoGroup group("Radio");
    group.Add("Basic", &ZRadioDemoBasic);
    group.Add("Border", &ZRadioDemoBorder);
    group.Add("Disabled", &ZRadioDemoDisabled);
    group.Add("Vertical", &ZRadioDemoVertical);
    registry.AddGroup(group);
}
