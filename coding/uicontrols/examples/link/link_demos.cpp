#include "link/link_demos.h"

#include "demo/demo_registry.h"

void RegisterLinkDemos(demo::DemoRegistry& registry) {
    demo::DemoGroup group("Link");
    group.Add("Basic", &ZLinkDemoBasic);
    group.Add("Disabled", &ZLinkDemoDisabled);
    group.Add("Types", &ZLinkDemoTypes);
    group.Add("Underline", &ZLinkDemoUnderline);
    registry.AddGroup(group);
}
