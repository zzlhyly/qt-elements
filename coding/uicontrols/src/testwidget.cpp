#include "testwidget.h"

#include <QFrame>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QListWidget>
#include <QScrollArea>
#include <QStackedWidget>
#include <QVBoxLayout>

#include "button/zbutton.h"
#include "tag/ztag.h"
#include "badge/zbadge.h"
#include "divider/zdivider.h"
#include "link/zlink.h"
#include "text/ztext.h"
#include "input/zinput.h"
#include "radio/zradio.h"
#include "checkbox/zcheckbox.h"

static QLabel* sectionLabel(const QString& text)
{
    QLabel* l = new QLabel(text);
    QFont f = l->font();
    f.setPixelSize(14);
    f.setBold(true);
    l->setFont(f);
    return l;
}

static QWidget* createButtonPage()
{
    auto* scroll = new QScrollArea();
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

    // --- Row 5: Link variant ---
    mainLayout->addWidget(sectionLabel("Link Variant"));
    auto* row5 = new QHBoxLayout();
    row5->setSpacing(12);
    for (int i = 0; i < 6; ++i) {
        auto* btn = new ZButton(typeNames[i]);
        btn->setButtonType(types[i]);
        btn->setButtonVariant(ZButton::kLink);
        row5->addWidget(btn);
    }
    row5->addStretch();
    mainLayout->addLayout(row5);

    // --- Row 6: Round buttons ---
    mainLayout->addWidget(sectionLabel("Round Buttons"));
    auto* row6 = new QHBoxLayout();
    row6->setSpacing(12);
    for (int i = 0; i < 6; ++i) {
        auto* btn = new ZButton(typeNames[i]);
        btn->setButtonType(types[i]);
        btn->setRound(true);
        row6->addWidget(btn);
    }
    row6->addStretch();
    mainLayout->addLayout(row6);

    // --- Row 7: Dashed variant ---
    mainLayout->addWidget(sectionLabel("Dashed Variant"));
    auto* row7 = new QHBoxLayout();
    row7->setSpacing(12);
    for (int i = 0; i < 5; ++i) {
        auto* btn = new ZButton(plainNames[i]);
        btn->setButtonType(plainTypes[i]);
        btn->setButtonVariant(ZButton::kDashed);
        row7->addWidget(btn);
    }
    row7->addStretch();
    mainLayout->addLayout(row7);

    // --- Row 8: Disabled ---
    mainLayout->addWidget(sectionLabel("Disabled"));
    auto* row8 = new QHBoxLayout();
    row8->setSpacing(12);
    auto* d1 = new ZButton("Default");  d1->setEnabled(false);
    auto* d2 = new ZButton("Primary");  d2->setButtonType(ZButton::kPrimary); d2->setEnabled(false);
    auto* d3 = new ZButton("Success");  d3->setButtonType(ZButton::kSuccess); d3->setEnabled(false);
    auto* d4 = new ZButton("Plain");    d4->setButtonType(ZButton::kPrimary); d4->setButtonVariant(ZButton::kPlain); d4->setEnabled(false);
    auto* d5 = new ZButton("Text");     d5->setButtonType(ZButton::kDanger);  d5->setButtonVariant(ZButton::kText);  d5->setEnabled(false);
    row8->addWidget(d1);
    row8->addWidget(d2);
    row8->addWidget(d3);
    row8->addWidget(d4);
    row8->addWidget(d5);
    row8->addStretch();
    mainLayout->addLayout(row8);

    // --- Row 9: Loading buttons ---
    mainLayout->addWidget(sectionLabel("Loading"));
    auto* row9 = new QHBoxLayout();
    row9->setSpacing(12);
    auto* ld1 = new ZButton("Primary"); ld1->setButtonType(ZButton::kPrimary); ld1->setLoading(true);
    auto* ld2 = new ZButton("Success"); ld2->setButtonType(ZButton::kSuccess); ld2->setLoading(true);
    auto* ld3 = new ZButton("Plain");   ld3->setButtonType(ZButton::kPrimary); ld3->setButtonVariant(ZButton::kPlain); ld3->setLoading(true);
    auto* ld4 = new ZButton("Text");    ld4->setButtonType(ZButton::kDanger);  ld4->setButtonVariant(ZButton::kText);  ld4->setLoading(true);
    row9->addWidget(ld1);
    row9->addWidget(ld2);
    row9->addWidget(ld3);
    row9->addWidget(ld4);
    row9->addStretch();
    mainLayout->addLayout(row9);

    mainLayout->addStretch();

    scroll->setWidget(content);
    return scroll;
}

