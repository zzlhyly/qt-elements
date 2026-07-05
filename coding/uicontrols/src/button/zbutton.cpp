#include "zbutton.h"
#include <QPainter>
#include <QPainterPath>

ZButton::ZButton(QWidget* parent)
    : QAbstractButton(parent)
{
    setButtonSize(BS_Medium);
}

void ZButton::setButtonSize(ButtonSize size)
{
    m_buttonSize = size;
    switch (size)
    {
    case ZButton::BS_Small:
        setFixedSize(120, 36);
        break;
    case ZButton::BS_Medium:
        setFixedSize(200, 40);
        break;
    case ZButton::BS_Large:
        setFixedSize(320, 56);
        break;
    default:
        break;
    }
}

void ZButton::setButtonType(ButtonType type)
{
    m_buttonType = type;;
    switch (type)
    {
    case ZButton::BT_Normal:
        m_radius = 8.0;
        break;
    case ZButton::BT_Chips:
        m_radius = height() / 2.0;
        break;
    default:
        break;
    }
}

void ZButton::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(Qt::NoPen);

    QPainterPath outterPath;
    outterPath.addRoundedRect(rect(), m_radius, m_radius);
    painter.setClipPath(outterPath);
    painter.setBrush(Qt::white);
    if (underMouse())
    {
        painter.setBrush(Qt::green);
    }
    painter.drawRect(rect());

    QPainterPath innerPath;
    innerPath.addRoundedRect(rect().adjusted(1, 1, -1, -1), m_radius - 1, m_radius - 1);
    painter.setClipPath(outterPath - innerPath);

    painter.setBrush(Qt::gray);
    painter.drawRect(rect());
}