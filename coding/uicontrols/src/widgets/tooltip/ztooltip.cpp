#include "ztooltip.h"
#include "popup/zpopup.h"
#include "painter/painter.h"

#include <QApplication>
#include <QEvent>
#include <QFontMetrics>
#include <QGraphicsOpacityEffect>
#include <QPainter>
#include <QPainterPath>
#include <QPropertyAnimation>
#include <QTimer>

namespace {

class TooltipContent : public QWidget {
public:
    TooltipContent(const QString& text, ZPopup::Placement placement,
                   ZTooltip::Effect effect, QWidget* parent = nullptr)
        : QWidget(parent), text_(text), placement_(placement), effect_(effect)
    {
        QFont f = font();
        f.setPixelSize(12);
        setFont(f);
        QFontMetrics fm(f);
        int tw = fm.horizontalAdvance(text_) + 8;
        int w = qMin(tw, 260);
        if (tw > 260) wordWrap_ = true;
        bool horiz = (placement_ == ZPopup::kTop || placement_ == ZPopup::kBottom);
        int th;
        if (wordWrap_ && horiz) th = fm.height() * 2 + 14 + 5;
        else if (horiz) th = fm.height() + 14 + 5;
        else th = fm.height() + 14;
        if (!horiz) { w = tw + 5; w = qMin(w, 265); if (tw + 5 > 265) wordWrap_ = true; }
        setFixedSize(w, th);
    }

protected:
    void paintEvent(QPaintEvent*) override {
        QPainter p(this);
        p.setRenderHint(QPainter::Antialiasing);

        bool isDark = (effect_ == ZTooltip::kDark);
        QColor bgColor = isDark ? QColor(0x30, 0x31, 0x33) : Qt::white;
        QColor textColor = isDark ? Qt::white : QColor(0x30, 0x31, 0x33);
        QColor borderColor = isDark ? QColor(0x30, 0x31, 0x33) : QColor(0xe4, 0xe7, 0xed);

        qreal radius = 4.0;
        bool horiz = (placement_ == ZPopup::kTop || placement_ == ZPopup::kBottom);

        QRect body;
        if (horiz) {
            body = (placement_ == ZPopup::kTop) ? rect().adjusted(0, 0, 0, -5) : rect().adjusted(0, 5, 0, 0);
        } else {
            body = (placement_ == ZPopup::kLeft) ? rect().adjusted(0, 0, -5, 0) : rect().adjusted(5, 0, 0, 0);
        }

        // Body background + border
        painter::DrawBackground(p, body, bgColor, radius);
        if (!isDark) {
            painter::DrawBorder(p, QRectF(body), borderColor, 1.0, radius);
        }

        // Arrow
        QPainterPath arrow;
        if (horiz) {
            int ax = width() / 2;
            if (placement_ == ZPopup::kTop) {
                int ay = height() - 1;
                arrow.moveTo(ax - 4, ay - 5); arrow.lineTo(ax, ay); arrow.lineTo(ax + 4, ay - 5);
            } else {
                arrow.moveTo(ax - 4, 5); arrow.lineTo(ax, 0); arrow.lineTo(ax + 4, 5);
            }
        } else {
            int ay = height() / 2;
            if (placement_ == ZPopup::kLeft) {
                int ax = width() - 1;
                arrow.moveTo(ax - 5, ay - 4); arrow.lineTo(ax, ay); arrow.lineTo(ax - 5, ay + 4);
            } else {
                arrow.moveTo(5, ay - 4); arrow.lineTo(0, ay); arrow.lineTo(5, ay + 4);
            }
        }
        arrow.closeSubpath();
        p.setPen(Qt::NoPen);
        p.setBrush(bgColor);
        p.drawPath(arrow);

        // Arrow border (light theme only)
        if (!isDark && horiz) {
            QPainterPath arrowBorder;
            int ax = width() / 2;
            if (placement_ == ZPopup::kTop) {
                int ay = height() - 1;
                arrowBorder.moveTo(ax - 4, ay - 5); arrowBorder.lineTo(ax, ay + 1);
            } else {
                arrowBorder.moveTo(ax - 4, 5); arrowBorder.lineTo(ax, -1);
            }
            p.setPen(QPen(borderColor, 1));
            p.setBrush(Qt::NoBrush);
            p.drawPath(arrowBorder);
        }

        QFont f = font();
        f.setPixelSize(12);
        if (wordWrap_)
            p.drawText(body.adjusted(4, 7, -4, -7), Qt::AlignHCenter | Qt::AlignVCenter | Qt::TextWordWrap, text_);
        else
            painter::DrawText(p, body, text_, f, textColor, Qt::AlignCenter);
    }

private:
    QString text_;
    ZPopup::Placement placement_;
    ZTooltip::Effect effect_ = ZTooltip::kDark;
    bool wordWrap_ = false;
};

} // namespace

// ─── ZTooltip ──────────────────────────────────────────────────────

ZTooltip::ZTooltip(QObject* parent)
    : QObject(parent)
{
    show_timer_ = new QTimer(this);
    show_timer_->setSingleShot(true);
    connect(show_timer_, &QTimer::timeout, this, &ZTooltip::onHoverTimeout);

    hide_timer_ = new QTimer(this);
    hide_timer_->setSingleShot(true);
    connect(hide_timer_, &QTimer::timeout, this, &ZTooltip::hidePopup);
}

