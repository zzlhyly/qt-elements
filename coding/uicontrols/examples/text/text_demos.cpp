#include "text/text_demos.h"

#include "demo/demo_registry.h"

void RegisterTextDemos(demo::DemoRegistry& registry) {
    demo::DemoGroup group("Text");
    group.Add("All Types", &ZTextDemoAllTypes);
    group.Add("Sizes", &ZTextDemoSizes);
    group.Add("Truncated", &ZTextDemoTruncated);
    group.Add("Types", &ZTextDemoTypes);
    registry.AddGroup(group);
}
