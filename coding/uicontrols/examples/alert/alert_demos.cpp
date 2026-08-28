#include "alert/alert_demos.h"

#include "demo/demo_registry.h"

void RegisterAlertDemos(demo::DemoRegistry& registry) {
    demo::DemoGroup group("Alert");
    group.Add("Basic", &ZAlertDemoBasic);
    group.Add("Center", &ZAlertDemoCenter);
    group.Add("Closable", &ZAlertDemoClosable);
    group.Add("Description", &ZAlertDemoDescription);
    group.Add("show-icon", &ZAlertDemoShowIcon);
    group.Add("Theme", &ZAlertDemoTheme);
    registry.AddGroup(group);
}
