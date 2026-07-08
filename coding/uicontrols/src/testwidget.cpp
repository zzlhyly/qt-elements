#include "testwidget.h"

#include <QFrame>
#include <QPushButton>
#include <QButtonGroup>
#include <QHBoxLayout>
#include <QLabel>
#include <QListWidget>
#include <QScrollArea>
#include <QStackedWidget>
#include <QVBoxLayout>

#include "widgets/button/zbutton.h"
#include "tag/ztag.h"
#include "badge/zbadge.h"
#include "divider/zdivider.h"
#include "link/zlink.h"
#include "text/ztext.h"
#include "input/zinput.h"
#include "radio/zradio.h"
#include "checkbox/zcheckbox.h"
#include "switch/zswitch.h"
#include "slider/zslider.h"
#include "progress/zprogress.h"
#include "alert/zalert.h"
#include "popup/zpopup.h"
#include "tooltip/ztooltip.h"

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
    scroll->viewport()->setAutoFillBackground(false);
    auto* content = new QWidget();
    auto* layout = new QVBoxLayout(content);
    layout->setSpacing(24);
    layout->setContentsMargins(32, 24, 32, 24);

    const int kN = 6;
    const ZButton::ButtonType allTypes[kN] =
        {ZButton::kDefault, ZButton::kPrimary, ZButton::kSuccess,
         ZButton::kInfo, ZButton::kWarning, ZButton::kDanger};
    const char* allTypeNames[kN] =
        {"Default", "Primary", "Success", "Info", "Warning", "Danger"};

    // Basic - 6 types solid
    layout->addWidget(sectionLabel("Basic"));
    {
        auto* row = new QHBoxLayout();
        row->setSpacing(12);
        for (int i = 0; i < kN; ++i) {
            auto* btn = new ZButton(allTypeNames[i]);
            btn->setButtonType(allTypes[i]);
            row->addWidget(btn);
        }
        row->addStretch();
        layout->addLayout(row);
    }

    // Plain - 5 types plain, skip default
    layout->addWidget(sectionLabel("Plain"));
    {
        auto* row = new QHBoxLayout();
        row->setSpacing(12);
        for (int i = 1; i < kN; ++i) {
            auto* btn = new ZButton(allTypeNames[i]);
            btn->setButtonType(allTypes[i]);
            btn->setButtonVariant(ZButton::kPlain);
            row->addWidget(btn);
        }
        row->addStretch();
        layout->addLayout(row);
    }

    // Round - 5 types round, skip default
    layout->addWidget(sectionLabel("Round"));
    {
        auto* row = new QHBoxLayout();
        row->setSpacing(12);
        for (int i = 1; i < kN; ++i) {
            auto* btn = new ZButton(allTypeNames[i]);
            btn->setButtonType(allTypes[i]);
            btn->setRound(true);
            row->addWidget(btn);
        }
        row->addStretch();
        layout->addLayout(row);
    }

    // Circle - 5 types circle with "A"
    layout->addWidget(sectionLabel("Circle"));
    {
        auto* row = new QHBoxLayout();
        row->setSpacing(12);
        for (int i = 1; i < kN; ++i) {
            auto* btn = new ZButton("A");
            btn->setButtonType(allTypes[i]);
            btn->setCircle(true);
            row->addWidget(btn);
        }
        row->addStretch();
        layout->addLayout(row);
    }

    // Dashed - 5 types dashed, skip default
    layout->addWidget(sectionLabel("Dashed"));
    {
        auto* row = new QHBoxLayout();
        row->setSpacing(12);
        for (int i = 1; i < kN; ++i) {
            auto* btn = new ZButton(allTypeNames[i]);
            btn->setButtonType(allTypes[i]);
            btn->setButtonVariant(ZButton::kDashed);
            row->addWidget(btn);
        }
        row->addStretch();
        layout->addLayout(row);
    }

    // Disabled - all 6 types disabled
    layout->addWidget(sectionLabel("Disabled"));
    {
        auto* row = new QHBoxLayout();
        row->setSpacing(12);
        for (int i = 0; i < kN; ++i) {
            auto* btn = new ZButton(allTypeNames[i]);
            btn->setButtonType(allTypes[i]);
            btn->setEnabled(false);
            row->addWidget(btn);
        }
        row->addStretch();
        layout->addLayout(row);
    }

    // Link - ZLink primary + disabled
    layout->addWidget(sectionLabel("Link"));
    {
        auto* row = new QHBoxLayout();
        row->setSpacing(12);
        auto* link = new ZLink("Link");
        link->setLinkType(ZLink::kPrimary);
        row->addWidget(link);
        auto* linkDisabled = new ZLink("Disabled");
        linkDisabled->setLinkType(ZLink::kPrimary);
        linkDisabled->setEnabled(false);
        row->addWidget(linkDisabled);
        row->addStretch();
        layout->addLayout(row);
    }

    // Text - text basic + text disabled
    layout->addWidget(sectionLabel("Text"));
    {
        auto* row = new QHBoxLayout();
        row->setSpacing(12);
        auto* tb = new ZButton("Text");
        tb->setButtonType(ZButton::kPrimary);
        tb->setButtonVariant(ZButton::kText);
        row->addWidget(tb);
        auto* tbd = new ZButton("Disabled");
        tbd->setButtonType(ZButton::kPrimary);
        tbd->setButtonVariant(ZButton::kText);
        tbd->setEnabled(false);
        row->addWidget(tbd);
        row->addStretch();
        layout->addLayout(row);
    }

    // Loading - 1 loading primary button
    layout->addWidget(sectionLabel("Loading"));
    {
        auto* row = new QHBoxLayout();
        row->setSpacing(12);
        auto* loading = new ZButton("Loading");
        loading->setButtonType(ZButton::kPrimary);
        loading->setLoading(true);
        row->addWidget(loading);
        row->addStretch();
        layout->addLayout(row);
    }

    // Size - large / default / small primary
    layout->addWidget(sectionLabel("Size"));
    {
        auto* row = new QHBoxLayout();
        row->setSpacing(12);
        auto* lg = new ZButton("Large");
        lg->setButtonType(ZButton::kPrimary);
        lg->setButtonSize(ZButton::kLarge);
        auto* df = new ZButton("Default");
        df->setButtonType(ZButton::kPrimary);
        auto* sm = new ZButton("Small");
        sm->setButtonType(ZButton::kPrimary);
        sm->setButtonSize(ZButton::kSmall);
        row->addWidget(lg);
        row->addWidget(df);
        row->addWidget(sm);
        row->addStretch();
        layout->addLayout(row);
    }

    // Icon
    layout->addWidget(sectionLabel("Icon"));
    {
        auto* row = new QHBoxLayout();
        row->setSpacing(12);
        auto* bi1 = new ZButton(QString(QChar(0x1F50D)) + " Search");
        bi1->setButtonType(ZButton::kPrimary);
        auto* bi2 = new ZButton(QString(QChar(0x2605)) + " Star");
        bi2->setButtonType(ZButton::kSuccess);
        auto* bi3 = new ZButton(QString(QChar(0x2665)) + " Like");
        bi3->setButtonType(ZButton::kInfo);
        row->addWidget(bi1); row->addWidget(bi2); row->addWidget(bi3);
        row->addStretch();
        layout->addLayout(row);
    }

    layout->addStretch();
    scroll->setWidget(content);
    return scroll;
}

