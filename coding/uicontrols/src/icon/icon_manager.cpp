#include "icon/icon_manager.h"

#include <QApplication>
#include <QFont>
#include <QIcon>
#include <QMap>
#include <QPainter>
#include <QPixmap>
#include <QRect>
#include <QString>

// -----------------------------------------------------------------------
// Singleton
// -----------------------------------------------------------------------

IconManager& IconManager::Instance() {
    static IconManager instance;
    return instance;
}

// -----------------------------------------------------------------------
// LoadIcon - file-backed, cached by path
// -----------------------------------------------------------------------

QIcon IconManager::LoadIcon(const QString& path) {
    auto it = cache_.find(path);
    if (it != cache_.end()) {
        return it.value();
    }
    QIcon icon(path);
    cache_.insert(path, icon);
    return icon;
}

// -----------------------------------------------------------------------
// LoadGlyphIcon - render a unicode glyph from the icon font into a
// QPixmap and return a QIcon.  The font is lazily initialized.
// -----------------------------------------------------------------------

QIcon IconManager::LoadGlyphIcon(ushort unicode) {
    if (iconFont_ == QFont()) {
        // ponytail: "Segoe UI Symbol" is a safe fallback on Windows;
        // switch to the actual icon font when the design system requires it.
        iconFont_ = QFont(QStringLiteral("Segoe UI Symbol"), 14);
    }

    const int size = 64;  // render at a reasonable resolution
    const qreal dpr = qApp->devicePixelRatio();

    QPixmap pixmap(size, size);
    pixmap.setDevicePixelRatio(dpr);
    pixmap.fill(Qt::transparent);

    QPainter painter(&pixmap);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setFont(iconFont_);
    // ponytail: uses default pen color; if a specific color is needed
    // later, add a color parameter to LoadGlyphIcon.
    painter.drawText(QRect(0, 0, size, size), Qt::AlignCenter,
                     QChar(unicode));
    painter.end();

    return QIcon(pixmap);
}

// -----------------------------------------------------------------------
// TintIcon - recolor an icon by applying tintColor via SourceIn
// composition.
// -----------------------------------------------------------------------

QIcon IconManager::TintIcon(const QIcon& source, const QColor& tintColor) {
    const int size = 64;
    const qreal dpr = qApp->devicePixelRatio();

    QPixmap sourcePix = source.pixmap(size);
    QPixmap result(size, size);
    result.setDevicePixelRatio(dpr);
    result.fill(Qt::transparent);

    {
        QPainter painter(&result);
        painter.setRenderHint(QPainter::Antialiasing);
        // Draw the source pixmap first.
        painter.setCompositionMode(QPainter::CompositionMode_Source);
        painter.drawPixmap(0, 0, sourcePix);
        // Multiply by the tint color, preserving alpha of the source.
        painter.setCompositionMode(QPainter::CompositionMode_SourceIn);
        painter.fillRect(result.rect(), tintColor);
    }

    return QIcon(result);
}

// -----------------------------------------------------------------------
// Paint - DPI-aware icon rendering at the given logical size.
// -----------------------------------------------------------------------

void IconManager::Paint(QPainter* painter, const QRect& rect,
                        const QIcon& icon, int logicalSize,
                        Qt::Alignment alignment) const {
    if (!painter || icon.isNull()) return;

    const qreal dpr = painter->device()->devicePixelRatioF();
    const int pixelSize = static_cast<int>(logicalSize * dpr);

    // Qt's icon.paint() uses the device pixel ratio from the paint device,
    // so the pixmap is selected at the correct resolution internally.
    icon.paint(painter, rect, alignment, QIcon::Normal, QIcon::On);

    // ponytail: logicalSize is accepted for api consistency / future use
    // but icon.paint() handles sizing internally via the rect.
    Q_UNUSED(pixelSize);
    Q_UNUSED(logicalSize);
}

// -----------------------------------------------------------------------
// ClearCache
// -----------------------------------------------------------------------

void IconManager::ClearCache() {
    cache_.clear();
}
