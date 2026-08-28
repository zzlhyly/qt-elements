#include "checkbox/checkbox_demos.h"

#include "demo/demo_registry.h"

void RegisterCheckboxDemos(demo::DemoRegistry& registry) {
    demo::DemoGroup group("Checkbox");
    group.Add("Basic", &ZCheckboxDemoBasic);
    group.Add("Border", &ZCheckboxDemoBorder);
    group.Add("Button Style", &ZCheckboxDemoButtonStyle);
    group.Add("Disabled", &ZCheckboxDemoDisabled);
    group.Add("Group", &ZCheckboxDemoGroup);
    group.Add("Indeterminate", &ZCheckboxDemoIndeterminate);
    registry.AddGroup(group);
}
