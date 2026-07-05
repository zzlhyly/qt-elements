#include "ztooltip.h"
#include "popup/zpopup.h"

#include <QApplication>
#include <QEvent>
#include <QLabel>
#include <QPalette>
#include <QTimer>
#include <QVBoxLayout>

ZTooltip::ZTooltip(QObject* parent)
    : QObject(parent)
{
    timer_ = new QTimer(this);
    timer_->setSingleShot(true);
    timer_->setInterval(500);
    connect(timer_, &QTimer::timeout, this, &ZTooltip::onHoverTimeout);
}

ZTooltip::~ZTooltip()
{
    if (popup_) {
        popup_->close();
        popup_->deleteLater();
        popup_ = nullptr;
    }
}

void ZTooltip::setTarget(QWidget* widget)
{
    if (target_) target_->removeEventFilter(this);
    target_ = widget;
    if (target_) target_->installEventFilter(this);
}

void ZTooltip::setText(const QString& text)
{
    text_ = text;
}

void ZTooltip::showPopup()
{
    if (popup_) return;
    if (!target_ || text_.isEmpty()) return;

    // Build tooltip content label
    auto* label = new QLabel(text_);
    QPalette pal;
    pal.setColor(QPalette::Window, QColor(0x30, 0x31, 0x33));
    pal.setColor(QPalette::WindowText, Qt::white);
    label->setPalette(pal);
    label->setAutoFillBackground(true);
    label->setMargin(8);
    QFont f = label->font();
    f.setPixelSize(12);
    label->setFont(f);
    label->setWordWrap(true);
    label->setMaximumWidth(200);

    // Create popup
    popup_ = ZPopup::createPopup(target_, label, ZPopup::kTop);
    popup_->setAttribute(Qt::WA_DeleteOnClose, true);
    connect(popup_, &ZPopup::popupClosed, this, [this]() {
        popup_ = nullptr;
    });
}

void ZTooltip::onHoverTimeout()
{
    showPopup();
}

bool ZTooltip::eventFilter(QObject* obj, QEvent* event)
{
    if (obj == target_) {
        if (event->type() == QEvent::Enter) {
            timer_->start();
        } else if (event->type() == QEvent::Leave) {
            timer_->stop();
            if (popup_) {
                popup_->close();
                popup_ = nullptr;
            }
        } else if (event->type() == QEvent::MouseMove) {
            // Reset timer on mouse move within the widget
            if (timer_->isActive()) timer_->start();
        }
    }
    return QObject::eventFilter(obj, event);
}

// ─── Static convenience methods ────────────────────────────────────

void ZTooltip::showText(QWidget* target, const QString& text, int duration)
{
    if (!target || text.isEmpty()) return;

    auto* label = new QLabel(text);
    QPalette pal;
    pal.setColor(QPalette::Window, QColor(0x30, 0x31, 0x33));
    pal.setColor(QPalette::WindowText, Qt::white);
    label->setPalette(pal);
    label->setAutoFillBackground(true);
    label->setMargin(8);
    QFont f = label->font();
    f.setPixelSize(12);
    label->setFont(f);
    label->setWordWrap(true);
    label->setMaximumWidth(200);

    auto* popup = ZPopup::createPopup(target, label, ZPopup::kTop);
    popup->setAttribute(Qt::WA_DeleteOnClose, true);

    // Auto-hide after duration
    QTimer::singleShot(duration, popup, &QWidget::close);
}

void ZTooltip::install(QWidget* target, const QString& text)
{
    auto* tooltip = new ZTooltip(target);
    tooltip->setTarget(target);
    tooltip->setText(text);
    // ZTooltip will be parented to target, so it's cleaned up when target is destroyed
}
