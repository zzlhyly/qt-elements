#include "painter/painter.h"

#include <QFontMetrics>
#include <QPainterPath>

namespace painter {

void DrawBackground(QPainter& p, const QRect& rect,
                    const QColor& color, qreal borderRadius) {
    if (!color.isValid() || color.alpha() == 0) return;

    p.setPen(Qt::NoPen);
    p.setBrush(color);
    if (borderRadius > 0) {
        p.drawRoundedRect(rect, borderRadius, borderRadius);
    } else {
        p.drawRect(rect);
    }
}

void DrawBorder(QPainter& p, const QRectF& rect,
                const QColor& color, qreal width, qreal borderRadius,
                Qt::PenStyle style) {
    if (!color.isValid() || color.alpha() == 0) return;
    if (width <= 0.0) return;

    QPainterPath path;
    if (borderRadius > 0) {
        path.addRoundedRect(rect, borderRadius, borderRadius);
    } else {
        path.addRect(rect);
    }

    QPen pen(color, width, style);
    pen.setCosmetic(true);
    p.setPen(pen);
    p.setBrush(Qt::NoBrush);
    p.drawPath(path);
}

void DrawText(QPainter& p, const QRect& rect,
              const QString& text, const QFont& font, const QColor& color,
              Qt::Alignment alignment) {
    if (text.isEmpty()) return;

    p.setFont(font);
    p.setPen(color);

    QFontMetrics fm(font);
    QString elided = text;
    if (fm.horizontalAdvance(text) > rect.width()) {
        elided = fm.elidedText(text, Qt::ElideRight, rect.width());
    }

    p.drawText(rect, alignment, elided);
}

void DrawIcon(QPainter& p, const QRect& rect,
              const QIcon& icon, int logicalSize,
              Qt::Alignment alignment, QIcon::Mode mode) {
    if (icon.isNull()) return;
    if (logicalSize <= 0) return;

    int x = rect.x() + (rect.width() - logicalSize) / 2;
    int y = rect.y() + (rect.height() - logicalSize) / 2;

    // Adjust for right-alignment override.
    if (alignment & Qt::AlignRight) {
        x = rect.right() - logicalSize;
    } else if (alignment & Qt::AlignLeft) {
        x = rect.x();
    }
    if (alignment & Qt::AlignBottom) {
        y = rect.bottom() - logicalSize;
    } else if (alignment & Qt::AlignTop) {
        y = rect.y();
    }

    QRect targetRect(x, y, logicalSize, logicalSize);
    icon.paint(&p, targetRect, Qt::AlignCenter, mode);
}

void DrawFocusRing(QPainter& p, const QRectF& rect,
                   qreal borderRadius, const QColor& focusColor,
                   qreal offset) {
    if (!focusColor.isValid() || focusColor.alpha() == 0) return;

    QPainterPath path;
    QRectF outer = rect.adjusted(-offset, -offset, offset, offset);
    if (borderRadius > 0) {
        path.addRoundedRect(outer, borderRadius + offset,
                            borderRadius + offset);
    } else {
        path.addRect(outer);
    }

    QPen pen(focusColor, 2.0);
    pen.setCosmetic(true);
    p.setPen(pen);
    p.setBrush(Qt::NoBrush);
    p.drawPath(path);
}

void DrawShadow(QPainter& p, const QRect& rect,
                qreal borderRadius, int blurRadius, qreal offsetY,
                const QColor& shadowColor) {
    Q_UNUSED(blurRadius);
    if (!shadowColor.isValid() || shadowColor.alpha() == 0) return;

    QRect shadowRect = rect.translated(0, static_cast<int>(offsetY));
    p.setPen(Qt::NoPen);
    p.setBrush(shadowColor);
    if (borderRadius > 0) {
        p.drawRoundedRect(shadowRect, borderRadius, borderRadius);
    } else {
        p.drawRect(shadowRect);
    }
}

void DrawStateOverlay(QPainter& p, const QRect& rect,
                      qreal borderRadius, const QColor& overlayColor) {
    DrawBackground(p, rect, overlayColor, borderRadius);
}

}  // namespace painter
