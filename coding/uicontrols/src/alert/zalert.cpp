#include "zalert.h"
#include "theme/theme.h"

#include <QFontMetrics>
#include <QMouseEvent>
#include <QPainter>
#include <QPainterPath>

ZAlert::ZAlert(QWidget* parent)
    : QWidget(parent)
{
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    setMinimumWidth(200);
}

ZAlert::ZAlert(const QString& title, AlertType type, QWidget* parent)
    : QWidget(parent)
    , title_(title)
    , type_(type)
{
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    setMinimumWidth(200);
}

void ZAlert::setTitle(const QString& t) { title_ = t; updateGeometry(); update(); }
void ZAlert::setType(AlertType type)    { type_ = type; update(); }
void ZAlert::setEffect(AlertEffect e)   { effect_ = e; update(); }
void ZAlert::setClosable(bool c)        { closable_ = c; update(); }
void ZAlert::setShowIcon(bool s)        { showIcon_ = s; update(); }
void ZAlert::setCenter(bool c)          { center_ = c; update(); }

QString ZAlert::title() const          { return title_; }
ZAlert::AlertType ZAlert::type() const { return type_; }
ZAlert::AlertEffect ZAlert::effect() const { return effect_; }
bool ZAlert::isClosable() const        { return closable_; }
bool ZAlert::isShowIcon() const        { return showIcon_; }
bool ZAlert::isCenter() const          { return center_; }

// ─── Color helpers ─────────────────────────────────────────────────

QColor ZAlert::bgColor() const
{
    if (effect_ == kDark) {
        switch (type_) {
        case kSuccess: return theme::colorSuccess();
        case kWarning: return theme::colorWarning();
        case kError:   return theme::colorDanger();
        default:       return theme::colorInfo();
        }
    }
    // Light effect
    switch (type_) {
    case kSuccess: return QColor(0xf0, 0xf9, 0xeb);
    case kWarning: return QColor(0xfd, 0xf6, 0xec);
    case kError:   return QColor(0xfe, 0xf0, 0xf0);
    default:       return QColor(0xf4, 0xf4, 0xf5);
    }
}

QColor ZAlert::borderColor() const
{
    if (effect_ == kDark) {
        return bgColor();
    }
    switch (type_) {
    case kSuccess: return QColor(0xe1, 0xf3, 0xd8);
    case kWarning: return QColor(0xfa, 0xec, 0xd8);
    case kError:   return QColor(0xfd, 0xe2, 0xe2);
    default:       return QColor(0xe9, 0xe9, 0xeb);
    }
}

QColor ZAlert::textColor() const
{
    if (effect_ == kDark) return Qt::white;
    switch (type_) {
    case kSuccess: return theme::colorSuccess();
    case kWarning: return theme::colorWarning();
    case kError:   return theme::colorDanger();
    default:       return theme::colorInfo();
    }
}

QChar ZAlert::iconGlyph() const
{
    switch (type_) {
    case kSuccess: return theme::icon::success();
    case kWarning: return theme::icon::warning();
    case kError:   return theme::icon::error();
    default:       return theme::icon::info();
    }
}

QRect ZAlert::closeButtonRect() const
{
    if (!closable_) return QRect();
    int sz = 14;
    int x = width() - 16 - sz / 2;
    int y = (height() - sz) / 2;
    return QRect(x, y, sz, sz);
}

// ─── Size hints ────────────────────────────────────────────────────

QSize ZAlert::sizeHint() const
{
    QFont f = font();
    f.setPixelSize(13);
    f.setWeight(effect_ == kLight ? QFont::Medium : QFont::Normal);
    QFontMetrics fm(f);

    int w = 32;  // horizontal padding * 2
    if (showIcon_) w += 16 + 8;  // icon + gap
    w += fm.horizontalAdvance(title_);
    if (closable_) w += 14 + 8;  // close button + gap
    return QSize(qMax(w, 200), 38);
}

QSize ZAlert::minimumSizeHint() const
{
    return QSize(200, 38);
}

// ─── Paint ─────────────────────────────────────────────────────────

void ZAlert::paintEvent(QPaintEvent*)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    QRect r = rect();
    qreal radius = theme::borderRadiusBase();  // 4px
    QColor bg = bgColor();
    QColor border = borderColor();

    // Background + border
    QPainterPath path;
    path.addRoundedRect(QRectF(r).adjusted(0.5, 0.5, -0.5, -0.5), radius, radius);
    p.setPen(QPen(border, 1));
    p.setBrush(bg);
    p.drawPath(path);

    // Font for title
    QFont f = font();
    f.setPixelSize(13);
    f.setWeight(effect_ == kLight ? QFont::Medium : QFont::Normal);
    p.setFont(f);
    QFontMetrics fm(f);

    QColor tc = textColor();
    int cx = 16;  // left padding

    // Icon
    if (showIcon_) {
        QRect iconRect(cx, (height() - 16) / 2, 16, 16);
        QFont iconFont = font();
        iconFont.setPixelSize(14);
        iconFont.setWeight(QFont::Bold);
        p.setFont(iconFont);
        p.setPen(tc);
        p.drawText(iconRect, Qt::AlignCenter, QString(iconGlyph()));
        p.setFont(f);  // restore title font
        cx += 16 + 8;
    }

    // Title text
    int titleRight = width() - 16;
    if (closable_) titleRight -= 14 + 8;

    QRect titleRect(cx, 0, titleRight - cx, height());
    int flags = Qt::AlignVCenter | (center_ ? Qt::AlignCenter : Qt::AlignLeft);
    p.setPen(tc);
    QString displayText = fm.elidedText(title_, Qt::ElideRight, titleRect.width());
    p.drawText(titleRect, flags, displayText);

    // Close button
    if (closable_) {
        QRect cb = closeButtonRect();
        QColor closeColor = tc;
        if (close_pressed_) {
            closeColor = tc.darker(120);
        }
        QFont cf = font();
        cf.setPixelSize(12);
        cf.setWeight(QFont::Normal);
        p.setFont(cf);
        p.setPen(closeColor);
        p.drawText(cb, Qt::AlignCenter, QString(theme::icon::close()));
    }
}

// ─── Mouse events ──────────────────────────────────────────────────

void ZAlert::mousePressEvent(QMouseEvent* e)
{
    if (closable_ && closeButtonRect().contains(e->pos())) {
        close_pressed_ = true;
        update();
        e->accept();
        return;
    }
    QWidget::mousePressEvent(e);
}

void ZAlert::mouseMoveEvent(QMouseEvent* e)
{
    if (closable_) {
        bool was = close_hovered_;
        close_hovered_ = closeButtonRect().contains(e->pos());
        if (was != close_hovered_) update();
    }
    QWidget::mouseMoveEvent(e);
}

void ZAlert::mouseReleaseEvent(QMouseEvent* e)
{
    if (close_pressed_ && closable_ && closeButtonRect().contains(e->pos())) {
        close_pressed_ = false;
        close_hovered_ = false;
        emit closed();
        hide();
        update();
        e->accept();
        return;
    }
    close_pressed_ = false;
    update();
    QWidget::mouseReleaseEvent(e);
}
