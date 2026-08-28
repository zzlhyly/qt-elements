// demo_registry.h - Registry of every component demo rendered by the gallery.
//
// Each component owns one DemoGroup; the gallery renders one scrollable page
// per group. Registration is explicit and deterministic - no static
// initializers are involved, so page order is fully controlled by the caller.

#ifndef UICONTROLS_EXAMPLES_DEMO_DEMO_REGISTRY_H_
#define UICONTROLS_EXAMPLES_DEMO_DEMO_REGISTRY_H_

#include <QList>
#include <QString>
#include <functional>

class QWidget;

namespace demo {

// One demo: a section title plus a factory that builds its content widget.
// The factory is invoked lazily, once, when the gallery page is built.
struct DemoEntry {
    QString title;
    std::function<QWidget*()> factory;
};

// Every demo that belongs to a single component.
class DemoGroup {
public:
    explicit DemoGroup(QString name);

    [[nodiscard]] const QString& Name() const noexcept { return name_; }
    [[nodiscard]] const QList<DemoEntry>& Entries() const noexcept { return entries_; }

    void Add(QString title, std::function<QWidget*()> factory);

private:
    QString name_;
    QList<DemoEntry> entries_;
};

// Owns the ordered list of component groups rendered by the gallery.
class DemoRegistry {
public:
    void AddGroup(const DemoGroup& group);

    [[nodiscard]] const QList<DemoGroup>& Groups() const noexcept { return groups_; }

private:
    QList<DemoGroup> groups_;
};

}  // namespace demo

#endif  // UICONTROLS_EXAMPLES_DEMO_DEMO_REGISTRY_H_