static QWidget* createTagPage()
{
    auto* scroll = new QScrollArea();
    scroll->setWidgetResizable(true);
    scroll->setFrameShape(QFrame::NoFrame);
    scroll->viewport()->setAutoFillBackground(false);
    auto* content = new QWidget();
    auto* layout = new QVBoxLayout(content);
    layout->setSpacing(24);
    layout->setContentsMargins(32, 24, 32, 24);

    const int kN = 5;
    const ZTag::TagType allTypes[kN] =
        {ZTag::kPrimary, ZTag::kSuccess, ZTag::kInfo, ZTag::kWarning, ZTag::kDanger};
    const char* allTypeNames[kN] =
        {"Primary", "Success", "Info", "Warning", "Danger"};

    // Basic - 5 types, light effect
    layout->addWidget(sectionLabel("Basic"));
    {
        auto* row = new QHBoxLayout();
        row->setSpacing(12);
        for (int i = 0; i < kN; ++i) {
            auto* tag = new ZTag(allTypeNames[i]);
            tag->setTagType(allTypes[i]);
            row->addWidget(tag);
        }
        row->addStretch();
        layout->addLayout(row);
    }

    // Closable - 5 types closable
    layout->addWidget(sectionLabel("Closable"));
    {
        auto* row = new QHBoxLayout();
        row->setSpacing(12);
        for (int i = 0; i < kN; ++i) {
            auto* tag = new ZTag(allTypeNames[i]);
            tag->setTagType(allTypes[i]);
            tag->setClosable(true);
            QObject::connect(tag, &ZTag::closed, tag, &QWidget::hide);
            row->addWidget(tag);
        }
        row->addStretch();
        layout->addLayout(row);
    }

    // Sizes - large / default / small primary
    layout->addWidget(sectionLabel("Sizes"));
    {
        auto* row = new QHBoxLayout();
        row->setSpacing(12);
        auto* lg = new ZTag("Large");
        lg->setTagType(ZTag::kPrimary);
        lg->setTagSize(ZTag::kLarge);
        auto* md = new ZTag("Default");
        md->setTagType(ZTag::kPrimary);
        auto* sm = new ZTag("Small");
        sm->setTagType(ZTag::kPrimary);
        sm->setTagSize(ZTag::kSmall);
        row->addWidget(lg);
        row->addWidget(md);
        row->addWidget(sm);
        row->addStretch();
        layout->addLayout(row);
    }

    // Theme: Dark - 5 types dark effect
    layout->addWidget(sectionLabel("Theme: Dark"));
    {
        auto* row = new QHBoxLayout();
        row->setSpacing(12);
        for (int i = 0; i < kN; ++i) {
            auto* tag = new ZTag(allTypeNames[i]);
            tag->setTagType(allTypes[i]);
            tag->setEffect(ZTag::kDark);
            row->addWidget(tag);
        }
        row->addStretch();
        layout->addLayout(row);
    }

    // Theme: Light - 5 types light effect
    layout->addWidget(sectionLabel("Theme: Light"));
    {
        auto* row = new QHBoxLayout();
        row->setSpacing(12);
        for (int i = 0; i < kN; ++i) {
            auto* tag = new ZTag(allTypeNames[i]);
            tag->setTagType(allTypes[i]);
            tag->setEffect(ZTag::kLight);
            row->addWidget(tag);
        }
        row->addStretch();
        layout->addLayout(row);
    }

    // Theme: Plain - 5 types plain effect
    layout->addWidget(sectionLabel("Theme: Plain"));
    {
        auto* row = new QHBoxLayout();
        row->setSpacing(12);
        for (int i = 0; i < kN; ++i) {
            auto* tag = new ZTag(allTypeNames[i]);
            tag->setTagType(allTypes[i]);
            tag->setEffect(ZTag::kPlain);
            row->addWidget(tag);
        }
        row->addStretch();
        layout->addLayout(row);
    }

    // Round - 5 types round
    layout->addWidget(sectionLabel("Round"));
    {
        auto* row = new QHBoxLayout();
        row->setSpacing(12);
        for (int i = 0; i < kN; ++i) {
            auto* tag = new ZTag(allTypeNames[i]);
            tag->setTagType(allTypes[i]);
            tag->setRound(true);
            row->addWidget(tag);
        }
        row->addStretch();
        layout->addLayout(row);
    }

    layout->addStretch();
    scroll->setWidget(content);
    return scroll;
}

