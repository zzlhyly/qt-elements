#include "zpopup.h"

#include <QApplication>
#include <QDesktopWidget>
#include <QVBoxLayout>

ZPopup::ZPopup(QWidget* parent)
    : QWidget(nullptr)  // ponytail: always top-level, no parent to avoid stacking issues
{
    setWindowFlags(Qt::ToolTip | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_NoSystemBackground);
    setAttribute(Qt::WA_ShowWithoutActivating);
    setAutoFillBackground(false);

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
    content_->setParent(this);
    qobject_cast<QVBoxLayout*>(layout())->addWidget(content_);
}

QWidget* ZPopup::content() const { return content_; }

void ZPopup::showAt(QWidget* target, Placement placement)
{
    if (!target) return;

    // Force layout before sizing
    layout()->activate();
    adjustSize();

    QPoint tl = target->mapToGlobal(QPoint(0, 0));
    int tw = target->width();
    int th = target->height();
    int pw = width();
    int ph = height();

    QPoint pos;
    switch (placement) {
    case kTop:    pos = QPoint(tl.x() + (tw - pw) / 2, tl.y() - ph - 2); break;  // 2px gap to prevent flicker
    case kBottom: pos = QPoint(tl.x() + (tw - pw) / 2, tl.y() + th); break;
    case kLeft:   pos = QPoint(tl.x() - pw, tl.y() + (th - ph) / 2); break;
    case kRight:  pos = QPoint(tl.x() + tw, tl.y() + (th - ph) / 2); break;
    }

    // Clamp to screen
    QRect screen = QApplication::desktop()->availableGeometry(pos);
    pos.setX(qBound(screen.left(), pos.x(), screen.right() - pw));
    pos.setY(qBound(screen.top(), pos.y(), screen.bottom() - ph));

    move(pos);
    show();
}

ZPopup* ZPopup::createPopup(QWidget* target, QWidget* content, Placement placement)
{
    auto* popup = new ZPopup();
    popup->setContent(content);
    if (target) popup->showAt(target, placement);
    return popup;
}

bool ZPopup::event(QEvent* e)
{
    if (e->type() == QEvent::Close) emit popupClosed();
    return QWidget::event(e);
}
