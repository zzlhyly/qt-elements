#include "zlink.h"
#include "theme/theme.h"

#include <QFontMetrics>
#include <QMouseEvent>
#include <QPainter>

ZLink::ZLink(QWidget* parent)
    : QWidget(parent)
{
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    setCursor(Qt::PointingHandCursor);
}

ZLink::ZLink(const QString& text, QWidget* parent)
    : QWidget(parent)
    , text_(text)
{
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    setCursor(Qt::PointingHandCursor);
}

void ZLink::setText(const QString& text)
{
    text_ = text;
    updateGeometry();
    update();
}

void ZLink::setLinkType(LinkType type)
{
    type_ = type;
    update();
}

void ZLink::setUnderline(bool underline)
{
    underline_ = underline;
    update();
}

QString ZLink::text() const { return text_; }
ZLink::LinkType ZLink::linkType() const { return type_; }
bool ZLink::isUnderline() const { return underline_; }

QSize ZLink::sizeHint() const
{
    QFont f = font();
    f.setPixelSize(14);
    f.setWeight(QFont::Medium);
    QFontMetrics fm(f);
    int w = fm.horizontalAdvance(text_);
    return QSize(w, 22);
}

void ZLink::paintEvent(QPaintEvent*)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    QFont f = font();
    f.setPixelSize(14);
    f.setWeight(QFont::Medium);
    p.setFont(f);

    // Determine state for theme lookup
    theme::State state = theme::kNormal;
    if (!isEnabled()) {
        state = theme::kDisabled;
    } else if (hovered_) {
        state = theme::kHover;
    }

    QColor tc;
    if (!isEnabled()) {
        tc = theme::textDisabled();
    } else {
        tc = theme::buttonLinkText(static_cast<int>(type_), state);
    }

    p.setPen(tc);

    QFontMetrics fm(f);
    QRect textRect(0, 0, fm.horizontalAdvance(text_), fm.height());
    textRect.moveCenter(rect().center());
    textRect.moveLeft(0);  // left-align, not center

    // Adjust for actual widget rect
    textRect.setLeft(0);
    textRect.setRight(width());

    p.drawText(textRect, Qt::AlignLeft | Qt::AlignVCenter, text_);

    // Underline: draw 1px line under text
    if (hovered_ || underline_) {
        int textW = fm.horizontalAdvance(text_);
        qreal underlineY = rect().center().y() + fm.height() / 2.0 - 1;
        QPen underlinePen(tc, 1);
        p.setPen(underlinePen);
        p.drawLine(QPointF(0, underlineY), QPointF(textW, underlineY));
    }
}

void ZLink::enterEvent(QEvent*)
{
    hovered_ = true;
    update();
}

void ZLink::leaveEvent(QEvent*)
{
    hovered_ = false;
    update();
}

void ZLink::mousePressEvent(QMouseEvent* e)
{
    if (e->button() == Qt::LeftButton && isEnabled()) {
        emit clicked();
        e->accept();
        return;
    }
    QWidget::mousePressEvent(e);
}
