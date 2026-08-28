#include "demo/demo_registry.h"

#include <utility>

namespace demo {

DemoGroup::DemoGroup(QString name) : name_(std::move(name)) {}

void DemoGroup::Add(QString title, std::function<QWidget*()> factory) {
    entries_.append(DemoEntry{std::move(title), std::move(factory)});
}

void DemoRegistry::AddGroup(const DemoGroup& group) { groups_.append(group); }

}  // namespace demo
