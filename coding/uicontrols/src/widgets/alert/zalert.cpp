#include "widgets/alert/zalert.h"

#include <QFontMetrics>
#include <QMouseEvent>
#include <QPainter>
#include <QPainterPath>

#include "painter/painter.h"
#include "theme/theme.h"

// ─── Construction ─────────────────────────────────────────────────

ZAlert::ZAlert(QWidget* parent)
    : QWidget(parent)
{
    Init();
}

ZAlert::ZAlert(const QString& title, AlertType type, QWidget* parent)
    : QWidget(parent)
    , title_(title)
    , type_(type)
{
    Init();
}

void ZAlert::Init()
{
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    setMinimumWidth(200);
    setMouseTracking(true);
    close_state_ = new statemachine::StateTracker(this);
}

// ─── Setters ──────────────────────────────────────────────────────

void ZAlert::setTitle(const QString& t) { title_ = t; updateGeometry(); update(); }
void ZAlert::setType(AlertType type)     { type_ = type; update(); }
void ZAlert::setEffect(AlertEffect e)    { effect_ = e; update(); }
void ZAlert::setClosable(bool c)         { closable_ = c; update(); }
void ZAlert::setShowIcon(bool s)         { showIcon_ = s; update(); }
void ZAlert::setCenter(bool c)           { center_ = c; update(); }

// ─── Getters ─────────────────────────────────────────────────────

QString ZAlert::title() const          { return title_; }
ZAlert::AlertType ZAlert::type() const { return type_; }
ZAlert::AlertEffect ZAlert::effect() const { return effect_; }
bool ZAlert::isClosable() const        { return closable_; }
bool ZAlert::isShowIcon() const        { return showIcon_; }
bool ZAlert::isCenter() const          { return center_; }

// ─── Close button rect ───────────────────────────────────────────

QRect ZAlert::closeButtonRect() const
{
    if (!closable_) return QRect();
    return QRect(width() - 28, 0, 28, height());
}

// ─── Size hints ──────────────────────────────────────────────────

QSize ZAlert::sizeHint() const
{
    QFont f = font();
    f.setPixelSize(13);
    f.setWeight(QFont::Medium);
    QFontMetrics fm(f);

    int w = 32;  // horizontal padding * 2
    if (showIcon_) w += 16 + 8;  // icon + gap
    w += fm.horizontalAdvance(title_);
    if (closable_) w += 14 + 8;  // close button + gap
    return QSize(qMax(w, 300), 36);
}

QSize ZAlert::minimumSizeHint() const
{
    return QSize(200, 36);
}

// ─── Paint ───────────────────────────────────────────────────────

void ZAlert::paintEvent(QPaintEvent*)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    QRect r = rect();
    auto visuals = style::ResolveAlert(static_cast<int>(type_),
                                       static_cast<int>(effect_));

    // Background
    painter::DrawBackground(p, r, visuals.background, 4.0);

    // Border
    QRectF rf = QRectF(r).adjusted(0.5, 0.5, -0.5, -0.5);
    painter::DrawBorder(p, rf, visuals.borderColor, 1.0, 4.0);

    // Title font
    QFont titleFont = font();
    titleFont.setPixelSize(13);
    titleFont.setWeight(QFont::Medium);
    p.setFont(titleFont);
    QFontMetrics fm(titleFont);

    int cx = 16;  // left padding

    // Icon
    if (showIcon_) {
        QRect iconRect(cx, (height() - 16) / 2, 16, 16);
        QFont iconFont = font();
        iconFont.setPixelSize(14);
        iconFont.setWeight(QFont::Bold);
        p.setFont(iconFont);
        p.setPen(visuals.textColor);
        p.drawText(iconRect, Qt::AlignCenter, QString(visuals.iconGlyph));
        p.setFont(titleFont);  // restore title font
        cx += 16 + 8;
    }

    // Title text
    int titleRight = width() - 16;
    if (closable_) titleRight -= 14 + 8;

    QRect titleRect(cx, 0, titleRight - cx, height());
    int flags = Qt::AlignVCenter | (center_ ? Qt::AlignCenter : Qt::AlignLeft);
    p.setPen(visuals.textColor);
    p.setFont(titleFont);
    QString displayText = fm.elidedText(title_, Qt::ElideRight,
                                        titleRect.width());
    p.drawText(titleRect, flags, displayText);

    // Close button
    if (closable_) {
        QRect cb = closeButtonRect();
        QColor closeColor = visuals.textColor;
        if (close_state_->CurrentState() ==
            statemachine::ComponentState::kHover) {
            closeColor = theme::colorPrimary();
        }
        QFont cf = font();
        cf.setPixelSize(12);
        cf.setWeight(QFont::Normal);
        p.setFont(cf);
        p.setPen(closeColor);
        p.drawText(cb, Qt::AlignCenter, QString(theme::icon::close()));
    }
}

// ─── Mouse events ────────────────────────────────────────────────

void ZAlert::mouseMoveEvent(QMouseEvent* e)
{
    if (closable_) {
        bool hovered = closeButtonRect().contains(e->pos());
        close_state_->SetHovered(hovered);
        if (close_state_->Update()) {
            update();
        }
    }
    QWidget::mouseMoveEvent(e);
}

void ZAlert::mousePressEvent(QMouseEvent* e)
{
    if (closable_ && closeButtonRect().contains(e->pos())) {
        close_state_->SetPressed(true);
        close_state_->Update();
        update();
        e->accept();
        return;
    }
    QWidget::mousePressEvent(e);
}

void ZAlert::mouseReleaseEvent(QMouseEvent* e)
{
    if (closable_ && closeButtonRect().contains(e->pos())) {
        close_state_->SetPressed(false);
        close_state_->SetHovered(false);
        close_state_->Update();
        emit closed();
        hide();
        update();
        e->accept();
        return;
    }
    close_state_->SetPressed(false);
    close_state_->Update();
    update();
    QWidget::mouseReleaseEvent(e);
}
