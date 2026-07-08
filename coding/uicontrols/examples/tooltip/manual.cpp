#include <QHBoxLayout>
#include <QPushButton>
#include <QWidget>
#include "widgets/tooltip/ztooltip.h"

QWidget* ZTooltipDemoManual() {
    auto* w = new QWidget();
    auto* row = new QHBoxLayout(w);
    row->setSpacing(12);

    auto* btnShow = new QPushButton("Show manual tooltip");
    auto* tt = new ZTooltip(btnShow);
    tt->setTarget(btnShow);
    tt->setText("Manually triggered tooltip");
    tt->setTrigger(ZTooltip::kManual);

    QObject::connect(btnShow, &QPushButton::clicked, [tt]() { tt->show(); });
    row->addWidget(btnShow);

    return w;
}
