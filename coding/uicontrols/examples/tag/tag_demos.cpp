#include "tag/tag_demos.h"

#include "demo/demo_registry.h"

void RegisterTagDemos(demo::DemoRegistry& registry) {
    demo::DemoGroup group("Tag");
    group.Add("Basic", &ZTagDemoBasic);
    group.Add("Closable", &ZTagDemoClosable);
    group.Add("Round", &ZTagDemoRound);
    group.Add("Sizes", &ZTagDemoSizes);
    group.Add("Theme Dark", &ZTagDemoThemeDark);
    group.Add("Theme Light", &ZTagDemoThemeLight);
    group.Add("Theme Plain", &ZTagDemoThemePlain);
    registry.AddGroup(group);
}
