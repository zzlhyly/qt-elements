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

#include "button/zbutton.h"
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

    // 基础用法 — all 6 types solid
    layout->addWidget(sectionLabel("基础用法"));
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

    // 朴素按钮 — 5 types plain (skip default)
    layout->addWidget(sectionLabel("朴素按钮"));
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

    // 圆角按钮 — 5 types round (skip default)
    layout->addWidget(sectionLabel("圆角按钮"));
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

    // 圆形按钮 — 5 types circle with single char "A"
    layout->addWidget(sectionLabel("圆形按钮"));
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

    // 虚线按钮 — 5 types dashed (skip default)
    layout->addWidget(sectionLabel("虚线按钮"));
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

    // 禁用状态 — all 6 types disabled, solid
    layout->addWidget(sectionLabel("禁用状态"));
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

    // 链接按钮 — ZLink primary + disabled
    layout->addWidget(sectionLabel("链接按钮"));
    {
        auto* row = new QHBoxLayout();
        row->setSpacing(12);
        auto* link = new ZLink("链接按钮");
        link->setLinkType(ZLink::kPrimary);
        row->addWidget(link);
        auto* linkDisabled = new ZLink("禁用链接");
        linkDisabled->setLinkType(ZLink::kPrimary);
        linkDisabled->setEnabled(false);
        row->addWidget(linkDisabled);
        row->addStretch();
        layout->addLayout(row);
    }

    // 文字按钮 — text basic + text disabled
    layout->addWidget(sectionLabel("文字按钮"));
    {
        auto* row = new QHBoxLayout();
        row->setSpacing(12);
        auto* tb = new ZButton("文字按钮");
        tb->setButtonType(ZButton::kPrimary);
        tb->setButtonVariant(ZButton::kText);
        row->addWidget(tb);
        auto* tbd = new ZButton("禁用文字");
        tbd->setButtonType(ZButton::kPrimary);
        tbd->setButtonVariant(ZButton::kText);
        tbd->setEnabled(false);
        row->addWidget(tbd);
        row->addStretch();
        layout->addLayout(row);
    }

    // 加载中 — one loading primary button
    layout->addWidget(sectionLabel("加载中"));
    {
        auto* row = new QHBoxLayout();
        row->setSpacing(12);
        auto* loading = new ZButton("加载中");
        loading->setButtonType(ZButton::kPrimary);
        loading->setLoading(true);
        row->addWidget(loading);
        row->addStretch();
        layout->addLayout(row);
    }

    // 尺寸 — large / default / small primary
    layout->addWidget(sectionLabel("尺寸"));
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

    // 基础用法 — 5 types, light effect
    layout->addWidget(sectionLabel("基础用法"));
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

    // 可移除标签 — 5 types closable
    layout->addWidget(sectionLabel("可移除标签"));
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

    // 不同尺寸 — large / default / small, primary
    layout->addWidget(sectionLabel("不同尺寸"));
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

    // 主题 — Dark / Light / Plain sub-rows, each with 5 tags
    layout->addWidget(sectionLabel("主题"));
    {
        auto* subLayout = new QVBoxLayout();
        subLayout->setSpacing(8);
        {
            auto* subRow = new QHBoxLayout();
            subRow->setSpacing(12);
            auto* lbl = new QLabel("Dark");
            lbl->setFixedWidth(48);
            subRow->addWidget(lbl);
            for (int i = 0; i < kN; ++i) {
                auto* tag = new ZTag(allTypeNames[i]);
                tag->setTagType(allTypes[i]);
                tag->setEffect(ZTag::kDark);
                subRow->addWidget(tag);
            }
            subRow->addStretch();
            subLayout->addLayout(subRow);
        }
        {
            auto* subRow = new QHBoxLayout();
            subRow->setSpacing(12);
            auto* lbl = new QLabel("Light");
            lbl->setFixedWidth(48);
            subRow->addWidget(lbl);
            for (int i = 0; i < kN; ++i) {
                auto* tag = new ZTag(allTypeNames[i]);
                tag->setTagType(allTypes[i]);
                tag->setEffect(ZTag::kLight);
                subRow->addWidget(tag);
            }
            subRow->addStretch();
            subLayout->addLayout(subRow);
        }
        {
            auto* subRow = new QHBoxLayout();
            subRow->setSpacing(12);
            auto* lbl = new QLabel("Plain");
            lbl->setFixedWidth(48);
            subRow->addWidget(lbl);
            for (int i = 0; i < kN; ++i) {
                auto* tag = new ZTag(allTypeNames[i]);
                tag->setTagType(allTypes[i]);
                tag->setEffect(ZTag::kPlain);
                subRow->addWidget(tag);
            }
            subRow->addStretch();
            subLayout->addLayout(subRow);
        }
        layout->addLayout(subLayout);
    }

    // 圆形标签 — 5 types round
    layout->addWidget(sectionLabel("圆形标签"));
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

    // 基础用法 — 5 badges, each with different value and type
    layout->addWidget(sectionLabel("基础用法"));
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

    // 圆点模式 — 5 badges dot=true
    layout->addWidget(sectionLabel("圆点模式"));
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

    // 最大值 — value=150 (shows 99+) and value=50
    layout->addWidget(sectionLabel("最大值"));
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

    // 基础用法 — plain horizontal divider
    layout->addWidget(sectionLabel("基础用法"));
    layout->addWidget(new ZDivider());

    // 带文字 — left / center / right
    layout->addWidget(sectionLabel("带文字"));
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

    // 虚线/点线 — dashed + dotted
    layout->addWidget(sectionLabel("虚线/点线"));
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

    // 基础用法 — all 6 types
    layout->addWidget(sectionLabel("基础用法"));
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

    // 下划线 — 2 links with underline always on, info type
    layout->addWidget(sectionLabel("下划线"));
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

    // 禁用 — 3 disabled links
    layout->addWidget(sectionLabel("禁用"));
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

    // 类型 — all 6 text types in one row
    layout->addWidget(sectionLabel("类型"));
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

    // 尺寸 — large / default / small
    layout->addWidget(sectionLabel("尺寸"));
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

    // 截断 — long text with truncated=true, fixed width 200px
    layout->addWidget(sectionLabel("截断"));
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

    // 基础用法 — one default ZInput
    layout->addWidget(sectionLabel("基础用法"));
    layout->addWidget(new ZInput());

    // Placeholder
    layout->addWidget(sectionLabel("Placeholder"));
    {
        auto* input = new ZInput();
        input->setPlaceholderText("Please input");
        layout->addWidget(input);
    }

    // 可清空 — clearable with default value
    layout->addWidget(sectionLabel("可清空"));
    {
        auto* input = new ZInput();
        input->setPlaceholderText("Type something...");
        input->setText("Clear me");
        input->setClearable(true);
        layout->addWidget(input);
    }

    // 密码框 — password mode
    layout->addWidget(sectionLabel("密码框"));
    {
        auto* input = new ZInput();
        input->setPlaceholderText("Please input password");
        input->setPasswordMode(true);
        layout->addWidget(input);
    }

    // 禁用 — disabled with text
    layout->addWidget(sectionLabel("禁用"));
    {
        auto* input = new ZInput();
        input->setPlaceholderText("Disabled");
        input->setText("Disabled");
        input->setEnabled(false);
        layout->addWidget(input);
    }

    // 尺寸 — large / default / small in a row
    layout->addWidget(sectionLabel("尺寸"));
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

    // 基础用法 — 3 options, A checked
    layout->addWidget(sectionLabel("基础用法"));
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

    // 禁用 — one checked disabled, one unchecked disabled
    layout->addWidget(sectionLabel("禁用"));
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

    // 基础用法 — 3 checkboxes A/B/C
    layout->addWidget(sectionLabel("基础用法"));
    {
        auto* row = new QHBoxLayout();
        row->setSpacing(16);
        row->addWidget(new ZCheckbox("Option A"));
        row->addWidget(new ZCheckbox("Option B"));
        row->addWidget(new ZCheckbox("Option C"));
        row->addStretch();
        layout->addLayout(row);
    }

    // 禁用 — one checked disabled, one unchecked disabled
    layout->addWidget(sectionLabel("禁用"));
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

    // 基础用法 — one ON (checked), one OFF
    layout->addWidget(sectionLabel("基础用法"));
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

    // 禁用 — disabled ON + disabled OFF
    layout->addWidget(sectionLabel("禁用"));
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

    // 基础用法 — at 0 / 50 / 100
    layout->addWidget(sectionLabel("基础用法"));
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

    // 禁用 — disabled at value 30
    layout->addWidget(sectionLabel("禁用"));
    {
        auto* sd = new ZSlider();
        sd->setValue(30);
        sd->setEnabled(false);
        layout->addWidget(sd);
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

    // 线条 — 0% / 50% / 100%
    layout->addWidget(sectionLabel("线条"));
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

    // 状态 — 60% with success / exception / warning
    layout->addWidget(sectionLabel("状态"));
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

    // 圆环 — 0% / 50% / 100% circle
    layout->addWidget(sectionLabel("圆环"));
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

    // 基础用法 — 4 alerts with titles
    layout->addWidget(sectionLabel("基础用法"));
    layout->addWidget(new ZAlert("Success alert", ZAlert::kSuccess));
    layout->addWidget(new ZAlert("Info alert", ZAlert::kInfo));
    layout->addWidget(new ZAlert("Warning alert", ZAlert::kWarning));
    layout->addWidget(new ZAlert("Error alert", ZAlert::kError));

    // 主题 — 4 light (default) + 4 dark
    layout->addWidget(sectionLabel("主题"));
    // light
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

    // 可关闭 — 4 alerts closable
    layout->addWidget(sectionLabel("可关闭"));
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

    // show-icon — one with icon, one without
    layout->addWidget(sectionLabel("show-icon"));
    layout->addWidget(new ZAlert("With icon", ZAlert::kInfo));
    {
        auto* ani = new ZAlert("No icon", ZAlert::kInfo);
        ani->setShowIcon(false);
        layout->addWidget(ani);
    }

    // center — one centered alert
    layout->addWidget(sectionLabel("center"));
    {
        auto* ac = new ZAlert("Centered alert text", ZAlert::kInfo);
        ac->setCenter(true);
        layout->addWidget(ac);
    }

    // description — one alert with long description text as title
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

    // 悬停 — 3 buttons with hover tooltips (top, bottom, left)
    layout->addWidget(sectionLabel("悬停"));
    {
        auto* row = new QHBoxLayout();
        row->setSpacing(12);
        auto* btn1 = new ZButton("上边");
        btn1->setButtonType(ZButton::kPrimary);
        ZTooltip::install(btn1, "Tooltip on top");
        row->addWidget(btn1);
        auto* btn2 = new ZButton("下边");
        btn2->setButtonType(ZButton::kPrimary);
        ZTooltip::install(btn2, "Tooltip on bottom");
        row->addWidget(btn2);
        auto* btn3 = new ZButton("左边");
        btn3->setButtonType(ZButton::kPrimary);
        ZTooltip::install(btn3, "Tooltip on left");
        row->addWidget(btn3);
        row->addStretch();
        layout->addLayout(row);
    }

    // 静态展示 — button that calls ZTooltip::showText on click (3s auto-hide)
    layout->addWidget(sectionLabel("静态展示"));
    {
        auto* row = new QHBoxLayout();
        row->setSpacing(12);
        auto* btnShow = new ZButton("点击显示提示");
        btnShow->setButtonType(ZButton::kPrimary);
        QObject::connect(btnShow, &QPushButton::clicked, [btnShow]() {
            ZTooltip::showText(btnShow, "Static tooltip — auto-hides after 3s", 3000);
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