static QWidget* createBadgePage()
{
    auto* scroll = new QScrollArea();
    scroll->setWidgetResizable(true);
    scroll->setFrameShape(QFrame::NoFrame);
    scroll->viewport()->setAutoFillBackground(false);
    auto* content = new QWidget();
    auto* layout = new QVBoxLayout(content);
    layout->setSpacing(24);
    layout->setContentsMargins(32, 24, 32, 24);

    const int kN = 5;
    const ZBadge::BadgeType allTypes[kN] =
        {ZBadge::kPrimary, ZBadge::kSuccess, ZBadge::kInfo,
         ZBadge::kWarning, ZBadge::kDanger};
    const int values[kN] = {10, 20, 30, 40, 50};

    // Basic - 5 badges with type-specific values
    layout->addWidget(sectionLabel("Basic"));
    {
        auto* row = new QHBoxLayout();
        row->setSpacing(16);
        for (int i = 0; i < kN; ++i) {
            auto* badge = new ZBadge(values[i]);
            badge->setBadgeType(allTypes[i]);
            row->addWidget(badge);
        }
        row->addStretch();
        layout->addLayout(row);
    }

    // Dot Mode - 5 badges dot=true
    layout->addWidget(sectionLabel("Dot Mode"));
    {
        auto* row = new QHBoxLayout();
        row->setSpacing(16);
        for (int i = 0; i < kN; ++i) {
            auto* badge = new ZBadge();
            badge->setBadgeType(allTypes[i]);
            badge->setDot(true);
            row->addWidget(badge);
        }
        row->addStretch();
        layout->addLayout(row);
    }

    // Max Value - value=150 (shows 99+) and value=50
    layout->addWidget(sectionLabel("Max Value"));
    {
        auto* row = new QHBoxLayout();
        row->setSpacing(16);
        auto* b1 = new ZBadge(150);
        b1->setBadgeType(ZBadge::kDanger);
        row->addWidget(b1);
        auto* b2 = new ZBadge(50);
        b2->setBadgeType(ZBadge::kDanger);
        row->addWidget(b2);
        row->addStretch();
        layout->addLayout(row);
    }

    layout->addStretch();
    scroll->setWidget(content);
    return scroll;
}

static QWidget* createDividerPage()
{
    auto* scroll = new QScrollArea();
    scroll->setWidgetResizable(true);
    scroll->setFrameShape(QFrame::NoFrame);
    scroll->viewport()->setAutoFillBackground(false);
    auto* content = new QWidget();
    auto* layout = new QVBoxLayout(content);
    layout->setSpacing(24);
    layout->setContentsMargins(32, 24, 32, 24);

    // Basic - plain horizontal divider
    layout->addWidget(sectionLabel("Basic"));
    layout->addWidget(new ZDivider());

    // With Text - left / center / right
    layout->addWidget(sectionLabel("With Text"));
    {
        auto* dLeft = new ZDivider("Left");
        dLeft->setContentPosition(ZDivider::kLeft);
        layout->addWidget(dLeft);
    }
    layout->addWidget(new ZDivider("Center"));
    {
        auto* dRight = new ZDivider("Right");
        dRight->setContentPosition(ZDivider::kRight);
        layout->addWidget(dRight);
    }

    // Dashed/Dotted
    layout->addWidget(sectionLabel("Dashed/Dotted"));
    {
        auto* dDashed = new ZDivider("Dashed");
        dDashed->setBorderStyle(ZDivider::kDashed);
        layout->addWidget(dDashed);
    }
    {
        auto* dDotted = new ZDivider("Dotted");
        dDotted->setBorderStyle(ZDivider::kDotted);
        layout->addWidget(dDotted);
    }

    layout->addStretch();
    scroll->setWidget(content);
    return scroll;
}

static QWidget* createLinkPage()
{
    auto* scroll = new QScrollArea();
    scroll->setWidgetResizable(true);
    scroll->setFrameShape(QFrame::NoFrame);
    scroll->viewport()->setAutoFillBackground(false);
    auto* content = new QWidget();
    auto* layout = new QVBoxLayout(content);
    layout->setSpacing(24);
    layout->setContentsMargins(32, 24, 32, 24);

    const int kN = 6;
    const ZLink::LinkType allTypes[kN] =
        {ZLink::kDefault, ZLink::kPrimary, ZLink::kSuccess,
         ZLink::kWarning, ZLink::kDanger, ZLink::kInfo};
    const char* allTypeNames[kN] =
        {"Default", "Primary", "Success", "Warning", "Danger", "Info"};

    // Basic - all 6 types
    layout->addWidget(sectionLabel("Basic"));
    {
        auto* row = new QHBoxLayout();
        row->setSpacing(16);
        for (int i = 0; i < kN; ++i) {
            auto* link = new ZLink(allTypeNames[i]);
            link->setLinkType(allTypes[i]);
            row->addWidget(link);
        }
        row->addStretch();
        layout->addLayout(row);
    }

    // Underline - 2 links with underline always on
    layout->addWidget(sectionLabel("Underline"));
    {
        auto* row = new QHBoxLayout();
        row->setSpacing(16);
        auto* l1 = new ZLink("With underline");
        l1->setLinkType(ZLink::kInfo);
        l1->setUnderline(true);
        row->addWidget(l1);
        auto* l2 = new ZLink("Always show");
        l2->setLinkType(ZLink::kInfo);
        l2->setUnderline(true);
        row->addWidget(l2);
        row->addStretch();
        layout->addLayout(row);
    }

    // Disabled - 3 disabled links
    layout->addWidget(sectionLabel("Disabled"));
    {
        auto* row = new QHBoxLayout();
        row->setSpacing(16);
        auto* d1 = new ZLink("Default");
        d1->setEnabled(false);
        row->addWidget(d1);
        auto* d2 = new ZLink("Primary");
        d2->setLinkType(ZLink::kPrimary);
        d2->setEnabled(false);
        row->addWidget(d2);
        auto* d3 = new ZLink("Info");
        d3->setLinkType(ZLink::kInfo);
        d3->setEnabled(false);
        row->addWidget(d3);
        row->addStretch();
        layout->addLayout(row);
    }

    layout->addStretch();
    scroll->setWidget(content);
    return scroll;
}

