#include "widgets/tag/ztag.h"
#include "painter/painter.h"

#include <QFontMetrics>
#include <QMouseEvent>
#include <QPainter>

ZTag::ZTag(QWidget* parent)
    : QWidget(parent)
    , close_state_(new statemachine::StateTracker(this))
{
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
}

ZTag::ZTag(const QString& text, QWidget* parent)
    : QWidget(parent)
    , text_(text)
    , close_state_(new statemachine::StateTracker(this))
{
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
}

void ZTag::setText(const QString& text)
{
    text_ = text;
    updateGeometry();
    update();
}

QString ZTag::text() const
{
    return text_;
}

void ZTag::setTagType(TagType type)  { type_ = type; update(); }
void ZTag::setEffect(TagEffect e)    { effect_ = e; update(); }
void ZTag::setTagSize(TagSize s)     { size_ = s; updateGeometry(); update(); }
void ZTag::setClosable(bool c)       { closable_ = c; update(); }
void ZTag::setRound(bool r)          { round_ = r; update(); }
void ZTag::setHit(bool h)            { hit_ = h; update(); }

ZTag::TagType ZTag::tagType() const   { return type_; }
ZTag::TagEffect ZTag::effect() const  { return effect_; }
ZTag::TagSize ZTag::tagSize() const   { return size_; }
bool ZTag::isClosable() const         { return closable_; }
bool ZTag::isRound() const            { return round_; }
bool ZTag::isHit() const              { return hit_; }

QSize ZTag::sizeHint() const
{
    const theme::SizeSpec& s = theme::tagSize(static_cast<int>(size_));
    QFont f = font();
    f.setPixelSize(s.fontSize);
    f.setWeight(QFont::Medium);
    QFontMetrics fm(f);

    int w = s.padH * 2 + fm.horizontalAdvance(text_);
    if (closable_) w += theme::tagCloseSize(static_cast<int>(size_)) + s.iconGap;
    w = qMax(w, s.height * 2);
    return QSize(w, s.height);
}

QSize ZTag::minimumSizeHint() const
{
    return QSize(0, theme::tagSize(static_cast<int>(size_)).height);
}

QRect ZTag::closeButtonRect() const
{
    if (!closable_) return QRect();
    const theme::SizeSpec& s = theme::tagSize(static_cast<int>(size_));
    int cs = theme::tagCloseSize(static_cast<int>(size_));
    int cm = s.iconGap;
    return QRect(width() - cm - cs, (height() - cs) / 2, cs, cs);
}

void ZTag::paintEvent(QPaintEvent*)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    const theme::SizeSpec& s = theme::tagSize(static_cast<int>(size_));
    style::TagVisuals visuals = style::ResolveTag(
        static_cast<int>(type_),
        static_cast<int>(effect_),
        isEnabled());

    QFont f = font();
    f.setPixelSize(s.fontSize);
    f.setWeight(QFont::Medium);

    QRect r = rect();
    qreal radius = round_ ? static_cast<qreal>(s.height) / 2.0
                          : static_cast<qreal>(s.radius);

    // Background
    painter::DrawBackground(p, r, visuals.background, radius);

    // Border
    QColor borderColor = visuals.borderColor;
    int borderWidth = s.border;
    if (hit_) {
        borderColor = theme::colorPrimary();
        borderWidth = 2;
    }
    if (borderColor.isValid() && borderColor.alpha() > 0) {
        painter::DrawBorder(p, QRectF(r), borderColor,
                            static_cast<qreal>(borderWidth), radius);
    }

    // Text
    QRect textRect = r;
    if (closable_) {
        textRect.setRight(r.right() - theme::tagCloseSize(static_cast<int>(size_))
                          - s.iconGap);
    }
    painter::DrawText(p, textRect, text_, f, visuals.textColor);

    // Close button
    if (closable_) {
        QRect cb = closeButtonRect();
        QFont cf = f;
        cf.setWeight(QFont::Normal);

        QColor closeColor = visuals.textColor;
        if (close_state_->CurrentState() == statemachine::ComponentState::kHover
            || close_state_->CurrentState() == statemachine::ComponentState::kPressed) {
            closeColor = theme::colorPrimary();
        }

        painter::DrawText(p, cb, QString(theme::icon::close()), cf, closeColor);
    }
}

void ZTag::mousePressEvent(QMouseEvent* e)
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

void ZTag::mouseReleaseEvent(QMouseEvent* e)
{
    if (closable_
        && close_state_->CurrentState() == statemachine::ComponentState::kPressed
        && closeButtonRect().contains(e->pos())) {
        close_state_->SetPressed(false);
        close_state_->SetHovered(false);
        close_state_->Update();
        update();
        emit closed();
        e->accept();
        return;
    }
    close_state_->SetPressed(false);
    close_state_->Update();
    update();
    QWidget::mouseReleaseEvent(e);
}

void ZTag::mouseMoveEvent(QMouseEvent* e)
{
    if (closable_) {
        close_state_->SetHovered(closeButtonRect().contains(e->pos()));
        if (close_state_->Update()) {
            update();
        }
    }
    QWidget::mouseMoveEvent(e);
}