ZTooltip::~ZTooltip() {
    if (popup_) { popup_->close(); popup_->deleteLater(); }
}

void ZTooltip::setTarget(QWidget* widget) {
    if (target_) target_->removeEventFilter(this);
    target_ = widget;
    if (target_) target_->installEventFilter(this);
}

void ZTooltip::setText(const QString& text) { text_ = text; }
void ZTooltip::setPlacement(ZPopup::Placement p) { placement_ = p; }
void ZTooltip::setEffect(Effect e) { effect_ = e; }
void ZTooltip::setTrigger(Trigger t) { trigger_ = t; }
void ZTooltip::setShowDelay(int ms) { showDelay_ = qMax(0, ms); }
void ZTooltip::setHideDelay(int ms) { hideDelay_ = qMax(0, ms); }

void ZTooltip::show() {
    if (trigger_ != kManual) return;
    if (popup_ || !target_ || text_.isEmpty()) return;
    showPopup();
}

void ZTooltip::hide() {
    if (trigger_ != kManual) return;
    hidePopup();
}

void ZTooltip::onHoverTimeout() {
    if (popup_ || !target_ || text_.isEmpty()) return;
    showPopup();
}

void ZTooltip::showPopup() {
    auto* content = new TooltipContent(text_, placement_, effect_);
    popup_ = ZPopup::createPopup(target_, content, placement_);
    popup_->setAttribute(Qt::WA_DeleteOnClose, true);
    connect(popup_, &ZPopup::popupClosed, this, [this]() { popup_ = nullptr; });

    // Fade-in animation
    auto* effect = new QGraphicsOpacityEffect(popup_);
    effect->setOpacity(0.0);
    popup_->setGraphicsEffect(effect);
    auto* anim = new QPropertyAnimation(effect, "opacity", this);
    anim->setStartValue(0.0);
    anim->setEndValue(1.0);
    anim->setDuration(200);
    anim->setEasingCurve(QEasingCurve::OutCubic);
    anim->start(QAbstractAnimation::DeleteWhenStopped);
}

void ZTooltip::hidePopup() {
    if (!popup_) return;

    auto* effect = new QGraphicsOpacityEffect(popup_);
    effect->setOpacity(1.0);
    popup_->setGraphicsEffect(effect);
    auto* anim = new QPropertyAnimation(effect, "opacity", this);
    anim->setStartValue(1.0);
    anim->setEndValue(0.0);
    anim->setDuration(150);
    anim->setEasingCurve(QEasingCurve::InCubic);
    connect(anim, &QPropertyAnimation::finished, this, [this]() {
        if (popup_) { popup_->close(); popup_ = nullptr; }
    });
    anim->start(QAbstractAnimation::DeleteWhenStopped);
}

void ZTooltip::scheduleShow() {
    if (trigger_ != kHover) return;
    hide_timer_->stop();
    show_timer_->start(showDelay_);
}

void ZTooltip::scheduleHide() {
    if (trigger_ != kHover) return;
    show_timer_->stop();
    if (hideDelay_ > 0) {
        hide_timer_->start(hideDelay_);
    } else {
        hidePopup();
    }
}

bool ZTooltip::eventFilter(QObject* obj, QEvent* event) {
    if (obj == target_ && trigger_ == kHover) {
        if (event->type() == QEvent::Enter) {
            scheduleShow();
        } else if (event->type() == QEvent::Leave) {
            scheduleHide();
        }
    }
    return QObject::eventFilter(obj, event);
}

void ZTooltip::showText(QWidget* target, const QString& text, Effect effect, int duration) {
    if (!target || text.isEmpty()) return;
    auto* content = new TooltipContent(text, ZPopup::kTop, effect);
    auto* popup = ZPopup::createPopup(target, content, ZPopup::kTop);
    popup->setAttribute(Qt::WA_DeleteOnClose, true);

    // Fade-in
    auto* effectObj = new QGraphicsOpacityEffect(popup);
    effectObj->setOpacity(0.0);
    popup->setGraphicsEffect(effectObj);
    auto* anim = new QPropertyAnimation(effectObj, "opacity", popup);
    anim->setStartValue(0.0);
    anim->setEndValue(1.0);
    anim->setDuration(200);
    anim->start(QAbstractAnimation::DeleteWhenStopped);

    QTimer::singleShot(duration - 200, popup, [popup]() {
        // Fade-out before close
        auto* fadeOut = new QGraphicsOpacityEffect(popup);
        fadeOut->setOpacity(1.0);
        popup->setGraphicsEffect(fadeOut);
        auto* a = new QPropertyAnimation(fadeOut, "opacity", popup);
        a->setStartValue(1.0);
        a->setEndValue(0.0);
        a->setDuration(150);
        connect(a, &QPropertyAnimation::finished, popup, &QWidget::close);
        a->start(QAbstractAnimation::DeleteWhenStopped);
    });
}

void ZTooltip::install(QWidget* target, const QString& text,
                        ZPopup::Placement placement, Effect effect) {
    auto* tooltip = new ZTooltip(target);
    tooltip->setTarget(target);
    tooltip->setText(text);
    tooltip->setPlacement(placement);
    tooltip->setEffect(effect);
}
