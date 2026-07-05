#include "zbadge.h"
#include "theme/theme.h"

#include <QFontMetrics>
#include <QPainter>
#include <QPainterPath>

ZBadge::ZBadge(QWidget* parent)
    : QWidget(parent)
{
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
}

ZBadge::ZBadge(int value, QWidget* parent)
    : QWidget(parent)
    , value_(value)
{
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
}

void ZBadge::setValue(int value)
{
    value_ = value;
    updateGeometry();
    update();
}

void ZBadge::setBadgeType(BadgeType type)
{
    type_ = type;
    update();
}

void ZBadge::setMax(int max)
{
    max_ = max;
    update();
}

void ZBadge::setDot(bool dot)
{
    dot_ = dot;
    updateGeometry();
    update();
}

void ZBadge::setBadgeHidden(bool hidden)
{
    hidden_ = hidden;
    setVisible(!hidden_);
}

int ZBadge::value() const { return value_; }
ZBadge::BadgeType ZBadge::badgeType() const { return type_; }
int ZBadge::max() const { return max_; }
bool ZBadge::isDot() const { return dot_; }
bool ZBadge::isBadgeHidden() const { return hidden_; }

QSize ZBadge::sizeHint() const
{
    if (dot_) return QSize(8, 8);

    QFont f = font();
    f.setPixelSize(12);
    f.setWeight(QFont::Medium);
    QFontMetrics fm(f);

    QString displayText = QString::number(value_);
    if (value_ > max_) displayText = QString("%1+").arg(max_);

    int w = fm.horizontalAdvance(displayText) + 12;  // 6px padding each side
    w = qMax(w, 16);
    return QSize(w, 16);
}

QSize ZBadge::minimumSizeHint() const
{
    if (dot_) return QSize(8, 8);
    return QSize(16, 16);
}

void ZBadge::paintEvent(QPaintEvent*)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    QFont f = font();
    f.setPixelSize(12);
    f.setWeight(QFont::Medium);
    p.setFont(f);

    QRect r = rect();
    QColor bg = theme::tagDarkBg(static_cast<int>(type_));

    if (dot_) {
        // Draw 8px circle centered
        qreal cx = r.x() + r.width() / 2.0;
        qreal cy = r.y() + r.height() / 2.0;
        QRectF dotRect(cx - 4, cy - 4, 8, 8);
        p.setBrush(bg);
        p.setPen(Qt::NoPen);
        p.drawEllipse(dotRect);
        return;
    }

    // Normal badge: rounded rect
    qreal radius = 8.0;  // height / 2 for 16px height
    QPainterPath path;
    path.addRoundedRect(QRectF(r), radius, radius);
    p.setBrush(bg);
    p.setPen(Qt::NoPen);
    p.drawPath(path);

    // Text
    QString displayText = QString::number(value_);
    if (value_ > max_) displayText = QString("%1+").arg(max_);

    p.setPen(Qt::white);
    p.drawText(r, Qt::AlignCenter, displayText);
}
