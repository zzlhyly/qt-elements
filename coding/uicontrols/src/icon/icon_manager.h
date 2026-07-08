#ifndef ICON_ICON_MANAGER_H_
#define ICON_ICON_MANAGER_H_

#include <QFont>
#include <QIcon>
#include <QMap>
#include <QPainter>
#include <QString>

class IconManager {
public:
    static IconManager& Instance();

    // Load icon from file path (SVG, PNG, etc.). Cached by path.
    QIcon LoadIcon(const QString& path);

    // Load icon from unicode glyph using a default icon font.
    QIcon LoadGlyphIcon(ushort unicode);

    // Create a tinted version of an icon (useful for hover/pressed states).
    QIcon TintIcon(const QIcon& source, const QColor& tintColor);

    // Paint icon DPI-aware at given logical size, centered in rect.
    void Paint(QPainter* painter, const QRect& rect, const QIcon& icon,
               int logicalSize,
               Qt::Alignment alignment = Qt::AlignCenter) const;

    // Clear the cache.
    void ClearCache();

private:
    IconManager() = default;
    ~IconManager() = default;
    IconManager(const IconManager&) = delete;
    IconManager& operator=(const IconManager&) = delete;

    QMap<QString, QIcon> cache_;
    QFont iconFont_;  // lazy-initialized
};

#endif  // ICON_ICON_MANAGER_H_

