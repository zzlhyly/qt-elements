#include <QVBoxLayout>
#include <QWidget>
#include "widgets/text/ztext.h"

QWidget* ZTextDemoTruncated() {
    auto* w = new QWidget();
    auto* col = new QVBoxLayout(w);
    col->setSpacing(12);
    auto* normal = new ZText("This is a very long text that does not fit the available width");
    normal->setFixedWidth(120);
    col->addWidget(normal);
    auto* truncated = new ZText("This is a very long text that does not fit the available width");
    truncated->setFixedWidth(120);
    truncated->setTruncated(true);
    col->addWidget(truncated);
    col->addStretch();
    return w;
}
