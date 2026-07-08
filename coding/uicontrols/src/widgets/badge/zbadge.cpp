#include "zbadge.h"
#include "painter/painter.h"

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

void ZBadge::setValue(int value)          { value_ = value; updateGeometry(); update(); }
void ZBadge::setBadgeType(BadgeType type) { type_ = type; update(); }
void ZBadge::setMax(int max)              { max_ = max; update(); }
void ZBadge::setDot(bool dot)             { dot_ = dot; updateGeometry(); update(); }
void ZBadge::setBadgeHidden(bool hidden)  { hidden_ = hidden; setVisible(!hidden_); }

int ZBadge::value() const                 { return value_; }
ZBadge::BadgeType ZBadge::badgeType() const { return type_; }
int ZBadge::max() const                   { return max_; }
bool ZBadge::isDot() const                { return dot_; }
bool ZBadge::isBadgeHidden() const        { return hidden_; }

QSize ZBadge::sizeHint() const
{
    if (dot_) return QSize(8, 8);
    QFont f = font();
    f.setPixelSize(12);
    f.setWeight(QFont::Medium);
    QFontMetrics fm(f);
    QString displayText = QString::number(value_);
    if (value_ > max_) displayText = QString("%1+").arg(max_);
    int w = fm.horizontalAdvance(displayText) + 12;
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

    QColor bg = theme::tagDarkBg(static_cast<int>(type_));

    if (dot_) {
        qreal cx = rect().x() + rect().width() / 2.0;
        qreal cy = rect().y() + rect().height() / 2.0;
        painter::DrawBackground(p, QRect(static_cast<int>(cx - 4), static_cast<int>(cy - 4), 8, 8), bg, 4.0);
        return;
    }

    painter::DrawBackground(p, rect(), bg, 8.0);

    QFont f = font();
    f.setPixelSize(12);
    f.setWeight(QFont::Medium);
    QString displayText = QString::number(value_);
    if (value_ > max_) displayText = QString("%1+").arg(max_);
    painter::DrawText(p, rect(), displayText, f, Qt::white, Qt::AlignCenter);
}
