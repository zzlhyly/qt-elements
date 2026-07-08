#include "zbutton.h"

#include <QFocusEvent>
#include <QFontMetrics>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QPainter>
#include <QPainterPath>
#include <QTimerEvent>

#include "style/style.h"
#include "painter/painter.h"
#include "theme/theme.h"

// ─── Helpers: convert ZButton enums to foundation types ─────────────

static style::ButtonVariant toStyleVariant(ZButton::ButtonVariant v) {
    return static_cast<style::ButtonVariant>(v);
}

static theme::ButtonType toThemeType(ZButton::ButtonType t) {
    return static_cast<theme::ButtonType>(t);
}

static theme::State toThemeState(statemachine::ComponentState s) {
    switch (s) {
    case statemachine::ComponentState::kHover:   return theme::kHover;
    case statemachine::ComponentState::kPressed: return theme::kPressed;
    case statemachine::ComponentState::kDisabled:return theme::kDisabled;
    default:                                     return theme::kNormal;
    }
}

// ─── Construction ────────────────────────────────────────────────────

ZButton::ZButton(QWidget* parent)
    : QAbstractButton(parent)
    , state_tracker_(new statemachine::StateTracker(this))
    , anim_manager_(new AnimationManager(this))
{
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    setCursor(Qt::PointingHandCursor);
    setFocusPolicy(Qt::StrongFocus);
}

ZButton::ZButton(const QString& text, QWidget* parent)
    : QAbstractButton(parent)
    , state_tracker_(new statemachine::StateTracker(this))
    , anim_manager_(new AnimationManager(this))
{
    setText(text);
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    setCursor(Qt::PointingHandCursor);
    setFocusPolicy(Qt::StrongFocus);
}

ZButton::~ZButton() {
    // anim_manager_ is parented to this, Qt handles cleanup
}

// ─── Public setters / getters ────────────────────────────────────────

void ZButton::setButtonType(ButtonType type)    { type_ = type; update(); }
void ZButton::setButtonSize(ButtonSize size)    { size_ = size; updateGeometry(); update(); }
void ZButton::setButtonVariant(ButtonVariant v) { variant_ = v; update(); }
void ZButton::setRound(bool r)                  { round_ = r; update(); }
void ZButton::setCircle(bool c)                 { circle_ = c; updateGeometry(); update(); }

void ZButton::setLoading(bool loading) {
    if (loading_ == loading) return;
    loading_ = loading;
    if (loading_) {
        // Create a continuous progress animation for the spinner
        loading_anim_ = anim_manager_->CreateProgressAnimation(
            this, QByteArrayLiteral("_loading_angle"),
            1000,  // 1 second per full rotation
            [this](qreal progress) {
                loading_angle_ = progress;
                update();
            });
    } else {
        if (loading_anim_.IsValid()) {
            loading_anim_.Stop();
        }
    }
    state_tracker_->SetLoading(loading_);
    state_tracker_->Update();
    update();
}

bool ZButton::isLoading() const                     { return loading_; }

ZButton::ButtonType ZButton::buttonType() const     { return type_; }
ZButton::ButtonSize ZButton::buttonSize() const     { return size_; }
ZButton::ButtonVariant ZButton::buttonVariant() const{ return variant_; }
bool ZButton::isRound() const                       { return round_; }
bool ZButton::isCircle() const                      { return circle_; }

// ─── Size helpers ────────────────────────────────────────────────────

theme::SizeSpec ZButton::sizeSpec() const {
    return theme::buttonSize(size_);
}

QSize ZButton::sizeHint() const {
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
        w += s.padH * 2;
        w = qMax(w, s.height);
    }
    return QSize(w, s.height);
}

QSize ZButton::minimumSizeHint() const {
    const theme::SizeSpec& s = sizeSpec();
    if (circle_) return QSize(s.height, s.height);
    return QSize(s.height, s.height);
}

// ─── Painting ────────────────────────────────────────────────────────

