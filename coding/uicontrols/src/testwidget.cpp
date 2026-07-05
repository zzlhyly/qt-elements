#include "testwidget.h"
#include "button/zbutton.h"
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QScrollArea>
#include <QFrame>

static QLabel* sectionLabel(const QString& text)
{
    QLabel* l = new QLabel(text);
    QFont f = l->font();
    f.setPixelSize(14);
    f.setBold(true);
    l->setFont(f);
    return l;
}

TestWidget::TestWidget(QWidget* parent)
    : QWidget(parent)
{
    auto* scroll = new QScrollArea(this);
    scroll->setWidgetResizable(true);
    scroll->setFrameShape(QFrame::NoFrame);

    auto* content = new QWidget();
    auto* mainLayout = new QVBoxLayout(content);
    mainLayout->setSpacing(24);
    mainLayout->setContentsMargins(32, 24, 32, 24);

    // --- Row 1: All 6 types (solid) ---
    mainLayout->addWidget(sectionLabel("Solid Variant — All Types"));
    auto* row1 = new QHBoxLayout();
    row1->setSpacing(12);
    const char* typeNames[] = { "Default", "Primary", "Success", "Warning", "Danger", "Info" };
    ZButton::ButtonType types[] = { ZButton::BT_Default, ZButton::BT_Primary, ZButton::BT_Success, ZButton::BT_Warning, ZButton::BT_Danger, ZButton::BT_Info };
    for (int i = 0; i < 6; ++i) {
        auto* btn = new ZButton(typeNames[i]);
        btn->setButtonType(types[i]);
        row1->addWidget(btn);
    }
    row1->addStretch();
    mainLayout->addLayout(row1);

    // --- Row 2: All 3 sizes (primary) ---
    mainLayout->addWidget(sectionLabel("Sizes — Primary"));
    auto* row2 = new QHBoxLayout();
    row2->setSpacing(12);
    auto* lg = new ZButton("Large");   lg->setButtonType(ZButton::BT_Primary); lg->setButtonSize(ZButton::BS_Large);
    auto* df = new ZButton("Default"); df->setButtonType(ZButton::BT_Primary); df->setButtonSize(ZButton::BS_Default);
    auto* sm = new ZButton("Small");   sm->setButtonType(ZButton::BT_Primary); sm->setButtonSize(ZButton::BS_Small);
    row2->addWidget(lg);
    row2->addWidget(df);
    row2->addWidget(sm);
    row2->addStretch();
    mainLayout->addLayout(row2);

    // --- Row 3: Plain variant ---
    mainLayout->addWidget(sectionLabel("Plain Variant"));
    auto* row3 = new QHBoxLayout();
    row3->setSpacing(12);
    const char* plainNames[] = { "Primary", "Success", "Warning", "Danger", "Info" };
    ZButton::ButtonType plainTypes[] = { ZButton::BT_Primary, ZButton::BT_Success, ZButton::BT_Warning, ZButton::BT_Danger, ZButton::BT_Info };
    for (int i = 0; i < 5; ++i) {
        auto* btn = new ZButton(plainNames[i]);
        btn->setButtonType(plainTypes[i]);
        btn->setButtonVariant(ZButton::BV_Plain);
        row3->addWidget(btn);
    }
    row3->addStretch();
    mainLayout->addLayout(row3);

    // --- Row 4: Text variant ---
    mainLayout->addWidget(sectionLabel("Text Variant"));
    auto* row4 = new QHBoxLayout();
    row4->setSpacing(12);
    for (int i = 0; i < 6; ++i) {
        auto* btn = new ZButton(typeNames[i]);
        btn->setButtonType(types[i]);
        btn->setButtonVariant(ZButton::BV_Text);
        row4->addWidget(btn);
    }
    row4->addStretch();
    mainLayout->addLayout(row4);

    // --- Row 5: Round buttons ---
    mainLayout->addWidget(sectionLabel("Round Buttons"));
    auto* row5 = new QHBoxLayout();
    row5->setSpacing(12);
    for (int i = 0; i < 6; ++i) {
        auto* btn = new ZButton(typeNames[i]);
        btn->setButtonType(types[i]);
        btn->setRound(true);
        row5->addWidget(btn);
    }
    row5->addStretch();
    mainLayout->addLayout(row5);

    // --- Row 6: Disabled ---
    mainLayout->addWidget(sectionLabel("Disabled"));
    auto* row6 = new QHBoxLayout();
    row6->setSpacing(12);
    auto* d1 = new ZButton("Default");  d1->setEnabled(false);
    auto* d2 = new ZButton("Primary");  d2->setButtonType(ZButton::BT_Primary); d2->setEnabled(false);
    auto* d3 = new ZButton("Success");  d3->setButtonType(ZButton::BT_Success); d3->setEnabled(false);
    auto* d4 = new ZButton("Plain");    d4->setButtonType(ZButton::BT_Primary); d4->setButtonVariant(ZButton::BV_Plain); d4->setEnabled(false);
    auto* d5 = new ZButton("Text");     d5->setButtonType(ZButton::BT_Danger);  d5->setButtonVariant(ZButton::BV_Text);  d5->setEnabled(false);
    row6->addWidget(d1);
    row6->addWidget(d2);
    row6->addWidget(d3);
    row6->addWidget(d4);
    row6->addWidget(d5);
    row6->addStretch();
    mainLayout->addLayout(row6);

    mainLayout->addStretch();

    scroll->setWidget(content);

    auto* topLayout = new QVBoxLayout(this);
    topLayout->setContentsMargins(0, 0, 0, 0);
    topLayout->addWidget(scroll);
}