static QWidget* createTextPage()
{
    auto* scroll = new QScrollArea();
    scroll->setWidgetResizable(true);
    scroll->setFrameShape(QFrame::NoFrame);
    scroll->viewport()->setAutoFillBackground(false);
    auto* content = new QWidget();
    auto* layout = new QVBoxLayout(content);
    layout->setSpacing(24);
    layout->setContentsMargins(32, 24, 32, 24);

    // Types - all 6 text types in one row
    layout->addWidget(sectionLabel("Types"));
    {
        auto* row = new QHBoxLayout();
        row->setSpacing(16);
        ZText::TextType types[] =
            {ZText::kDefault, ZText::kPrimary, ZText::kSuccess,
             ZText::kInfo, ZText::kWarning, ZText::kDanger};
        const char* names[] =
            {"Default", "Primary", "Success", "Info", "Warning", "Danger"};
        for (int i = 0; i < 6; ++i) {
            auto* t = new ZText(names[i]);
            t->setTextType(types[i]);
            row->addWidget(t);
        }
        row->addStretch();
        layout->addLayout(row);
    }

    // Sizes - large / default / small
    layout->addWidget(sectionLabel("Sizes"));
    {
        auto* row = new QHBoxLayout();
        row->setSpacing(16);
        auto* lg = new ZText("Large");
        lg->setTextSize(ZText::kLarge);
        lg->setTextType(ZText::kPrimary);
        auto* df = new ZText("Default");
        df->setTextType(ZText::kPrimary);
        auto* sm = new ZText("Small");
        sm->setTextSize(ZText::kSmall);
        sm->setTextType(ZText::kPrimary);
        row->addWidget(lg);
        row->addWidget(df);
        row->addWidget(sm);
        row->addStretch();
        layout->addLayout(row);
    }

    // Truncated - long text truncated at 200px
    layout->addWidget(sectionLabel("Truncated"));
    {
        auto* tr = new ZText("This is a very long text that should be truncated "
                             "with ellipsis when it exceeds the available width");
        tr->setTruncated(true);
        tr->setFixedWidth(200);
        tr->setTextType(ZText::kPrimary);
        layout->addWidget(tr);
    }

    layout->addStretch();
    scroll->setWidget(content);
    return scroll;
}

static QWidget* createInputPage()
{
    auto* scroll = new QScrollArea();
    scroll->setWidgetResizable(true);
    scroll->setFrameShape(QFrame::NoFrame);
    scroll->viewport()->setAutoFillBackground(false);
    auto* content = new QWidget();
    auto* layout = new QVBoxLayout(content);
    layout->setSpacing(24);
    layout->setContentsMargins(32, 24, 32, 24);

    // Basic - one default ZInput
    layout->addWidget(sectionLabel("Basic"));
    layout->addWidget(new ZInput());

    // Placeholder
    layout->addWidget(sectionLabel("Placeholder"));
    {
        auto* input = new ZInput();
        input->setPlaceholderText("Please input");
        layout->addWidget(input);
    }

    // Clearable - clearable with default value
    layout->addWidget(sectionLabel("Clearable"));
    {
        auto* input = new ZInput();
        input->setPlaceholderText("Type something...");
        input->setText("Clear me");
        input->setClearable(true);
        layout->addWidget(input);
    }

    // Password - password mode
    layout->addWidget(sectionLabel("Password"));
    {
        auto* input = new ZInput();
        input->setPlaceholderText("Please input password");
        input->setPasswordMode(true);
        layout->addWidget(input);
    }

    // Disabled - disabled with text
    layout->addWidget(sectionLabel("Disabled"));
    {
        auto* input = new ZInput();
        input->setPlaceholderText("Disabled");
        input->setText("Disabled");
        input->setEnabled(false);
        layout->addWidget(input);
    }

    // Size - large / default / small
    layout->addWidget(sectionLabel("Size"));
    {
        auto* row = new QHBoxLayout();
        row->setSpacing(12);
        auto* lg = new ZInput();
        lg->setInputSize(ZInput::kLarge);
        lg->setPlaceholderText("Large");
        auto* df = new ZInput();
        df->setPlaceholderText("Default");
        auto* sm = new ZInput();
        sm->setInputSize(ZInput::kSmall);
        sm->setPlaceholderText("Small");
        row->addWidget(lg);
        row->addWidget(df);
        row->addWidget(sm);
        row->addStretch();
        layout->addLayout(row);
    }

    // Textarea
    layout->addWidget(sectionLabel("Textarea"));
    {
        auto* input = new ZInput(); input->setTextarea(4);
        input->setPlaceholderText("Enter multiple lines of text...");
        layout->addWidget(input);
    }

    // With Icon
    layout->addWidget(sectionLabel("With Icon"));
    {
        auto* row = new QHBoxLayout();
        row->setSpacing(12);
        auto* inp1 = new ZInput(); inp1->setPrefixIcon(QChar(0x1F50D));
        inp1->setPlaceholderText("Search");
        auto* inp2 = new ZInput(); inp2->setSuffixIcon(QChar(0x2713));
        inp2->setPlaceholderText("With suffix");
        row->addWidget(inp1);
        row->addWidget(inp2);
        row->addStretch();
        layout->addLayout(row);
    }

    layout->addStretch();
    scroll->setWidget(content);
    return scroll;
}