static QWidget* createTagPage()
{
    auto* scroll = new QScrollArea();
    scroll->setWidgetResizable(true);
    scroll->setFrameShape(QFrame::NoFrame);

    auto* content = new QWidget();
    auto* mainLayout = new QVBoxLayout(content);
    mainLayout->setSpacing(24);
    mainLayout->setContentsMargins(32, 24, 32, 24);

    // --- Tag types ---
    mainLayout->addWidget(sectionLabel("Tags — All Types (Light)"));
    auto* tagRow1 = new QHBoxLayout();
    tagRow1->setSpacing(12);
    const char* tagTypeNames[] = { "Primary", "Success", "Info", "Warning", "Danger" };
    ZTag::TagType tagTypes[] = { ZTag::kPrimary, ZTag::kSuccess, ZTag::kInfo, ZTag::kWarning, ZTag::kDanger };
    for (int i = 0; i < 5; ++i) {
        auto* tag = new ZTag(tagTypeNames[i]);
        tag->setTagType(tagTypes[i]);
        tagRow1->addWidget(tag);
    }
    tagRow1->addStretch();
    mainLayout->addLayout(tagRow1);

    // --- Tag effects ---
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

    // --- Tag sizes + round ---
    mainLayout->addWidget(sectionLabel("Tags — Sizes & Round"));
    auto* tagRow3 = new QHBoxLayout();
    tagRow3->setSpacing(12);
    auto* tagLg = new ZTag("Large");    tagLg->setTagType(ZTag::kWarning); tagLg->setTagSize(ZTag::kLarge);
    auto* tagMd = new ZTag("Medium");   tagMd->setTagType(ZTag::kWarning); tagMd->setTagSize(ZTag::kMedium);
    auto* tagSm = new ZTag("Small");    tagSm->setTagType(ZTag::kWarning); tagSm->setTagSize(ZTag::kSmall);
    auto* tagRd = new ZTag("Round");    tagRd->setTagType(ZTag::kDanger);   tagRd->setRound(true);
    auto* tagHit = new ZTag("Hit");     tagHit->setTagType(ZTag::kPrimary); tagHit->setHit(true);
    tagRow3->addWidget(tagLg);
    tagRow3->addWidget(tagMd);
    tagRow3->addWidget(tagSm);
    tagRow3->addWidget(tagRd);
    tagRow3->addWidget(tagHit);
    tagRow3->addStretch();
    mainLayout->addLayout(tagRow3);

    // --- Closable tags ---
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
    return scroll;
}

