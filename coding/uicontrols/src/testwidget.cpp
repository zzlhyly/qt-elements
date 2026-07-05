#include "testwidget.h"

#include <QFrame>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QScrollArea>
#include <QVBoxLayout>

#include "button/zbutton.h"

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
    ZButton::ButtonType types[] = { ZButton::kDefault, ZButton::kPrimary, ZButton::kSuccess, ZButton::kWarning, ZButton::kDanger, ZButton::kInfo };
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
    auto* lg = new ZButton("Large");   lg->setButtonType(ZButton::kPrimary); lg->setButtonSize(ZButton::kLarge);
    auto* df = new ZButton("Default"); df->setButtonType(ZButton::kPrimary); df->setButtonSize(ZButton::kMedium);
    auto* sm = new ZButton("Small");   sm->setButtonType(ZButton::kPrimary); sm->setButtonSize(ZButton::kSmall);
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
    ZButton::ButtonType plainTypes[] = { ZButton::kPrimary, ZButton::kSuccess, ZButton::kWarning, ZButton::kDanger, ZButton::kInfo };
    for (int i = 0; i < 5; ++i) {
        auto* btn = new ZButton(plainNames[i]);
        btn->setButtonType(plainTypes[i]);
        btn->setButtonVariant(ZButton::kPlain);
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
        btn->setButtonVariant(ZButton::kText);
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
    auto* d2 = new ZButton("Primary");  d2->setButtonType(ZButton::kPrimary); d2->setEnabled(false);
    auto* d3 = new ZButton("Success");  d3->setButtonType(ZButton::kSuccess); d3->setEnabled(false);
    auto* d4 = new ZButton("Plain");    d4->setButtonType(ZButton::kPrimary); d4->setButtonVariant(ZButton::kPlain); d4->setEnabled(false);
    auto* d5 = new ZButton("Text");     d5->setButtonType(ZButton::kDanger);  d5->setButtonVariant(ZButton::kText);  d5->setEnabled(false);
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
