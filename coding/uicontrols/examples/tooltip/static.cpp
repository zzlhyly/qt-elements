#include <QHBoxLayout>
#include <QPushButton>
#include <QWidget>
#include "widgets/tooltip/ztooltip.h"

QWidget* ZTooltipDemoStatic() {
    auto* w = new QWidget();
    auto* row = new QHBoxLayout(w);
    row->setSpacing(12);

    auto* btn = new QPushButton("Show tooltip");
    QObject::connect(btn, &QPushButton::clicked, [btn]() {
        ZTooltip::showText(btn, "Static tooltip - auto-hides after 3s", ZTooltip::kDark, 3000);
    });
    row->addWidget(btn);

    return w;
}
