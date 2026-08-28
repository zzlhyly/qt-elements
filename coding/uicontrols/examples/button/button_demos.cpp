#include "button/button_demos.h"

#include "demo/demo_registry.h"

void RegisterButtonDemos(demo::DemoRegistry& registry) {
    demo::DemoGroup group("Button");
    group.Add("Basic", &ZButtonDemoBasic);
    group.Add("Button Group", &ZButtonDemoButtonGroup);
    group.Add("Circle", &ZButtonDemoCircle);
    group.Add("Color", &ZButtonDemoColor);
    group.Add("Dashed", &ZButtonDemoDashed);
    group.Add("Disabled", &ZButtonDemoDisabled);
    group.Add("Icon", &ZButtonDemoIcon);
    group.Add("Link", &ZButtonDemoLink);
    group.Add("Loading", &ZButtonDemoLoading);
    group.Add("Plain", &ZButtonDemoPlain);
    group.Add("Round", &ZButtonDemoRound);
    group.Add("Size", &ZButtonDemoSize);
    group.Add("Text", &ZButtonDemoText);
    registry.AddGroup(group);
}
