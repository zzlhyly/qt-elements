#include "testwidget.h"

#include <QFrame>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QScrollArea>
#include <QVBoxLayout>

#include "button/zbutton.h"
#include "tag/ztag.h"

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

    // --- ZTag Section ---
    mainLayout->addWidget(sectionLabel("Tags — All Types (Light)"));

    // Row 7: Tag types
    auto* tagRow1 = new QHBoxLayout();
    tagRow1->setSpacing(12);
    const char* tagTypeNames[] = { "Default", "Success", "Info", "Warning", "Danger" };
    ZTag::TagType tagTypes[] = { ZTag::kDefault, ZTag::kSuccess, ZTag::kInfo, ZTag::kWarning, ZTag::kDanger };
    for (int i = 0; i < 5; ++i) {
        auto* tag = new ZTag(tagTypeNames[i]);
        tag->setTagType(tagTypes[i]);
        tagRow1->addWidget(tag);
    }
    tagRow1->addStretch();
    mainLayout->addLayout(tagRow1);

    // Row 8: Tag effects
    mainLayout->addWidget(sectionLabel("Tags — Effects (Primary)"));
    auto* tagRow2 = new QHBoxLayout();
    tagRow2->setSpacing(12);
    auto* lightTag = new ZTag("Light");    lightTag->setTagType(ZTag::kSuccess);
    auto* darkTag = new ZTag("Dark");       darkTag->setTagType(ZTag::kSuccess); darkTag->setEffect(ZTag::kDark);
    auto* plainTag = new ZTag("Plain");     plainTag->setTagType(ZTag::kSuccess); plainTag->setEffect(ZTag::kPlain);
    tagRow2->addWidget(lightTag);
    tagRow2->addWidget(darkTag);
    tagRow2->addWidget(plainTag);
    tagRow2->addStretch();
    mainLayout->addLayout(tagRow2);

    // Row 9: Tag sizes + round
    mainLayout->addWidget(sectionLabel("Tags — Sizes & Round"));
    auto* tagRow3 = new QHBoxLayout();
    tagRow3->setSpacing(12);
    auto* tagLg = new ZTag("Large");    tagLg->setTagType(ZTag::kWarning); tagLg->setTagSize(ZTag::kLarge);
    auto* tagMd = new ZTag("Medium");   tagMd->setTagType(ZTag::kWarning); tagMd->setTagSize(ZTag::kMedium);
    auto* tagSm = new ZTag("Small");    tagSm->setTagType(ZTag::kWarning); tagSm->setTagSize(ZTag::kSmall);
    auto* tagRd = new ZTag("Round");    tagRd->setTagType(ZTag::kDanger);   tagRd->setRound(true);
    auto* tagHit = new ZTag("Hit");     tagHit->setTagType(ZTag::kDefault); tagHit->setHit(true);
    tagRow3->addWidget(tagLg);
    tagRow3->addWidget(tagMd);
    tagRow3->addWidget(tagSm);
    tagRow3->addWidget(tagRd);
    tagRow3->addWidget(tagHit);
    tagRow3->addStretch();
    mainLayout->addLayout(tagRow3);

    // Row 10: Closable tags
    mainLayout->addWidget(sectionLabel("Tags — Closable"));
    auto* tagRow4 = new QHBoxLayout();
    tagRow4->setSpacing(12);
    for (int i = 0; i < 5; ++i) {
        auto* tag = new ZTag(tagTypeNames[i]);
        tag->setTagType(tagTypes[i]);
        tag->setClosable(true);
        QObject::connect(tag, &ZTag::closed, tag, &QWidget::hide);
        tagRow4->addWidget(tag);
    }
    tagRow4->addStretch();
    mainLayout->addLayout(tagRow4);

    mainLayout->addStretch();

    scroll->setWidget(content);

    auto* topLayout = new QVBoxLayout(this);
    topLayout->setContentsMargins(0, 0, 0, 0);
    topLayout->addWidget(scroll);
}
