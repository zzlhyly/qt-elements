#include <QVBoxLayout>
#include <QWidget>
#include "widgets/divider/zdivider.h"

QWidget* ZDividerDemoBasic() {
    auto* w = new QWidget();
    auto* col = new QVBoxLayout(w);
    col->setSpacing(12);
    col->addWidget(new QWidget());
    col->addWidget(new ZDivider());
    col->addWidget(new QWidget());
    col->addStretch();
    return w;
}