static QWidget* createRadioPage()
{
    auto* scroll = new QScrollArea();
    scroll->setWidgetResizable(true);
    scroll->setFrameShape(QFrame::NoFrame);
    scroll->viewport()->setAutoFillBackground(false);
    auto* content = new QWidget();
    auto* layout = new QVBoxLayout(content);
    layout->setSpacing(24);
    layout->setContentsMargins(32, 24, 32, 24);

    // Basic - 3 options, A checked
    layout->addWidget(sectionLabel("Basic"));
    {
        auto* group = new QButtonGroup(content);
        auto* row = new QHBoxLayout();
        row->setSpacing(16);
        auto* r1 = new ZRadio("Option A");
        auto* r2 = new ZRadio("Option B");
        auto* r3 = new ZRadio("Option C");
        r1->setChecked(true);
        group->addButton(r1);
        group->addButton(r2);
        group->addButton(r3);
        row->addWidget(r1);
        row->addWidget(r2);
        row->addWidget(r3);
        row->addStretch();
        layout->addLayout(row);
    }

    // Disabled - one checked, one unchecked
    layout->addWidget(sectionLabel("Disabled"));
    {
        auto* row = new QHBoxLayout();
        row->setSpacing(16);
        auto* rd1 = new ZRadio("Disabled unchecked");
        rd1->setEnabled(false);
        auto* rd2 = new ZRadio("Disabled checked");
        rd2->setChecked(true);
        rd2->setEnabled(false);
        row->addWidget(rd1);
        row->addWidget(rd2);
        row->addStretch();
        layout->addLayout(row);
    }

    // Vertical
    layout->addWidget(sectionLabel("Vertical"));
    {
        auto* vbox = new QVBoxLayout();
        vbox->setSpacing(12);
        auto* group = new QButtonGroup(content);
        auto* rv1 = new ZRadio("Option A"); rv1->setChecked(true);
        auto* rv2 = new ZRadio("Option B");
        auto* rv3 = new ZRadio("Option C");
        group->addButton(rv1); group->addButton(rv2); group->addButton(rv3);
        vbox->addWidget(rv1);
        vbox->addWidget(rv2);
        vbox->addWidget(rv3);
        layout->addLayout(vbox);
    }

    // Border
    layout->addWidget(sectionLabel("Border"));
    {
        auto* row = new QHBoxLayout();
        row->setSpacing(16);
        auto* rb1 = new ZRadio("Option A"); rb1->setBorder(true); rb1->setChecked(true);
        auto* rb2 = new ZRadio("Option B"); rb2->setBorder(true);
        auto* rb3 = new ZRadio("Option C"); rb3->setBorder(true);
        row->addWidget(rb1); row->addWidget(rb2); row->addWidget(rb3);
        row->addStretch();
        layout->addLayout(row);
    }

    layout->addStretch();
    scroll->setWidget(content);
    return scroll;
}

static QWidget* createCheckboxPage()
{
    auto* scroll = new QScrollArea();
    scroll->setWidgetResizable(true);
    scroll->setFrameShape(QFrame::NoFrame);
    scroll->viewport()->setAutoFillBackground(false);
    auto* content = new QWidget();
    auto* layout = new QVBoxLayout(content);
    layout->setSpacing(24);
    layout->setContentsMargins(32, 24, 32, 24);

    // Basic - 3 checkboxes
    layout->addWidget(sectionLabel("Basic"));
    {
        auto* row = new QHBoxLayout();
        row->setSpacing(16);
        row->addWidget(new ZCheckbox("Option A"));
        row->addWidget(new ZCheckbox("Option B"));
        row->addWidget(new ZCheckbox("Option C"));
        row->addStretch();
        layout->addLayout(row);
    }

    // Disabled - one checked, one unchecked
    layout->addWidget(sectionLabel("Disabled"));
    {
        auto* row = new QHBoxLayout();
        row->setSpacing(16);
        auto* cd1 = new ZCheckbox("Disabled unchecked");
        cd1->setEnabled(false);
        auto* cd2 = new ZCheckbox("Disabled checked");
        cd2->setChecked(true);
        cd2->setEnabled(false);
        row->addWidget(cd1);
        row->addWidget(cd2);
        row->addStretch();
        layout->addLayout(row);
    }

    // Checked
    layout->addWidget(sectionLabel("Checked"));
    {
        auto* row = new QHBoxLayout();
        row->setSpacing(16);
        auto* cc1 = new ZCheckbox("Checked");  cc1->setChecked(true);
        auto* cc2 = new ZCheckbox("Unchecked");
        row->addWidget(cc1);
        row->addWidget(cc2);
        row->addStretch();
        layout->addLayout(row);
    }

    // Indeterminate
    layout->addWidget(sectionLabel("Indeterminate"));
    {
        auto* ci = new ZCheckbox("Indeterminate");
        ci->setIndeterminate(true);
        layout->addWidget(ci);
    }

    layout->addStretch();
    scroll->setWidget(content);
    return scroll;
}

