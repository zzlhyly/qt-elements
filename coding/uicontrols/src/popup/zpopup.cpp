#include "zpopup.h"

#include <QApplication>
#include <QDesktopWidget>
#include <QPainter>
#include <QVBoxLayout>

ZPopup::ZPopup(QWidget* parent)
    : QWidget(parent)
{
    setWindowFlags(Qt::Popup | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground, true);
    setAttribute(Qt::WA_ShowWithoutActivating, true);

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

    adjustSize();  // ensure correct size before calculating position

    QPoint targetTL = target->mapToGlobal(QPoint(0, 0));
    QPoint pos;
    int tw = target->width();
    int th = target->height();
    int pw = width();
    int ph = height();

    switch (placement) {
    case kBottom:
        pos = QPoint(targetTL.x() + (tw - pw) / 2, targetTL.y() + th);
        break;
    case kTop:
        pos = QPoint(targetTL.x() + (tw - pw) / 2, targetTL.y() - ph);
        break;
    case kLeft:
        pos = QPoint(targetTL.x() - pw, targetTL.y() + (th - ph) / 2);
        break;
    case kRight:
        pos = QPoint(targetTL.x() + tw, targetTL.y() + (th - ph) / 2);
        break;
    }

    fitToScreen(pos);
    show();
    raise();
}

void ZPopup::fitToScreen(const QPoint& pos)
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

bool ZPopup::event(QEvent* e)
{
    if (e->type() == QEvent::Close) {
        emit popupClosed();
    }
    return QWidget::event(e);
}
