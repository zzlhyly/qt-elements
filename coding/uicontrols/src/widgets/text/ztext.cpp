#include "ztext.h"
#include "theme/theme.h"
#include "painter/painter.h"

#include <QFontMetrics>
#include <QPainter>

ZText::ZText(QWidget* parent)
    : QWidget(parent)
{
}

ZText::ZText(const QString& text, QWidget* parent)
    : QWidget(parent)
    , text_(text)
{
}

void ZText::setText(const QString& text)      { text_ = text; updateGeometry(); update(); }
void ZText::setTextType(TextType type)         { type_ = type; update(); }
void ZText::setTextSize(TextSize size)         { size_ = size; updateGeometry(); update(); }
void ZText::setTruncated(bool truncated)       { truncated_ = truncated; update(); }

QString ZText::text() const                   { return text_; }
ZText::TextType ZText::textType() const       { return type_; }
ZText::TextSize ZText::textSize() const       { return size_; }
bool ZText::isTruncated() const               { return truncated_; }

static int resolveFontSize(int size) {
    static const int sizes[] = {16, 14, 12};
    return sizes[size];
}

static QColor resolveColor(int type) {
    if (type == ZText::kDefault) return theme::textRegular();
    return theme::tagTextColor(type - 1);
}

QSize ZText::sizeHint() const
{
    QFont f = font();
    f.setPixelSize(resolveFontSize(size_));
    QFontMetrics fm(f);
    int w = fm.horizontalAdvance(text_);
    return QSize(qMax(w, 16), fm.height());
}

void ZText::paintEvent(QPaintEvent*)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    QFont f = font();
    f.setPixelSize(resolveFontSize(size_));
    f.setWeight(QFont::Normal);

    QString displayText = text_;
    if (truncated_) {
        QFontMetrics fm(f);
        if (fm.horizontalAdvance(text_) > width()) {
            displayText = fm.elidedText(text_, Qt::ElideRight, width());
        }
    }

    QColor color = resolveColor(type_);
    painter::DrawText(p, rect(), displayText, f, color, Qt::AlignLeft | Qt::AlignVCenter);
}