static QWidget* createSwitchPage()
{
    auto* scroll = new QScrollArea();
    scroll->setWidgetResizable(true);
    scroll->setFrameShape(QFrame::NoFrame);
    scroll->viewport()->setAutoFillBackground(false);
    auto* content = new QWidget();
    auto* layout = new QVBoxLayout(content);
    layout->setSpacing(24);
    layout->setContentsMargins(32, 24, 32, 24);

    // Basic - one OFF, one ON (checked)
    layout->addWidget(sectionLabel("Basic"));
    {
        auto* row = new QHBoxLayout();
        row->setSpacing(16);
        row->addWidget(new ZSwitch());
        auto* on = new ZSwitch();
        on->setChecked(true);
        row->addWidget(on);
        row->addStretch();
        layout->addLayout(row);
    }

    // Disabled - disabled OFF + disabled ON
    layout->addWidget(sectionLabel("Disabled"));
    {
        auto* row = new QHBoxLayout();
        row->setSpacing(16);
        auto* off = new ZSwitch();
        off->setEnabled(false);
        auto* on = new ZSwitch();
        on->setChecked(true);
        on->setEnabled(false);
        row->addWidget(off);
        row->addWidget(on);
        row->addStretch();
        layout->addLayout(row);
    }

    // With Label
    layout->addWidget(sectionLabel("With Label"));
    {
        auto* row = new QHBoxLayout();
        row->setSpacing(12);
        auto* sw = new ZSwitch();
        auto* label = new QLabel("Toggle me");
        label->setFont(QFont("", 13));
        row->addWidget(sw);
        row->addWidget(label);
        row->addStretch();
        layout->addLayout(row);
    }

    // Sizes
    layout->addWidget(sectionLabel("Sizes"));
    {
        auto* row = new QHBoxLayout();
        row->setSpacing(16);
        auto* sl = new ZSwitch(); sl->setSwitchSize(ZSwitch::kLarge);
        auto* sd = new ZSwitch();
        auto* ss = new ZSwitch(); ss->setSwitchSize(ZSwitch::kSmall);
        auto* slon = new ZSwitch(); slon->setSwitchSize(ZSwitch::kLarge); slon->setChecked(true);
        auto* sdon = new ZSwitch(); sdon->setChecked(true);
        auto* sson = new ZSwitch(); sson->setSwitchSize(ZSwitch::kSmall); sson->setChecked(true);
        row->addWidget(sl); row->addWidget(slon);
        row->addWidget(sd); row->addWidget(sdon);
        row->addWidget(ss); row->addWidget(sson);
        row->addStretch();
        layout->addLayout(row);
    }

    // Loading
    layout->addWidget(sectionLabel("Loading"));
    {
        auto* row = new QHBoxLayout();
        row->setSpacing(16);
        auto* swl1 = new ZSwitch(); swl1->setLoading(true);
        auto* swl2 = new ZSwitch(); swl2->setChecked(true); swl2->setLoading(true);
        row->addWidget(swl1);
        row->addWidget(swl2);
        row->addStretch();
        layout->addLayout(row);
    }

    // Active Text
    layout->addWidget(sectionLabel("Active Text"));
    {
        auto* row = new QHBoxLayout();
        row->setSpacing(16);
        auto* swt1 = new ZSwitch(); swt1->setActiveText("ON"); swt1->setInactiveText("OFF");
        auto* swt2 = new ZSwitch(); swt2->setChecked(true); swt2->setActiveText("Yes"); swt2->setInactiveText("No");
        row->addWidget(swt1);
        row->addWidget(swt2);
        row->addStretch();
        layout->addLayout(row);
    }

    layout->addStretch();
    scroll->setWidget(content);
    return scroll;
}

static QWidget* createSliderPage()
{
    auto* scroll = new QScrollArea();
    scroll->setWidgetResizable(true);
    scroll->setFrameShape(QFrame::NoFrame);
    scroll->viewport()->setAutoFillBackground(false);
    auto* content = new QWidget();
    auto* layout = new QVBoxLayout(content);
    layout->setSpacing(24);
    layout->setContentsMargins(32, 24, 32, 24);

    // Basic - at 0, 50, 100
    layout->addWidget(sectionLabel("Basic"));
    {
        auto* s0 = new ZSlider();
        s0->setValue(0);
        auto* s50 = new ZSlider();
        s50->setValue(50);
        auto* s100 = new ZSlider();
        s100->setValue(100);
        layout->addWidget(s0);
        layout->addWidget(s50);
        layout->addWidget(s100);
    }

    // Disabled - disabled at value 30
    layout->addWidget(sectionLabel("Disabled"));
    {
        auto* sd = new ZSlider();
        sd->setValue(30);
        sd->setEnabled(false);
        layout->addWidget(sd);
    }

    // Range
    layout->addWidget(sectionLabel("Range"));
    {
        auto* sr1 = new ZSlider(); sr1->setMinimum(0);  sr1->setMaximum(50);  sr1->setValue(25);
        auto* sr2 = new ZSlider(); sr2->setMinimum(20); sr2->setMaximum(80);  sr2->setValue(50);
        layout->addWidget(sr1);
        layout->addWidget(sr2);
    }

    // Stops
    layout->addWidget(sectionLabel("Stops"));
    {
        auto* ss = new ZSlider(); ss->setStep(25); ss->setShowStops(true); ss->setValue(50);
        layout->addWidget(ss);
    }

    layout->addStretch();
    scroll->setWidget(content);
    return scroll;
}

