#include "zbutton.h"
#include "theme/theme.h"

#include <QFocusEvent>
#include <QFontMetrics>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QPainter>
#include <QPainterPath>
#include <QTimerEvent>

ZButton::ZButton(QWidget* parent)
    : QAbstractButton(parent)
{
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    setCursor(Qt::PointingHandCursor);
    setFocusPolicy(Qt::StrongFocus);
}

ZButton::ZButton(const QString& text, QWidget* parent)
    : QAbstractButton(parent)
{
    setText(text);
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    setCursor(Qt::PointingHandCursor);
    setFocusPolicy(Qt::StrongFocus);
}

void ZButton::setButtonType(ButtonType type)   { type_ = type; update(); }
void ZButton::setButtonSize(ButtonSize size)   { size_ = size; updateGeometry(); update(); }
void ZButton::setButtonVariant(ButtonVariant v) { variant_ = v; update(); }
void ZButton::setRound(bool r)                 { round_ = r; update(); }
void ZButton::setCircle(bool c)                { circle_ = c; updateGeometry(); update(); }
void ZButton::setLoading(bool loading)
{
    if (loading_ == loading) return;
    loading_ = loading;
    if (loading_) {
        loading_angle_ = 0;
        loading_timer_id_ = startTimer(50);
    } else {
        if (loading_timer_id_) {
            killTimer(loading_timer_id_);
            loading_timer_id_ = 0;
        }
    }
    update();
}
bool ZButton::isLoading() const                      { return loading_; }

void ZButton::timerEvent(QTimerEvent* e)
{
    if (e->timerId() == loading_timer_id_) {
        loading_angle_ = (loading_angle_ + 30) % 360;
        update();
        return;
    }
    QWidget::timerEvent(e);
}

ZButton::ButtonType ZButton::buttonType() const     { return type_; }
ZButton::ButtonSize ZButton::buttonSize() const      { return size_; }
ZButton::ButtonVariant ZButton::buttonVariant() const { return variant_; }
bool ZButton::isRound() const                        { return round_; }
bool ZButton::isCircle() const                       { return circle_; }

theme::SizeSpec ZButton::sizeSpec() const
{
    return theme::buttonSize(size_);
}

qreal ZButton::borderRadius() const
{
    if (circle_) return height() / 2.0;
    if (round_) return 20.0;
    return sizeSpec().radius;
}

QColor ZButton::bgColor() const
{
    theme::State si = !isEnabled() ? theme::kDisabled : isDown() ? theme::kPressed : hovered_ ? theme::kHover : theme::kNormal;
    int ti = static_cast<int>(type_);
    
    if (variant_ == kText) {
        if (!isEnabled()) return Qt::transparent;
        if (isDown()) return theme::fillColor();
        if (hovered_) return theme::fillLight();
        return Qt::transparent;
    }
    if (variant_ == kLink) return Qt::transparent;
    if (variant_ == kSolid) return theme::buttonSolidBg(ti, si);
    if (type_ == kDefault) return theme::buttonSolidBg(theme::kDefault, si);
    return theme::buttonPlainBg(ti, si);
}

QColor ZButton::textColor() const
{
    theme::State si = !isEnabled() ? theme::kDisabled : isDown() ? theme::kPressed : hovered_ ? theme::kHover : theme::kNormal;
    int ti = static_cast<int>(type_);

    if (variant_ == kText) {
        if (!isEnabled()) return theme::textDisabled();
        return theme::buttonTextColor(ti);
    }
    if (variant_ == kLink) return theme::buttonLinkText(ti, si);
    if (variant_ == kSolid) return theme::buttonSolidText(ti, si);
    if (type_ == kDefault) return theme::buttonSolidText(theme::kDefault, si);
    return theme::buttonPlainText(ti, si);
}

QColor ZButton::borderColor() const
{
    if (variant_ == kText || variant_ == kLink) return Qt::transparent;
    theme::State si = !isEnabled() ? theme::kDisabled : isDown() ? theme::kPressed : hovered_ ? theme::kHover : theme::kNormal;
    int ti = static_cast<int>(type_);

    if (variant_ == kSolid) return theme::buttonSolidBorder(ti, si);
    if (type_ == kDefault) return theme::buttonSolidBorder(theme::kDefault, si);
    return theme::buttonPlainBorder(ti, si);
}

QSize ZButton::sizeHint() const
{
    const theme::SizeSpec& s = sizeSpec();
    QFont f = font();
    f.setPixelSize(s.fontSize);
    f.setWeight(QFont::Medium);
    QFontMetrics fm(f);

    int w = 0;
    if (circle_) {
        w = s.height;
    } else {
        if (!text().isEmpty()) w += fm.horizontalAdvance(text());
        if (!icon().isNull()) {
            int iconSize = s.height - 8;
            w += iconSize;
            if (!text().isEmpty()) w += s.iconGap;
        }
        if (!circle_) w += s.padH * 2;
        w = qMax(w, s.height);
    }
    return QSize(w, s.height);
}

QSize ZButton::minimumSizeHint() const
{
    const theme::SizeSpec& s = sizeSpec();
    if (circle_) return QSize(s.height, s.height);
    return QSize(s.height, s.height);
}

