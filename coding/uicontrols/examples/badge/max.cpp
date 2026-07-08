#include <QHBoxLayout>
#include <QWidget>
#include "widgets/badge/zbadge.h"

QWidget* ZBadgeDemoMax() {
    auto* w = new QWidget();
    auto* row = new QHBoxLayout(w);
    row->setSpacing(16);
    auto* badge = new ZBadge(150, w);
    badge->setMax(5);
    row->addWidget(badge);
    row->addStretch();
    return w;
}
