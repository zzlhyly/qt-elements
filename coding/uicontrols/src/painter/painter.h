#ifndef PAINTER_PAINTER_H_
#define PAINTER_PAINTER_H_

#include <QColor>
#include <QFont>
#include <QIcon>
#include <QPainter>
#include <QRect>
#include <QRectF>
#include <QString>

namespace painter {

// Draw a filled rounded rectangle background with antialiasing.
// If color is invalid or fully transparent, does nothing.
void DrawBackground(QPainter& p, const QRect& rect,
                    const QColor& color, qreal borderRadius);

// Draw a stroked rounded rectangle border. Supports solid and dashed.
// If color is invalid/transparent or width <= 0, does nothing.
void DrawBorder(QPainter& p, const QRectF& rect,
                const QColor& color, qreal width, qreal borderRadius,
                Qt::PenStyle style = Qt::SolidLine);

// Draw text with alignment and right-elision for overflow.
// If text is empty, does nothing.
void DrawText(QPainter& p, const QRect& rect,
              const QString& text, const QFont& font, const QColor& color,
              Qt::Alignment alignment = Qt::AlignCenter);

// Draw an icon centered in a rect at given logical size.
void DrawIcon(QPainter& p, const QRect& rect,
              const QIcon& icon, int logicalSize,
              Qt::Alignment alignment = Qt::AlignCenter,
              QIcon::Mode mode = QIcon::Normal);

// Draw a focus ring (2px stroke) outside the rounded rect.
void DrawFocusRing(QPainter& p, const QRectF& rect,
                   qreal borderRadius, const QColor& focusColor,
                   qreal offset = 1.0);

// Draw a drop shadow behind the given rect.
void DrawShadow(QPainter& p, const QRect& rect,
                qreal borderRadius, int blurRadius, qreal offsetY,
                const QColor& shadowColor = QColor(0, 0, 0, 30));

// Draw a semi-transparent state overlay for hover/pressed/disabled states.
void DrawStateOverlay(QPainter& p, const QRect& rect,
                      qreal borderRadius, const QColor& overlayColor);

}  // namespace painter

#endif  // PAINTER_PAINTER_H_