static QWidget* createBadgePage()
{
    auto* scroll = new QScrollArea();
    scroll->setWidgetResizable(true);
    scroll->setFrameShape(QFrame::NoFrame);

    auto* content = new QWidget();
    auto* mainLayout = new QVBoxLayout(content);
    mainLayout->setSpacing(24);
    mainLayout->setContentsMargins(32, 24, 32, 24);

    // Row 1: Types
    mainLayout->addWidget(sectionLabel("Badge — All Types (value=10)"));
    auto* row1 = new QHBoxLayout();
    row1->setSpacing(16);
    const char* badgeTypeNames[] = { "Primary", "Success", "Info", "Warning", "Danger" };
    ZBadge::BadgeType badgeTypes[] = { ZBadge::kPrimary, ZBadge::kSuccess, ZBadge::kInfo, ZBadge::kWarning, ZBadge::kDanger };
    for (int i = 0; i < 5; ++i) {
        auto* badge = new ZBadge(10);
        badge->setBadgeType(badgeTypes[i]);
        row1->addWidget(badge);
    }
    row1->addStretch();
    mainLayout->addLayout(row1);

    // Row 2: Dot mode
    mainLayout->addWidget(sectionLabel("Badge — Dot Mode"));
    auto* row2 = new QHBoxLayout();
    row2->setSpacing(16);
    for (int i = 0; i < 5; ++i) {
        auto* badge = new ZBadge();
        badge->setBadgeType(badgeTypes[i]);
        badge->setDot(true);
        row2->addWidget(badge);
    }
    row2->addStretch();
    mainLayout->addLayout(row2);

    // Row 3: Max value
    mainLayout->addWidget(sectionLabel("Badge — Max Value (value=150, max=99 → \"99+\")"));
    auto* row3 = new QHBoxLayout();
    row3->setSpacing(16);
    auto* badgeMax1 = new ZBadge(150);
    badgeMax1->setBadgeType(ZBadge::kDanger);
    row3->addWidget(badgeMax1);
    auto* badgeMax2 = new ZBadge(50);
    badgeMax2->setBadgeType(ZBadge::kDanger);
    row3->addWidget(badgeMax2);
    row3->addStretch();
    mainLayout->addLayout(row3);

    // Row 4: Hidden toggle
    mainLayout->addWidget(sectionLabel("Badge — Hidden"));
    auto* row4 = new QHBoxLayout();
    row4->setSpacing(16);
    auto* badgeHidden = new ZBadge(5);
    badgeHidden->setBadgeType(ZBadge::kDanger);
    badgeHidden->setBadgeHidden(true);
    row4->addWidget(badgeHidden);
    row4->addStretch();
    mainLayout->addLayout(row4);

    mainLayout->addStretch();

    scroll->setWidget(content);
    return scroll;
}

static QWidget* createDividerPage()
{
    auto* scroll = new QScrollArea();
    scroll->setWidgetResizable(true);
    scroll->setFrameShape(QFrame::NoFrame);

    auto* content = new QWidget();
    auto* mainLayout = new QVBoxLayout(content);
    mainLayout->setSpacing(24);
    mainLayout->setContentsMargins(32, 24, 32, 24);

    // Horizontal divider, no text
    mainLayout->addWidget(sectionLabel("Divider — Horizontal, No Text"));
    mainLayout->addWidget(new ZDivider());

    // Horizontal divider with text, left
    mainLayout->addWidget(sectionLabel("Divider — Left"));
    auto* dLeft = new ZDivider("Left");
    dLeft->setContentPosition(ZDivider::kLeft);
    mainLayout->addWidget(dLeft);

    // Horizontal divider with text, center
    mainLayout->addWidget(sectionLabel("Divider — Center"));
    mainLayout->addWidget(new ZDivider("Center"));

    // Horizontal divider with text, right
    mainLayout->addWidget(sectionLabel("Divider — Right"));
    auto* dRight = new ZDivider("Right");
    dRight->setContentPosition(ZDivider::kRight);
    mainLayout->addWidget(dRight);

    // Dashed style
    mainLayout->addWidget(sectionLabel("Divider — Dashed"));
    auto* dDashed = new ZDivider("Dashed");
    dDashed->setBorderStyle(ZDivider::kDashed);
    mainLayout->addWidget(dDashed);

    // Dotted style
    mainLayout->addWidget(sectionLabel("Divider — Dotted"));
    auto* dDotted = new ZDivider("Dotted");
    dDotted->setBorderStyle(ZDivider::kDotted);
    mainLayout->addWidget(dDotted);

    // Vertical divider
    mainLayout->addWidget(sectionLabel("Divider — Vertical"));
    auto* vertLayout = new QHBoxLayout();
    auto* vd = new ZDivider();
    vd->setDirection(ZDivider::kVertical);
    vd->setFixedHeight(100);
    vertLayout->addWidget(vd);
    vertLayout->addStretch();
    mainLayout->addLayout(vertLayout);

    mainLayout->addStretch();

    scroll->setWidget(content);
    return scroll;
}

