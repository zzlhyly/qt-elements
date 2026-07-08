#include <QHBoxLayout>
#include <QWidget>
#include "widgets/button/zbutton.h"

QWidget* ZButtonDemoIcon() {
    auto* w = new QWidget();
    auto* row = new QHBoxLayout(w);
    row->setSpacing(12);
    {
        auto* btn = new ZButton(QString::fromUtf8("\u2B50 Edit"));
        btn->setButtonType(ZButton::kPrimary);
        row->addWidget(btn);
    }
    {
        auto* btn = new ZButton(QString::fromUtf8("\u2764 Like"));
        btn->setButtonType(ZButton::kSuccess);
        row->addWidget(btn);
    }
    {
        auto* btn = new ZButton(QString::fromUtf8("\u2605 Star"));
        btn->setButtonType(ZButton::kWarning);
        row->addWidget(btn);
    }
    row->addStretch();
    return w;
}
