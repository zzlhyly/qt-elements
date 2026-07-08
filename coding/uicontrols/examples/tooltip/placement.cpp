#include <QHBoxLayout>
#include <QPushButton>
#include <QWidget>
#include "widgets/tooltip/ztooltip.h"

QWidget* ZTooltipDemoPlacement() {
    auto* w = new QWidget();
    auto* row = new QHBoxLayout(w);
    row->setSpacing(12);

    auto* btnTop = new QPushButton("Top");
    ZTooltip::install(btnTop, "Tooltip on top", ZPopup::kTop);
    row->addWidget(btnTop);

    auto* btnBottom = new QPushButton("Bottom");
    ZTooltip::install(btnBottom, "Tooltip on bottom", ZPopup::kBottom);
    row->addWidget(btnBottom);

    auto* btnLeft = new QPushButton("Left");
    ZTooltip::install(btnLeft, "Tooltip on left", ZPopup::kLeft);
    row->addWidget(btnLeft);

    auto* btnRight = new QPushButton("Right");
    ZTooltip::install(btnRight, "Tooltip on right", ZPopup::kRight);
    row->addWidget(btnRight);

    return w;
}
