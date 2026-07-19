#include <QHBoxLayout>
#include <QWidget>
#include "widgets/divider/zdivider.h"

QWidget* ZDividerDemoVertical() {
    auto* w = new QWidget();
    auto* row = new QHBoxLayout(w);
    row->setSpacing(12);
    auto* left = new QWidget();
    left->setMinimumSize(100, 100);
    row->addWidget(left);
    auto* divider = new ZDivider();
    divider->setDirection(ZDivider::kVertical);
    row->addWidget(divider);
    auto* right = new QWidget();
    right->setMinimumSize(100, 100);
    row->addWidget(right);
    row->addStretch();
    return w;
}
