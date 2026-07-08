#include <QHBoxLayout>
#include <QWidget>
#include "widgets/text/ztext.h"

QWidget* ZTextDemoTypes() {
    auto* w = new QWidget();
    auto* row = new QHBoxLayout(w);
    row->setSpacing(12);
    const char* names[] = {"Default", "Primary", "Success", "Info", "Warning", "Danger"};
    const ZText::TextType types[] = {ZText::kDefault, ZText::kPrimary, ZText::kSuccess,
                                     ZText::kInfo, ZText::kWarning, ZText::kDanger};
    for (int i = 0; i < 6; ++i) {
        auto* text = new ZText(names[i]);
        text->setTextType(types[i]);
        row->addWidget(text);
    }
    row->addStretch();
    return w;
}