void ZButton::paintEvent(QPaintEvent*) {
    const theme::SizeSpec& s = sizeSpec();
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    // Resolve visual properties from Style system
    statemachine::ComponentState compState = state_tracker_->CurrentState();
    theme::State themeState = toThemeState(compState);
    theme::ButtonType themeType = toThemeType(type_);

    auto visuals = style::ResolveButton(themeType, themeState,
                                         toStyleVariant(variant_),
                                         round_, circle_, s);

    QRect r = rect();

    // Shadow (subtle) — only for solid variant non-circle
    if (variant_ == kSolid && !circle_ && !loading_
        && compState != statemachine::ComponentState::kDisabled) {
        painter::DrawShadow(p, r, visuals.borderRadius, 4, 2.0,
                            QColor(0, 0, 0, 20));
    }

    // Background
    painter::DrawBackground(p, r, visuals.background, visuals.borderRadius);

    // Border
    if (visuals.borderWidth > 0 && visuals.borderColor.isValid()) {
        QRectF borderRect = QRectF(r).adjusted(
            visuals.borderWidth / 2.0, visuals.borderWidth / 2.0,
            -visuals.borderWidth / 2.0, -visuals.borderWidth / 2.0);
        Qt::PenStyle penStyle = (variant_ == kDashed) ? Qt::DashLine : Qt::SolidLine;
        painter::DrawBorder(p, borderRect, visuals.borderColor,
                            static_cast<qreal>(visuals.borderWidth),
                            visuals.borderRadius, penStyle);
    }

    // Focus ring
    if (compState == statemachine::ComponentState::kFocused && !circle_) {
        painter::DrawFocusRing(p, QRectF(r), visuals.borderRadius,
                                theme::focusOutline());
    }

    // Content: loading spinner or text+icon
    if (loading_) {
        // Semi-transparent overlay to indicate loading
        painter::DrawStateOverlay(p, r, visuals.borderRadius,
                                   QColor(255, 255, 255, 76));

        int arcRadius = qMax(6, s.height / 4);
        QPen arcPen(visuals.textColor, 2);
        arcPen.setCapStyle(Qt::RoundCap);
        p.setPen(arcPen);
        p.setBrush(Qt::NoBrush);

        qreal cx = r.x() + r.width() / 2.0;
        qreal cy = r.y() + r.height() / 2.0;
        QRectF arcRect(cx - arcRadius, cy - arcRadius, arcRadius * 2, arcRadius * 2);
        p.drawArc(arcRect, static_cast<int>(loading_angle_) * 16, 300 * 16);
        return;
    }

    // Font setup
    QFont f = font();
    f.setPixelSize(s.fontSize);
    f.setWeight(QFont::Medium);

    bool hasIcon = !icon().isNull();
    bool hasText = !text().isEmpty();
    int iconSize = s.height - 8;

    if (circle_ && hasIcon) {
        // Circle: icon only, centered
        QIcon::Mode mode = !isEnabled() ? QIcon::Disabled
                         : isDown() ? QIcon::Selected
                         : (compState == statemachine::ComponentState::kHover)
                           ? QIcon::Active : QIcon::Normal;
        painter::DrawIcon(p, r, icon(), iconSize, Qt::AlignCenter, mode);
    } else {
        // Calculate total content width
        int textW = hasText ? QFontMetrics(f).horizontalAdvance(text()) : 0;
        int totalW = textW;
        if (hasIcon) totalW += iconSize + (hasText ? s.iconGap : 0);

        qreal cx = r.x() + r.width() / 2.0;
        qreal cy = r.y() + r.height() / 2.0;
        int startX = static_cast<int>(cx - totalW / 2.0);

        if (hasIcon) {
            QIcon::Mode mode = !isEnabled() ? QIcon::Disabled
                             : isDown() ? QIcon::Selected
                             : (compState == statemachine::ComponentState::kHover)
                               ? QIcon::Active : QIcon::Normal;
            QRect iconRect(startX, static_cast<int>(cy - iconSize / 2.0),
                          iconSize, iconSize);
            painter::DrawIcon(p, iconRect, icon(), iconSize, Qt::AlignCenter, mode);
            startX += iconSize + s.iconGap;
        }

        if (hasText) {
            p.setPen(visuals.textColor);
            // painter::DrawText handles elision, but we also need the exact position
            QFontMetrics fm(f);
            QString elided = fm.elidedText(text(), Qt::ElideRight, textW);
            p.setFont(f);
            painter::DrawText(p, QRect(startX, r.y(), textW, r.height()),
                              elided, f, visuals.textColor, Qt::AlignCenter);
        }
    }
}

// ─── Event handlers ──────────────────────────────────────────────────

void ZButton::enterEvent(QEvent*) {
    state_tracker_->SetHovered(true);
    state_tracker_->Update();
    update();
}

void ZButton::leaveEvent(QEvent*) {
    state_tracker_->SetHovered(false);
    state_tracker_->Update();
    update();
}

void ZButton::focusInEvent(QFocusEvent* e) {
    bool keyboardFocus = (e->reason() == Qt::TabFocusReason
                       || e->reason() == Qt::BacktabFocusReason
                       || e->reason() == Qt::ShortcutFocusReason);
    state_tracker_->SetFocused(keyboardFocus);
    state_tracker_->Update();
    QAbstractButton::focusInEvent(e);
}

void ZButton::mousePressEvent(QMouseEvent* e) {
    if (loading_) return;
    state_tracker_->SetFocused(false);  // Clear keyboard focus on mouse click
    state_tracker_->Update();
    QAbstractButton::mousePressEvent(e);
}

void ZButton::keyPressEvent(QKeyEvent* e) {
    if (loading_) return;
    if (e->key() == Qt::Key_Space || e->key() == Qt::Key_Return
        || e->key() == Qt::Key_Enter) {
        click();
        return;
    }
    QAbstractButton::keyPressEvent(e);
}

void ZButton::changeEvent(QEvent* e) {
    QAbstractButton::changeEvent(e);
    if (e->type() == QEvent::EnabledChange) {
        state_tracker_->SetEnabled(isEnabled());
        state_tracker_->Update();
    }
}
