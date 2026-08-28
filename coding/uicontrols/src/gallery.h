// gallery.h - Demo gallery shell: component sidebar plus stacked demo pages.
//
// The gallery owns no demo content itself. Every page comes from the
// DemoRegistry, which each component fills in examples/<component>/.

#ifndef CODING_UICONTROLS_SRC_GALLERY_H_
#define CODING_UICONTROLS_SRC_GALLERY_H_

#include <QWidget>

class QListWidget;
class QStackedWidget;

namespace demo {
class DemoRegistry;
}  // namespace demo

class Gallery : public QWidget {
public:
    explicit Gallery(QWidget* parent = nullptr);

private:
    void BuildPages(const demo::DemoRegistry& registry);
    QListWidget* CreateSidebar(const demo::DemoRegistry& registry);

    QListWidget* sidebar_ = nullptr;
    QStackedWidget* stack_ = nullptr;
};

#endif  // CODING_UICONTROLS_SRC_GALLERY_H_
