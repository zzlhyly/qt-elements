#include "demo/demo_page.h"

#include <QFont>
#include <QFrame>
#include <QLabel>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QWidget>

#include "demo/demo_registry.h"
#include "theme/theme.h"

namespace demo {
namespace {

constexpr int kPageMarginH = 32;
constexpr int kPageMarginV = 24;
constexpr int kSectionSpacing = 24;

QLabel* CreateSectionLabel(const QString& text) {
    auto* label = new QLabel(text);
    QFont font = label->font();
    font.setPixelSize(theme::fontSizeBase());
    font.setBold(true);
    label->setFont(font);
    return label;
}

}  // namespace

QWidget* CreateDemoPage(const DemoGroup& group) {
    auto* scroll = new QScrollArea();
    scroll->setWidgetResizable(true);
    scroll->setFrameShape(QFrame::NoFrame);
    scroll->viewport()->setAutoFillBackground(false);

    auto* content = new QWidget();
    auto* layout = new QVBoxLayout(content);
    layout->setSpacing(kSectionSpacing);
    layout->setContentsMargins(kPageMarginH, kPageMarginV, kPageMarginH, kPageMarginV);

    for (const DemoEntry& entry : group.Entries()) {
        layout->addWidget(CreateSectionLabel(entry.title));
        layout->addWidget(entry.factory());
    }
    layout->addStretch();

    scroll->setWidget(content);
    return scroll;
}

}  // namespace demo
