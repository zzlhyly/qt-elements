#include "input/input_demos.h"

#include "demo/demo_registry.h"

void RegisterInputDemos(demo::DemoRegistry& registry) {
    demo::DemoGroup group("Input");
    group.Add("Basic", &ZInputDemoBasic);
    group.Add("Autosize", &ZInputDemoAutosize);
    group.Add("Clearable", &ZInputDemoClearable);
    group.Add("Disabled", &ZInputDemoDisabled);
    group.Add("Password", &ZInputDemoPassword);
    group.Add("Prepend / Append", &ZInputDemoPrependAppend);
    group.Add("Size", &ZInputDemoSize);
    group.Add("Textarea", &ZInputDemoTextarea);
    group.Add("With Icon", &ZInputDemoWithIcon);
    group.Add("Word Limit", &ZInputDemoWordLimit);
    registry.AddGroup(group);
}
