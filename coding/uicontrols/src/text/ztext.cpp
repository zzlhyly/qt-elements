#include "ztext.h"
#include "theme/theme.h"

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

void ZText::setText(const QString& text)
{
    text_ = text;
    updateGeometry();
    update();
}

void ZText::setTextType(TextType type)
{
    type_ = type;
    update();
}

void ZText::setTextSize(TextSize size)
{
    size_ = size;
    updateGeometry();
    update();
}

void ZText::setTruncated(bool truncated)
{
    truncated_ = truncated;
    update();
}

QString ZText::text() const          { return text_; }
ZText::TextType ZText::textType() const { return type_; }
ZText::TextSize ZText::textSize() const { return size_; }
bool ZText::isTruncated() const      { return truncated_; }

QColor ZText::resolveColor() const
{
    if (type_ == kDefault) return theme::textRegular();
    // tagTextColor index: 0=Primary,1=Success,2=Info,3=Warning,4=Danger
    return theme::tagTextColor(static_cast<int>(type_) - 1);
}

int ZText::resolveFontSize() const
{
    static const int sizes[] = {16, 14, 12};  // kLarge=0, kMedium=1, kSmall=2
    return sizes[size_];
}

QSize ZText::sizeHint() const
{
    QFont f = font();
    f.setPixelSize(resolveFontSize());
    f.setWeight(QFont::Normal);
    QFontMetrics fm(f);
    int w = fm.horizontalAdvance(text_);
    return QSize(qMax(w, 16), fm.height());
}

void ZText::paintEvent(QPaintEvent*)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    QFont f = font();
    f.setPixelSize(resolveFontSize());
    f.setWeight(QFont::Normal);
    p.setFont(f);

    QFontMetrics fm(f);
    p.setPen(resolveColor());

    QString displayText = text_;
    if (truncated_ && fm.horizontalAdvance(text_) > width()) {
        displayText = fm.elidedText(text_, Qt::ElideRight, width());
    }

    p.drawText(rect(), Qt::AlignLeft | Qt::AlignVCenter, displayText);
}
