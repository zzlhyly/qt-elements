#include "gallery.h"

#include <QFont>
#include <QFrame>
#include <QHBoxLayout>
#include <QListWidget>
#include <QStackedWidget>

#include "demo/demo_page.h"
#include "demo/demo_registry.h"
#include "theme/theme.h"

#include "alert/alert_demos.h"
#include "badge/badge_demos.h"
#include "button/button_demos.h"
#include "checkbox/checkbox_demos.h"
#include "divider/divider_demos.h"
#include "input/input_demos.h"
#include "link/link_demos.h"
#include "progress/progress_demos.h"
#include "radio/radio_demos.h"
#include "slider/slider_demos.h"
#include "switch/switch_demos.h"
#include "tag/tag_demos.h"
#include "text/text_demos.h"
#include "tooltip/tooltip_demos.h"

namespace {

constexpr int kSidebarWidth = 160;

// Sidebar order follows the component roadmap in COMPONENTS.md.
void RegisterAllDemos(demo::DemoRegistry& registry) {
    RegisterButtonDemos(registry);
    RegisterTagDemos(registry);
    RegisterBadgeDemos(registry);
    RegisterDividerDemos(registry);
    RegisterLinkDemos(registry);
    RegisterTextDemos(registry);
    RegisterInputDemos(registry);
    RegisterRadioDemos(registry);
    RegisterCheckboxDemos(registry);
    RegisterSwitchDemos(registry);
    RegisterSliderDemos(registry);
    RegisterProgressDemos(registry);
    RegisterAlertDemos(registry);
    RegisterTooltipDemos(registry);
}

}  // namespace

Gallery::Gallery(QWidget* parent) : QWidget(parent) {
    setMinimumSize(900, 600);
    setAutoFillBackground(true);
    QPalette window_palette = palette();
    window_palette.setColor(QPalette::Window, theme::fillLight());
    setPalette(window_palette);

    demo::DemoRegistry registry;
    RegisterAllDemos(registry);

    stack_ = new QStackedWidget();
    BuildPages(registry);
    sidebar_ = CreateSidebar(registry);

    auto* layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->addWidget(sidebar_);
    layout->addWidget(stack_);

    connect(sidebar_, &QListWidget::currentRowChanged, stack_, &QStackedWidget::setCurrentIndex);
    sidebar_->setCurrentRow(0);
}

void Gallery::BuildPages(const demo::DemoRegistry& registry) {
    for (const demo::DemoGroup& group : registry.Groups())
        stack_->addWidget(demo::CreateDemoPage(group));
}

QListWidget* Gallery::CreateSidebar(const demo::DemoRegistry& registry) {
    auto* list = new QListWidget();
    list->setFixedWidth(kSidebarWidth);
    list->setFrameShape(QFrame::NoFrame);
    list->setSpacing(0);

    QFont font = list->font();
    font.setPixelSize(theme::fontSizeBase());
    list->setFont(font);

    QPalette palette = list->palette();
    palette.setColor(QPalette::Base, theme::fillLight());
    palette.setColor(QPalette::Highlight, theme::primaryLight9());
    palette.setColor(QPalette::HighlightedText, theme::colorPrimary());
    list->setPalette(palette);

    for (const demo::DemoGroup& group : registry.Groups())
        list->addItem(group.Name());
    return list;
}
