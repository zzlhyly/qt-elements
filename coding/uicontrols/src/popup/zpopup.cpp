#include "zpopup.h"
#include "theme/theme.h"

#include <QApplication>
#include <QDesktopWidget>
#include <QEvent>
#include <QPainter>
#include <QPainterPath>
#include <QVBoxLayout>

ZPopup::ZPopup(QWidget* parent)
    : QWidget(parent)
{
    setWindowFlags(Qt::Popup | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground, false);
    setAttribute(Qt::WA_DeleteOnClose, false);

    auto* lay = new QVBoxLayout(this);
    lay->setContentsMargins(0, 0, 0, 0);
    lay->setSpacing(0);
}

void ZPopup::setContent(QWidget* content)
{
    if (content_) {
        layout()->removeWidget(content_);
        content_->setParent(nullptr);
    }
    content_ = content;
    qobject_cast<QVBoxLayout*>(layout())->addWidget(content_);
    adjustSize();
}

QWidget* ZPopup::content() const
{
    return content_;
}

void ZPopup::showAt(QWidget* target, Placement placement)
{
    target_ = target;
    placement_ = placement;

    if (!target_) return;
    QPoint pos;
    switch (placement) {
    case kBottom:
        pos = target->mapToGlobal(QPoint(0, target->height()));
        break;
    case kTop:
        pos = target->mapToGlobal(QPoint(0, 0)) - QPoint(0, height());
        break;
    case kLeft:
        pos = target->mapToGlobal(QPoint(0, 0)) - QPoint(width(), 0);
        break;
    case kRight:
        pos = target->mapToGlobal(QPoint(target->width(), 0));
        break;
    }
    adjustPosition(pos);
    show();
    raise();
}

void ZPopup::showAt(const QPoint& globalPos)
{
    adjustPosition(globalPos);
    show();
    raise();
}

void ZPopup::adjustPosition(const QPoint& pos)
{
    QRect screen = QApplication::desktop()->availableGeometry(pos);
    int x = qBound(screen.left(), pos.x(), screen.right() - width());
    int y = qBound(screen.top(), pos.y(), screen.bottom() - height());
    move(x, y);
}

ZPopup* ZPopup::createPopup(QWidget* target, QWidget* content, Placement placement)
{
    auto* popup = new ZPopup(target ? target->window() : nullptr);
    popup->setContent(content);
    if (target) popup->showAt(target, placement);
    return popup;
}

void ZPopup::paintEvent(QPaintEvent*)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    QRect r = rect();
    qreal radius = theme::borderRadiusBase();  // 4px

    // White background
    QPainterPath bgPath;
    bgPath.addRoundedRect(QRectF(r), radius, radius);
    p.setBrush(Qt::white);
    p.setPen(Qt::NoPen);
    p.drawPath(bgPath);

    // 1px border
    QPainterPath borderPath;
    borderPath.addRoundedRect(QRectF(r).adjusted(0.5, 0.5, -0.5, -0.5), radius, radius);
    p.setBrush(Qt::NoBrush);
    p.setPen(QPen(QColor(0xe4, 0xe7, 0xed), 1));
    p.drawPath(borderPath);
}

bool ZPopup::event(QEvent* e)
{
    if (e->type() == QEvent::Close) {
        emit popupClosed();
    }
    return QWidget::event(e);
}
