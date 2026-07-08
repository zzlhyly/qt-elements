#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include "widgets/tooltip/ztooltip.h"

QWidget* ZTooltipDemoDelay() {
    auto* w = new QWidget();
    auto* row = new QHBoxLayout(w);
    row->setSpacing(12);

    auto* btn = new QPushButton("Delay 800ms");
    auto* tt = new ZTooltip(btn);
    tt->setTarget(btn);
    tt->setText("Tooltip with 800ms delay");
    tt->setShowDelay(800);
    row->addWidget(btn);

    return w;
}