static QWidget* createProgressPage()
{
    auto* scroll = new QScrollArea();
    scroll->setWidgetResizable(true);
    scroll->setFrameShape(QFrame::NoFrame);
    scroll->viewport()->setAutoFillBackground(false);
    auto* content = new QWidget();
    auto* layout = new QVBoxLayout(content);
    layout->setSpacing(24);
    layout->setContentsMargins(32, 24, 32, 24);

    // Basic - line at 0%, 50%, 100%
    layout->addWidget(sectionLabel("Basic"));
    {
        auto* p0 = new ZProgress();
        p0->setPercentage(0);
        auto* p50 = new ZProgress();
        p50->setPercentage(50);
        auto* p100 = new ZProgress();
        p100->setPercentage(100);
        layout->addWidget(p0);
        layout->addWidget(p50);
        layout->addWidget(p100);
    }

    // Status - 60% with success / exception / warning
    layout->addWidget(sectionLabel("Status"));
    {
        auto* ps = new ZProgress();
        ps->setPercentage(60);
        ps->setStatus(ZProgress::kSuccess);
        auto* pe = new ZProgress();
        pe->setPercentage(60);
        pe->setStatus(ZProgress::kException);
        auto* pw = new ZProgress();
        pw->setPercentage(60);
        pw->setStatus(ZProgress::kWarning);
        layout->addWidget(ps);
        layout->addWidget(pe);
        layout->addWidget(pw);
    }

    // Circle - 0%, 50%, 100%
    layout->addWidget(sectionLabel("Circle"));
    {
        auto* row = new QHBoxLayout();
        row->setSpacing(16);
        auto* pc0 = new ZProgress();
        pc0->setType(ZProgress::kCircle);
        pc0->setPercentage(0);
        auto* pc50 = new ZProgress();
        pc50->setType(ZProgress::kCircle);
        pc50->setPercentage(50);
        auto* pc100 = new ZProgress();
        pc100->setType(ZProgress::kCircle);
        pc100->setPercentage(100);
        row->addWidget(pc0);
        row->addWidget(pc50);
        row->addWidget(pc100);
        row->addStretch();
        layout->addLayout(row);
    }

    // Stroke Width
    layout->addWidget(sectionLabel("Stroke Width"));
    {
        auto* row = new QHBoxLayout();
        row->setSpacing(16);
        auto* ps1 = new ZProgress(); ps1->setPercentage(50); ps1->setStrokeWidth(3);
        auto* ps2 = new ZProgress(); ps2->setPercentage(50); ps2->setStrokeWidth(6);
        auto* ps3 = new ZProgress(); ps3->setPercentage(50); ps3->setStrokeWidth(12);
        row->addWidget(ps1);
        row->addWidget(ps2);
        row->addWidget(ps3);
        row->addStretch();
        layout->addLayout(row);
    }

    // Show Text
    layout->addWidget(sectionLabel("Show Text"));
    {
        auto* pt1 = new ZProgress(); pt1->setPercentage(60); pt1->setShowText(true);
        auto* pt2 = new ZProgress(); pt2->setPercentage(60); pt2->setShowText(false);
        layout->addWidget(pt1);
        layout->addWidget(pt2);
    }

    // Dashboard
    layout->addWidget(sectionLabel("Dashboard"));
    {
        auto* row = new QHBoxLayout();
        row->setSpacing(16);
        auto* pd0 = new ZProgress(); pd0->setType(ZProgress::kDashboard); pd0->setPercentage(0);
        auto* pd30 = new ZProgress(); pd30->setType(ZProgress::kDashboard); pd30->setPercentage(30);
        auto* pd80 = new ZProgress(); pd80->setType(ZProgress::kDashboard); pd80->setPercentage(80);
        row->addWidget(pd0); row->addWidget(pd30); row->addWidget(pd80);
        row->addStretch();
        layout->addLayout(row);
    }

    // Indeterminate
    layout->addWidget(sectionLabel("Indeterminate"));
    {
        auto* pi = new ZProgress(); pi->setIndeterminate(true);
        layout->addWidget(pi);
    }

    // Text Inside
    layout->addWidget(sectionLabel("Text Inside"));
    {
        auto* pt = new ZProgress(); pt->setPercentage(70); pt->setStrokeWidth(18); pt->setTextInside(true);
        layout->addWidget(pt);
    }

    layout->addStretch();
    scroll->setWidget(content);
    return scroll;
}

