#include "ztooltip.h"
#include "popup/zpopup.h"

#include <QApplication>
#include <QEvent>
#include <QFontMetrics>
#include <QPainter>
#include <QPainterPath>
#include <QTimer>

namespace {

class TooltipContent : public QWidget {
public:
    explicit TooltipContent(const QString& text, QWidget* parent = nullptr) : QWidget(parent), text_(text) {
        QFont f = font();
        f.setPixelSize(12);
        setFont(f);
        QFontMetrics fm(f);
        int tw = fm.horizontalAdvance(text_) + 12;  // 6px padding each side
        int w = qMin(tw, 260);
        if (tw > 260) wordWrap_ = true;
        int th = (wordWrap_ ? fm.height() * 2 + 14 : fm.height()) + 14 + 5;  // text + pad + arrow
        setFixedSize(w, th);
    }
protected:
    void paintEvent(QPaintEvent*) override {
        QPainter p(this);
        p.setRenderHint(QPainter::Antialiasing);

        QRect body = rect().adjusted(0, 0, 0, -5);  // reserve 5px at bottom for arrow
        qreal radius = 4.0;

        // Dark background
        QPainterPath bgPath;
        bgPath.addRoundedRect(QRectF(body), radius, radius);
        p.setBrush(QColor(0x30, 0x31, 0x33));
        p.setPen(Qt::NoPen);
        p.drawPath(bgPath);

        // Arrow (triangle pointing down)
        int ax = width() / 2;
        int ay = height() - 1;
        QPainterPath arrow;
        arrow.moveTo(ax - 4, ay - 5);
        arrow.lineTo(ax, ay);
        arrow.lineTo(ax + 4, ay - 5);
        arrow.closeSubpath();
        p.drawPath(arrow);

        // Text
        QFont f = font();
        f.setPixelSize(12);
        p.setFont(f);
        p.setPen(Qt::white);
        if (wordWrap_) {
            p.drawText(body.adjusted(8, 7, -8, -7), Qt::AlignLeft | Qt::AlignVCenter | Qt::TextWordWrap, text_);
        } else {
            p.drawText(body, Qt::AlignCenter, text_);
        }
    }
private:
    QString text_;
    bool wordWrap_ = false;
};

} // namespace

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

void ZTooltip::setText(const QString& text) { text_ = text; }

void ZTooltip::onHoverTimeout()
{
    if (popup_) return;
    if (!target_ || text_.isEmpty()) return;

    auto* content = new TooltipContent(text_);
    popup_ = ZPopup::createPopup(target_, content, ZPopup::kTop);
    popup_->setAttribute(Qt::WA_DeleteOnClose, true);
    connect(popup_, &ZPopup::popupClosed, this, [this]() { popup_ = nullptr; });
}

bool ZTooltip::eventFilter(QObject* obj, QEvent* event)
{
    if (obj == target_) {
        if (event->type() == QEvent::Enter) {
            timer_->start();
        } else if (event->type() == QEvent::Leave) {
            timer_->stop();
            if (popup_) { popup_->close(); popup_ = nullptr; }
        }
    }
    return QObject::eventFilter(obj, event);
}

void ZTooltip::showText(QWidget* target, const QString& text, int duration)
{
    if (!target || text.isEmpty()) return;
    auto* content = new TooltipContent(text);
    auto* popup = ZPopup::createPopup(target, content, ZPopup::kTop);
    popup->setAttribute(Qt::WA_DeleteOnClose, true);
    QTimer::singleShot(duration, popup, &QWidget::close);
}

void ZTooltip::install(QWidget* target, const QString& text)
{
    auto* tooltip = new ZTooltip(target);
    tooltip->setTarget(target);
    tooltip->setText(text);
}
