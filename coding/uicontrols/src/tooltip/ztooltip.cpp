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
    TooltipContent(const QString& text, ZPopup::Placement placement, QWidget* parent = nullptr)
        : QWidget(parent), text_(text), placement_(placement)
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
        if (wordWrap_ && horiz) {
            th = fm.height() * 2 + 14 + 5;
        } else if (horiz) {
            th = fm.height() + 14 + 5;
        } else {
            th = fm.height() + 14;
        }
        if (!horiz) {
            w = tw + 5;
            w = qMin(w, 265);
            if (tw + 5 > 265) wordWrap_ = true;
        }
        setFixedSize(w, th);
        setMinimumSize(8, 8);
    }

protected:
    void paintEvent(QPaintEvent*) override {
        QPainter p(this);
        p.setRenderHint(QPainter::Antialiasing);

        qreal radius = 4.0;
        bool horiz = (placement_ == ZPopup::kTop || placement_ == ZPopup::kBottom);

        QRect body;
        if (horiz) {
            if (placement_ == ZPopup::kTop)
                body = rect().adjusted(0, 0, 0, -5);
            else
                body = rect().adjusted(0, 5, 0, 0);
        } else {
            if (placement_ == ZPopup::kLeft)
                body = rect().adjusted(0, 0, -5, 0);
            else
                body = rect().adjusted(5, 0, 0, 0);
        }

        QPainterPath bgPath;
        bgPath.addRoundedRect(QRectF(body), radius, radius);
        p.setBrush(QColor(0x30, 0x31, 0x33));
        p.setPen(Qt::NoPen);
        p.drawPath(bgPath);

        if (horiz) {
            int ax = width() / 2;
            if (placement_ == ZPopup::kTop) {
                int ay = height() - 1;
                QPainterPath arrow;
                arrow.moveTo(ax - 4, ay - 5);
                arrow.lineTo(ax, ay);
                arrow.lineTo(ax + 4, ay - 5);
                arrow.closeSubpath();
                p.drawPath(arrow);
            } else {
                QPainterPath arrow;
                arrow.moveTo(ax - 4, 5);
                arrow.lineTo(ax, 0);
                arrow.lineTo(ax + 4, 5);
                arrow.closeSubpath();
                p.drawPath(arrow);
            }
        } else {
            int ay = height() / 2;
            if (placement_ == ZPopup::kLeft) {
                int ax = width() - 1;
                QPainterPath arrow;
                arrow.moveTo(ax - 5, ay - 4);
                arrow.lineTo(ax, ay);
                arrow.lineTo(ax - 5, ay + 4);
                arrow.closeSubpath();
                p.drawPath(arrow);
            } else {
                QPainterPath arrow;
                arrow.moveTo(5, ay - 4);
                arrow.lineTo(0, ay);
                arrow.lineTo(5, ay + 4);
                arrow.closeSubpath();
                p.drawPath(arrow);
            }
        }

        QFont f = font();
        f.setPixelSize(12);
        p.setFont(f);
        p.setPen(Qt::white);
        if (wordWrap_) {
            p.drawText(body.adjusted(4, 7, -4, -7), Qt::AlignHCenter | Qt::AlignVCenter | Qt::TextWordWrap, text_);
        } else {
            p.drawText(body, Qt::AlignCenter, text_);
        }
    }

private:
    QString text_;
    ZPopup::Placement placement_;
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
void ZTooltip::setPlacement(ZPopup::Placement p) { placement_ = p; }

void ZTooltip::onHoverTimeout()
{
    if (popup_) return;
    if (!target_ || text_.isEmpty()) return;

    auto* content = new TooltipContent(text_, placement_);
    popup_ = ZPopup::createPopup(target_, content, placement_);
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
    auto* content = new TooltipContent(text, ZPopup::kTop);
    auto* popup = ZPopup::createPopup(target, content, ZPopup::kTop);
    popup->setAttribute(Qt::WA_DeleteOnClose, true);
    QTimer::singleShot(duration, popup, &QWidget::close);
}

void ZTooltip::install(QWidget* target, const QString& text, ZPopup::Placement placement)
{
    auto* tooltip = new ZTooltip(target);
    tooltip->setTarget(target);
    tooltip->setText(text);
    tooltip->setPlacement(placement);
}