static QWidget* createAlertPage()
{
    auto* scroll = new QScrollArea();
    scroll->setWidgetResizable(true);
    scroll->setFrameShape(QFrame::NoFrame);
    scroll->viewport()->setAutoFillBackground(false);
    auto* content = new QWidget();
    auto* layout = new QVBoxLayout(content);
    layout->setSpacing(24);
    layout->setContentsMargins(32, 24, 32, 24);

    // Basic - 4 alerts with titles
    layout->addWidget(sectionLabel("Basic"));
    layout->addWidget(new ZAlert("Success alert", ZAlert::kSuccess));
    layout->addWidget(new ZAlert("Info alert", ZAlert::kInfo));
    layout->addWidget(new ZAlert("Warning alert", ZAlert::kWarning));
    layout->addWidget(new ZAlert("Error alert", ZAlert::kError));

    // Theme - 4 light + 4 dark
    layout->addWidget(sectionLabel("Theme"));
    // light (default effect)
    layout->addWidget(new ZAlert("Success light", ZAlert::kSuccess));
    layout->addWidget(new ZAlert("Info light", ZAlert::kInfo));
    layout->addWidget(new ZAlert("Warning light", ZAlert::kWarning));
    layout->addWidget(new ZAlert("Error light", ZAlert::kError));
    // dark
    {
        auto* ad1 = new ZAlert("Success dark", ZAlert::kSuccess);
        ad1->setEffect(ZAlert::kDark);
        auto* ad2 = new ZAlert("Info dark", ZAlert::kInfo);
        ad2->setEffect(ZAlert::kDark);
        auto* ad3 = new ZAlert("Warning dark", ZAlert::kWarning);
        ad3->setEffect(ZAlert::kDark);
        auto* ad4 = new ZAlert("Error dark", ZAlert::kError);
        ad4->setEffect(ZAlert::kDark);
        layout->addWidget(ad1);
        layout->addWidget(ad2);
        layout->addWidget(ad3);
        layout->addWidget(ad4);
    }

    // Closable - 4 closable alerts
    layout->addWidget(sectionLabel("Closable"));
    {
        auto* a1 = new ZAlert("Success alert", ZAlert::kSuccess);
        a1->setClosable(true);
        QObject::connect(a1, &ZAlert::closed, a1, &QWidget::hide);
        layout->addWidget(a1);
        auto* a2 = new ZAlert("Info alert", ZAlert::kInfo);
        a2->setClosable(true);
        QObject::connect(a2, &ZAlert::closed, a2, &QWidget::hide);
        layout->addWidget(a2);
        auto* a3 = new ZAlert("Warning alert", ZAlert::kWarning);
        a3->setClosable(true);
        QObject::connect(a3, &ZAlert::closed, a3, &QWidget::hide);
        layout->addWidget(a3);
        auto* a4 = new ZAlert("Error alert", ZAlert::kError);
        a4->setClosable(true);
        QObject::connect(a4, &ZAlert::closed, a4, &QWidget::hide);
        layout->addWidget(a4);
    }

    // show-icon - one with, one without
    layout->addWidget(sectionLabel("show-icon"));
    layout->addWidget(new ZAlert("With icon", ZAlert::kInfo));
    {
        auto* ani = new ZAlert("No icon", ZAlert::kInfo);
        ani->setShowIcon(false);
        layout->addWidget(ani);
    }

    // center - one centered alert
    layout->addWidget(sectionLabel("center"));
    {
        auto* ac = new ZAlert("Centered alert text", ZAlert::kInfo);
        ac->setCenter(true);
        layout->addWidget(ac);
    }

    // description - one alert with long description text as title
    layout->addWidget(sectionLabel("description"));
    {
        auto* ad = new ZAlert(
            "This is a longer description that explains the alert in more detail. "
            "It provides additional context for the user about what happened.",
            ZAlert::kInfo);
        layout->addWidget(ad);
    }

    layout->addStretch();
    scroll->setWidget(content);
    return scroll;
}

static QWidget* createTooltipPage()
{
    auto* scroll = new QScrollArea();
    scroll->setWidgetResizable(true);
    scroll->setFrameShape(QFrame::NoFrame);
    scroll->viewport()->setAutoFillBackground(false);
    auto* content = new QWidget();
    auto* layout = new QVBoxLayout(content);
    layout->setSpacing(24);
    layout->setContentsMargins(32, 24, 32, 24);

    // Hover - 3 buttons with hover tooltips
    layout->addWidget(sectionLabel("Hover"));
    {
        auto* row = new QHBoxLayout();
        row->setSpacing(12);
        auto* btn1 = new ZButton("Top");
        btn1->setButtonType(ZButton::kPrimary);
        ZTooltip::install(btn1, "Tooltip on top", ZPopup::kTop);
        row->addWidget(btn1);
        auto* btn2 = new ZButton("Bottom");
        btn2->setButtonType(ZButton::kPrimary);
        ZTooltip::install(btn2, "Tooltip on bottom", ZPopup::kBottom);
        row->addWidget(btn2);
        auto* btn3 = new ZButton("Left");
        btn3->setButtonType(ZButton::kPrimary);
        ZTooltip::install(btn3, "Tooltip on left", ZPopup::kLeft);
        row->addWidget(btn3);
        auto* btn4 = new ZButton("Right");
        btn4->setButtonType(ZButton::kPrimary);
        ZTooltip::install(btn4, "Tooltip on right", ZPopup::kRight);
        row->addWidget(btn4);
        row->addStretch();
        layout->addLayout(row);
    }

    // Static - button calls ZTooltip::showText on click
    layout->addWidget(sectionLabel("Static"));
    {
        auto* row = new QHBoxLayout();
        row->setSpacing(12);
        auto* btnShow = new ZButton("Click to show tooltip");
        btnShow->setButtonType(ZButton::kPrimary);
        QObject::connect(btnShow, &QPushButton::clicked, [btnShow]() {
            ZTooltip::showText(btnShow, "Static tooltip - auto-hides after 3s", 3000);
        });
        row->addWidget(btnShow);
        row->addStretch();
        layout->addLayout(row);
    }

    layout->addStretch();
    scroll->setWidget(content);
    return scroll;
}

TestWidget::TestWidget(QWidget* parent)
    : QWidget(parent)
{
    setMinimumSize(900, 600);
    setAutoFillBackground(true);
    {
        QPalette pal = palette();
        pal.setColor(QPalette::Window, QColor(0xf5, 0xf7, 0xfa));
        setPalette(pal);
    }

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
    sidebar_->addItem("Switch");
    sidebar_->addItem("Slider");
    sidebar_->addItem("Progress");
    sidebar_->addItem("Alert");
    sidebar_->addItem("Tooltip");
    sidebar_->setFont(QFont("", 13));
    sidebar_->setFrameShape(QFrame::NoFrame);
    sidebar_->setSpacing(0);
    {
        QPalette pal = sidebar_->palette();
        pal.setColor(QPalette::Base, QColor(0xf5, 0xf7, 0xfa));
        pal.setColor(QPalette::Highlight, QColor(0xec, 0xf5, 0xff));
        pal.setColor(QPalette::HighlightedText, QColor(0x40, 0x9e, 0xff));
        sidebar_->setPalette(pal);
    }

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
    stack_->addWidget(createSwitchPage());
    stack_->addWidget(createSliderPage());
    stack_->addWidget(createProgressPage());
    stack_->addWidget(createAlertPage());
    stack_->addWidget(createTooltipPage());

    // Wire sidebar -> stack
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