static QWidget* createLinkPage()
{
    auto* scroll = new QScrollArea();
    scroll->setWidgetResizable(true);
    scroll->setFrameShape(QFrame::NoFrame);

    auto* content = new QWidget();
    auto* mainLayout = new QVBoxLayout(content);
    mainLayout->setSpacing(24);
    mainLayout->setContentsMargins(32, 24, 32, 24);

    // Row 1: All 6 types
    mainLayout->addWidget(sectionLabel("Link — All Types"));
    auto* row1 = new QHBoxLayout();
    row1->setSpacing(16);
    const char* linkTypeNames[] = { "Default", "Primary", "Success", "Warning", "Danger", "Info" };
    ZLink::LinkType linkTypes[] = { ZLink::kDefault, ZLink::kPrimary, ZLink::kSuccess, ZLink::kWarning, ZLink::kDanger, ZLink::kInfo };
    for (int i = 0; i < 6; ++i) {
        auto* link = new ZLink(linkTypeNames[i]);
        link->setLinkType(linkTypes[i]);
        row1->addWidget(link);
    }
    row1->addStretch();
    mainLayout->addLayout(row1);

    // Row 2: Underline always on
    mainLayout->addWidget(sectionLabel("Link — Underline Always On"));
    auto* row2 = new QHBoxLayout();
    row2->setSpacing(16);
    for (int i = 0; i < 6; ++i) {
        auto* link = new ZLink(linkTypeNames[i]);
        link->setLinkType(linkTypes[i]);
        link->setUnderline(true);
        row2->addWidget(link);
    }
    row2->addStretch();
    mainLayout->addLayout(row2);

    // Row 3: Disabled links
    mainLayout->addWidget(sectionLabel("Link — Disabled"));
    auto* row3 = new QHBoxLayout();
    row3->setSpacing(16);
    for (int i = 0; i < 6; ++i) {
        auto* link = new ZLink(linkTypeNames[i]);
        link->setLinkType(linkTypes[i]);
        link->setEnabled(false);
        row3->addWidget(link);
    }
    row3->addStretch();
    mainLayout->addLayout(row3);

    mainLayout->addStretch();

    scroll->setWidget(content);
    return scroll;
}

static QWidget* createTextPage()
{
    auto* scroll = new QScrollArea();
    scroll->setWidgetResizable(true);
    scroll->setFrameShape(QFrame::NoFrame);

    auto* content = new QWidget();
    auto* layout = new QVBoxLayout(content);
    layout->setSpacing(24);
    layout->setContentsMargins(32, 24, 32, 24);

    // Types
    layout->addWidget(sectionLabel("Text — All Types"));
    auto* row1 = new QHBoxLayout();
    row1->setSpacing(16);
    ZText::TextType ztTypes[] = { ZText::kDefault, ZText::kPrimary, ZText::kSuccess,
                                  ZText::kInfo, ZText::kWarning, ZText::kDanger };
    const char* ztNames[] = { "Default", "Primary", "Success", "Info", "Warning", "Danger" };
    for (int i = 0; i < 6; ++i) {
        auto* t = new ZText(ztNames[i]);
        t->setTextType(ztTypes[i]);
        row1->addWidget(t);
    }
    row1->addStretch();
    layout->addLayout(row1);

    // Sizes
    layout->addWidget(sectionLabel("Text — Sizes"));
    auto* row2 = new QHBoxLayout();
    row2->setSpacing(16);
    auto* tLg = new ZText("Large");   tLg->setTextSize(ZText::kLarge);   tLg->setTextType(ZText::kPrimary);
    auto* tDf = new ZText("Medium");  tDf->setTextSize(ZText::kMedium);  tDf->setTextType(ZText::kPrimary);
    auto* tSm = new ZText("Small");   tSm->setTextSize(ZText::kSmall);   tSm->setTextType(ZText::kPrimary);
    row2->addWidget(tLg);
    row2->addWidget(tDf);
    row2->addWidget(tSm);
    row2->addStretch();
    layout->addLayout(row2);

    // Truncated
    layout->addWidget(sectionLabel("Text — Truncated (200px)"));
    auto* tr = new ZText("This is a very long text that should be truncated with ellipsis");
    tr->setTruncated(true);
    tr->setFixedWidth(200);
    tr->setTextType(ZText::kPrimary);
    layout->addWidget(tr);

    layout->addStretch();
    scroll->setWidget(content);
    return scroll;
}

