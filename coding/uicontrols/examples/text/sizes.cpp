#include <QVBoxLayout>
#include <QWidget>
#include "widgets/text/ztext.h"

QWidget* ZTextDemoSizes() {
    auto* w = new QWidget();
    auto* col = new QVBoxLayout(w);
    col->setSpacing(12);
    const char* names[] = {"Large", "Medium", "Small"};
    const ZText::TextSize sizes[] = {ZText::kLarge, ZText::kMedium, ZText::kSmall};
    for (int i = 0; i < 3; ++i) {
        auto* text = new ZText(names[i]);
        text->setTextSize(sizes[i]);
        col->addWidget(text);
    }
    col->addStretch();
    return w;
}