void ZButton::paintEvent(QPaintEvent*)
{
    const theme::SizeSpec& s = sizeSpec();
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    // Font setup
    QFont f = font();
    f.setPixelSize(s.fontSize);
    f.setWeight(QFont::Medium);
    p.setFont(f);

    QRect r = rect();
    qreal radius = borderRadius();
    qreal bw = s.border;

    // Focus ring — drawn first so button covers inner half, like CSS outline
    if (focus_keyboard_ && !circle_) {
        QPainterPath focusPath;
        focusPath.addRoundedRect(QRectF(r).adjusted(-1, -1, 1, 1), radius + 1, radius + 1);
        p.setPen(QPen(QColor(0xa0, 0xcf, 0xff), 2));
        p.setBrush(Qt::NoBrush);
        p.drawPath(focusPath);
    }

    // Background + border
    QPainterPath path;
    path.addRoundedRect(QRectF(r).adjusted(bw/2, bw/2, -bw/2, -bw/2), radius, radius);

    QColor bg = bgColor();
    QColor bc = borderColor();

    if (variant_ == kText || variant_ == kLink) {
        // Text/Link variant: fill only, no border
        p.fillPath(path, bg);
    } else {
        QPen pen(bc, bw);
        if (variant_ == kDashed) pen.setStyle(Qt::DashLine);
        p.setPen(pen);
        p.setBrush(bg);
        p.drawPath(path);
    }

    // Content
    QColor tc = textColor();

    if (loading_) {
        // Semi-transparent white overlay
        p.fillRect(r, QColor(255, 255, 255, 76));

        // Spinning arc — use floating-point center for pixel-perfect centering
        int arcRadius = qMax(6, s.height / 4);
        QPen arcPen(tc, 2);
        arcPen.setCapStyle(Qt::RoundCap);
        p.setPen(arcPen);
        p.setBrush(Qt::NoBrush);

        qreal cx = r.x() + r.width() / 2.0;
        qreal cy = r.y() + r.height() / 2.0;
        QRectF arcRect(cx - arcRadius, cy - arcRadius, arcRadius * 2, arcRadius * 2);
        p.drawArc(arcRect, loading_angle_ * 16, 300 * 16);

        p.setPen(Qt::NoPen);
        return;
    }

    p.setPen(tc);

    bool hasIcon = !icon().isNull();
    bool hasText = !text().isEmpty();
    int iconSize = s.height - 8;

    if (circle_ && hasIcon) {
        // Circle: icon only, centered
        QIcon::Mode mode = !isEnabled() ? QIcon::Disabled : isDown() ? QIcon::Selected : hovered_ ? QIcon::Active : QIcon::Normal;
        qreal cx = r.x() + r.width() / 2.0;
        qreal cy = r.y() + r.height() / 2.0;
        icon().paint(&p, static_cast<int>(cx - iconSize / 2.0),
                     static_cast<int>(cy - iconSize / 2.0),
                     iconSize, iconSize, Qt::AlignCenter, mode);
    } else {
        // Calculate total content width
        int textW = hasText ? QFontMetrics(f).horizontalAdvance(text()) : 0;
        int totalW = textW;
        if (hasIcon) totalW += iconSize + (hasText ? s.iconGap : 0);

        qreal cx = r.x() + r.width() / 2.0;
        qreal cy = r.y() + r.height() / 2.0;
        int startX = static_cast<int>(cx - totalW / 2.0);

        if (hasIcon) {
            QIcon::Mode mode = !isEnabled() ? QIcon::Disabled : isDown() ? QIcon::Selected : hovered_ ? QIcon::Active : QIcon::Normal;
            icon().paint(&p, startX, static_cast<int>(cy - iconSize / 2.0), iconSize, iconSize, Qt::AlignCenter, mode);
            startX += iconSize + s.iconGap;
        }

        if (hasText) {
            QFontMetrics fm(f);
            QString elided = fm.elidedText(text(), Qt::ElideRight, textW);
            p.drawText(startX, static_cast<int>(cy - fm.height() / 2.0), textW, fm.height(), Qt::AlignCenter, elided);
        }
    }
}

void ZButton::enterEvent(QEvent*)
{
    hovered_ = true;
    update();
}

void ZButton::leaveEvent(QEvent*)
{
    hovered_ = false;
    update();
}

void ZButton::focusInEvent(QFocusEvent* e)
{
    focus_keyboard_ = (e->reason() == Qt::TabFocusReason
                    || e->reason() == Qt::BacktabFocusReason
                    || e->reason() == Qt::ShortcutFocusReason);
    QAbstractButton::focusInEvent(e);
}

void ZButton::mousePressEvent(QMouseEvent* e)
{
    if (loading_) return;
    focus_keyboard_ = false;
    QAbstractButton::mousePressEvent(e);
}

void ZButton::keyPressEvent(QKeyEvent* e)
{
    if (loading_) return;
    if (e->key() == Qt::Key_Space || e->key() == Qt::Key_Return || e->key() == Qt::Key_Enter) {
        click();
        return;
    }
    QAbstractButton::keyPressEvent(e);
}

void ZButton::changeEvent(QEvent*)
{
    update();
}