static QWidget* createInputPage()
{
    auto* scroll = new QScrollArea();
    scroll->setWidgetResizable(true);
    scroll->setFrameShape(QFrame::NoFrame);

    auto* content = new QWidget();
    auto* layout = new QVBoxLayout(content);
    layout->setSpacing(24);
    layout->setContentsMargins(32, 24, 32, 24);

    // Basic
    layout->addWidget(sectionLabel("Input — Basic"));
    auto* basic = new ZInput();
    basic->setPlaceholderText("Basic input");
    layout->addWidget(basic);

    // Sizes
    layout->addWidget(sectionLabel("Input — Sizes"));
    auto* szRow = new QHBoxLayout();
    szRow->setSpacing(12);
    auto* iLg = new ZInput(); iLg->setInputSize(ZInput::kLarge); iLg->setPlaceholderText("Large");
    auto* iDf = new ZInput(); iDf->setPlaceholderText("Default");
    auto* iSm = new ZInput(); iSm->setInputSize(ZInput::kSmall); iSm->setPlaceholderText("Small");
    szRow->addWidget(iLg);
    szRow->addWidget(iDf);
    szRow->addWidget(iSm);
    szRow->addStretch();
    layout->addLayout(szRow);

    // Clearable
    layout->addWidget(sectionLabel("Input — Clearable"));
    auto* clearInput = new ZInput();
    clearInput->setPlaceholderText("Type something and clear...");
    clearInput->setClearable(true);
    layout->addWidget(clearInput);

    // Password
    layout->addWidget(sectionLabel("Input — Password"));
    auto* pwdInput = new ZInput();
    pwdInput->setPlaceholderText("Enter password");
    pwdInput->setPasswordMode(true);
    layout->addWidget(pwdInput);

    // Disabled
    layout->addWidget(sectionLabel("Input — Disabled"));
    auto* disabledInput = new ZInput();
    disabledInput->setPlaceholderText("Disabled");
    disabledInput->setText("Can't edit");
    disabledInput->setEnabled(false);
    layout->addWidget(disabledInput);

    layout->addStretch();
    scroll->setWidget(content);
    return scroll;
}

static QWidget* createRadioPage()
{
    auto* scroll = new QScrollArea();
    scroll->setWidgetResizable(true);
    scroll->setFrameShape(QFrame::NoFrame);

    auto* content = new QWidget();
    auto* layout = new QVBoxLayout(content);
    layout->setSpacing(24);
    layout->setContentsMargins(32, 24, 32, 24);

    // Radio group
    layout->addWidget(sectionLabel("Radio — Group"));
    auto* group1 = new QHBoxLayout();
    group1->setSpacing(16);
    auto* r1 = new ZRadio("Option A");
    auto* r2 = new ZRadio("Option B");
    auto* r3 = new ZRadio("Option C");
    r1->setChecked(true);
    group1->addWidget(r1);
    group1->addWidget(r2);
    group1->addWidget(r3);
    group1->addStretch();
    layout->addLayout(group1);

    // Disabled
    layout->addWidget(sectionLabel("Radio — Disabled"));
    auto* group2 = new QHBoxLayout();
    group2->setSpacing(16);
    auto* rd1 = new ZRadio("Disabled unchecked"); rd1->setEnabled(false);
    auto* rd2 = new ZRadio("Disabled checked");   rd2->setChecked(true); rd2->setEnabled(false);
    group2->addWidget(rd1);
    group2->addWidget(rd2);
    group2->addStretch();
    layout->addLayout(group2);

    layout->addStretch();
    scroll->setWidget(content);
    return scroll;
}

