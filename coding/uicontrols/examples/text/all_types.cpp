#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QWidget>
#include <QLabel>
#include "widgets/text/ztext.h"

QWidget* ZTextDemoAllTypes() {
    auto* w = new QWidget();
    auto* col = new QVBoxLayout(w);
    col->setSpacing(12);

    struct TypeInfo {
        const char* name;
        ZText::TextType type;
    };
    const TypeInfo entries[] = {
        {"Default", ZText::kDefault},
        {"Primary", ZText::kPrimary},
        {"Success", ZText::kSuccess},
        {"Info",    ZText::kInfo},
        {"Warning", ZText::kWarning},
        {"Danger",  ZText::kDanger}
    };

    for (const auto& entry : entries) {
        auto* row = new QHBoxLayout();
        row->setSpacing(8);
        auto* label = new QLabel(QLatin1String(entry.name) + ":");
        row->addWidget(label);
        auto* text = new ZText("Sample text");
        text->setTextType(entry.type);
        row->addWidget(text);
        row->addStretch();
        col->addLayout(row);
    }

    col->addStretch();
    return w;
}
