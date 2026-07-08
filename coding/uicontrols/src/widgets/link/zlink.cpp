#include "zlink.h"

#include <QFontMetrics>
#include <QMouseEvent>
#include <QPainter>

#include "painter/painter.h"

ZLink::ZLink(QWidget* parent)
    : QWidget(parent)
    , state_tracker_(new statemachine::StateTracker(this))
{
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    setCursor(Qt::PointingHandCursor);
}

ZLink::ZLink(const QString& text, QWidget* parent)
    : QWidget(parent)
    , text_(text)
    , state_tracker_(new statemachine::StateTracker(this))
{
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    setCursor(Qt::PointingHandCursor);
}

void ZLink::setText(const QString& text) {
    text_ = text;
    updateGeometry();
    update();
}

void ZLink::setLinkType(LinkType type) {
    type_ = type;
    update();
}

void ZLink::setUnderline(bool underline) {
    underline_ = underline;
    update();
}

QString ZLink::text() const { return text_; }

ZLink::LinkType ZLink::linkType() const { return type_; }

bool ZLink::isUnderline() const { return underline_; }

QSize ZLink::sizeHint() const {
    QFont f = font();
    f.setPixelSize(14);
    f.setWeight(QFont::Medium);
    QFontMetrics fm(f);
    int w = fm.horizontalAdvance(text_);
    return QSize(w + 4, 22);
}

void ZLink::paintEvent(QPaintEvent*) {
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    QFont f = font();
    f.setPixelSize(14);
    f.setWeight(QFont::Medium);

    bool hovered = (state_tracker_->CurrentState() ==
                    statemachine::ComponentState::kHover);

    // Resolve text color
    QColor tc;
    if (!isEnabled()) {
        tc = theme::textDisabled();
    } else if (hovered) {
        tc = theme::buttonLinkText(static_cast<int>(type_), theme::kHover);
    } else {
        tc = theme::buttonLinkText(static_cast<int>(type_), theme::kNormal);
    }

    // Draw text
    painter::DrawText(p, rect(), text_, f, tc,
                      Qt::AlignLeft | Qt::AlignVCenter);

    // Underline: draw 1px line at text bottom
    if (underline_) {
        QFontMetrics fm(f);
        int textW = fm.horizontalAdvance(text_);
        qreal underlineY = rect().center().y() + fm.height() / 2.0 - 1;
        p.setPen(QPen(tc, 1));
        p.drawLine(QPointF(0, underlineY), QPointF(textW, underlineY));
    }
}

void ZLink::enterEvent(QEvent*) {
    state_tracker_->SetHovered(true);
    state_tracker_->Update();
    update();
}

void ZLink::leaveEvent(QEvent*) {
    state_tracker_->SetHovered(false);
    state_tracker_->Update();
    update();
}

void ZLink::mousePressEvent(QMouseEvent* e) {
    if (e->button() == Qt::LeftButton && isEnabled()) {
        emit clicked();
        e->accept();
        return;
    }
    QWidget::mousePressEvent(e);
}