static QWidget* createCheckboxPage()
{
    auto* scroll = new QScrollArea();
    scroll->setWidgetResizable(true);
    scroll->setFrameShape(QFrame::NoFrame);

    auto* content = new QWidget();
    auto* layout = new QVBoxLayout(content);
    layout->setSpacing(24);
    layout->setContentsMargins(32, 24, 32, 24);

    // Basic
    layout->addWidget(sectionLabel("Checkbox — Basic"));
    auto* row1 = new QHBoxLayout();
    row1->setSpacing(16);
    auto* c1 = new ZCheckbox("Checked");   c1->setChecked(true);
    auto* c2 = new ZCheckbox("Unchecked");
    row1->addWidget(c1);
    row1->addWidget(c2);
    row1->addStretch();
    layout->addLayout(row1);

    // Disabled
    layout->addWidget(sectionLabel("Checkbox — Disabled"));
    auto* row2 = new QHBoxLayout();
    row2->setSpacing(16);
    auto* cd1 = new ZCheckbox("Disabled unchecked"); cd1->setEnabled(false);
    auto* cd2 = new ZCheckbox("Disabled checked");   cd2->setChecked(true); cd2->setEnabled(false);
    row2->addWidget(cd1);
    row2->addWidget(cd2);
    row2->addStretch();
    layout->addLayout(row2);

    layout->addStretch();
    scroll->setWidget(content);
    return scroll;
}

TestWidget::TestWidget(QWidget* parent)
    : QWidget(parent)
{
    setMinimumSize(900, 600);

    // Sidebar
    sidebar_ = new QListWidget();
    sidebar_->setFixedWidth(160);
    sidebar_->addItem("Button");
    sidebar_->addItem("Tag");
    sidebar_->addItem("Badge");
    sidebar_->addItem("Divider");
    sidebar_->addItem("Link");
    sidebar_->addItem("Text");
    sidebar_->addItem("Input");
    sidebar_->addItem("Radio");
    sidebar_->addItem("Checkbox");
    sidebar_->setFont(QFont("", 13));
    sidebar_->setStyleSheet(
        "QListWidget { background: #f5f7fa; border: none; outline: none; }"
        "QListWidget::item { padding: 12px 16px; }"
        "QListWidget::item:selected { background: #ecf5ff; color: #409eff; font-weight: bold; }"
        "QListWidget::item:hover { background: #e8eaed; }"
    );

    // Stacked pages
    stack_ = new QStackedWidget();
    stack_->addWidget(createButtonPage());
    stack_->addWidget(createTagPage());
    stack_->addWidget(createBadgePage());
    stack_->addWidget(createDividerPage());
    stack_->addWidget(createLinkPage());
    stack_->addWidget(createTextPage());
    stack_->addWidget(createInputPage());
    stack_->addWidget(createRadioPage());
    stack_->addWidget(createCheckboxPage());

    // Wire sidebar → stack
    QObject::connect(sidebar_, &QListWidget::currentRowChanged,
                     stack_, &QStackedWidget::setCurrentIndex);
    sidebar_->setCurrentRow(0);

    // Main layout
    auto* layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->addWidget(sidebar_);
    layout->addWidget(stack_);
}
