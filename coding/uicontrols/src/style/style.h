// style.h — Maps (type × state × variant) → resolved visual properties.
//
// Each component has a Resolve* function that takes theme tokens and returns
// a fully resolved visual struct (background, text, border colors + dimensions).
// The painter layer consumes these structs directly — no further logic needed.

#ifndef STYLE_STYLE_H_
#define STYLE_STYLE_H_

#include <QColor>
#include "theme/theme.h"

namespace style {

// ─── Button variant enum ──────────────────────────────────────────

enum class ButtonVariant {
    kSolid  = 0,
    kPlain  = 1,
    kText   = 2,
    kLink   = 3,
    kDashed = 4,
};

// ─── ButtonVisuals ────────────────────────────────────────────────

struct ButtonVisuals {
    QColor background;
    QColor textColor;
    QColor borderColor;
    qreal borderRadius;
    int borderWidth;
};

// ─── ResolveButton ────────────────────────────────────────────────

inline ButtonVisuals ResolveButton(
    theme::ButtonType type,
    theme::State state,
    ButtonVariant variant,
    bool round,
    bool circle,
    const theme::SizeSpec& sizeSpec)
{
    ButtonVisuals v;

    // ── Resolve colors per variant ──────────────────────────────────

    switch (variant) {
    case ButtonVariant::kSolid:
        v.background  = theme::buttonSolidBg(type, state);
        v.textColor   = theme::buttonSolidText(type, state);
        v.borderColor = theme::buttonSolidBorder(type, state);
        break;

    case ButtonVariant::kPlain: {
        // theme::buttonPlain* already redirects kDefault to solid
        v.background  = theme::buttonPlainBg(type, state);
        v.textColor   = theme::buttonPlainText(type, state);
        v.borderColor = theme::buttonPlainBorder(type, state);
        break;
    }

    case ButtonVariant::kText:
        // Background varies by state, otherwise transparent
        if (state == theme::kPressed) {
            v.background = theme::fillColor();
        } else if (state == theme::kHover) {
            v.background = theme::fillLight();
        } else {
            v.background = Qt::transparent;
        }
        // Text color: disabled uses theme::textDisabled, otherwise type color
        v.textColor = (state == theme::kDisabled)
                          ? theme::textDisabled()
                          : theme::buttonTextColor(type);
        v.borderColor = Qt::transparent;
        break;

    case ButtonVariant::kLink:
        v.background  = Qt::transparent;
        v.textColor   = theme::buttonLinkText(type, state);
        v.borderColor = Qt::transparent;
        break;

    case ButtonVariant::kDashed:
        // Same color logic as kPlain; painter applies the dashed stroke
        v.background  = theme::buttonPlainBg(type, state);
        v.textColor   = theme::buttonPlainText(type, state);
        v.borderColor = theme::buttonPlainBorder(type, state);
        break;
    }

    // ── Border radius ───────────────────────────────────────────────

    if (circle) {
        v.borderRadius = static_cast<qreal>(sizeSpec.height) / 2.0;
    } else if (round) {
        v.borderRadius = theme::borderRadiusRound();
    } else {
        v.borderRadius = static_cast<qreal>(sizeSpec.radius);
    }

    // ── Border width ────────────────────────────────────────────────

    switch (variant) {
    case ButtonVariant::kText:
    case ButtonVariant::kLink:
        v.borderWidth = 0;
        break;
    default:
        v.borderWidth = sizeSpec.border;
        break;
    }

    return v;
}

// ─── Tag Visuals ────────────────────────────────────────────────────

struct TagVisuals {
    QColor background;
    QColor textColor;
    QColor borderColor;
};

inline TagVisuals ResolveTag(int type, int effect, bool enabled) {
    TagVisuals v;
    if (!enabled) {
        v.background = Qt::transparent;
        v.textColor = theme::textDisabled();
        v.borderColor = theme::borderLight();
        return v;
    }
    if (effect == 0) { // kLight
        v.background = theme::tagLightBg(type);
        v.textColor = theme::tagTextColor(type);
        v.borderColor = theme::tagLightBorder(type);
    } else if (effect == 1) { // kDark
        v.background = theme::tagDarkBg(type);
        v.textColor = Qt::white;
        v.borderColor = theme::tagDarkBg(type);
    } else { // kPlain
        v.background = Qt::transparent;
        v.textColor = theme::tagTextColor(type);
        v.borderColor = theme::tagPlainBorder(type);
    }
    return v;
}

// ─── Alert Visuals ──────────────────────────────────────────────────

struct AlertVisuals {
    QColor background;
    QColor borderColor;
    QColor textColor;
    QChar iconGlyph;
};

inline AlertVisuals ResolveAlert(int type, int effect) {
    AlertVisuals v;
    if (effect == 1) { // kDark
        switch (type) {
        case 0: v.background = theme::colorSuccess(); v.iconGlyph = QChar(0x2714); break;
        case 1: v.background = theme::colorInfo();    v.iconGlyph = QChar(0x2139); break;
        case 2: v.background = theme::colorWarning(); v.iconGlyph = QChar(0x26A0); break;
        case 3: v.background = theme::colorDanger();  v.iconGlyph = QChar(0x2716); break;
        default: v.background = theme::colorInfo();   v.iconGlyph = QChar(0x2139); break;
        }
        v.borderColor = v.background;
        v.textColor = Qt::white;
    } else { // kLight
        switch (type) {
        case 0: v.background = theme::successLight9(); v.borderColor = theme::successLight8(); v.iconGlyph = QChar(0x2714); break;
        case 1: v.background = theme::infoLight9();    v.borderColor = theme::infoLight8();    v.iconGlyph = QChar(0x2139); break;
        case 2: v.background = theme::warningLight9(); v.borderColor = theme::warningLight8(); v.iconGlyph = QChar(0x26A0); break;
        case 3: v.background = theme::dangerLight9();  v.borderColor = theme::dangerLight8();  v.iconGlyph = QChar(0x2716); break;
        default: v.background = theme::infoLight9();   v.borderColor = theme::infoLight8();   v.iconGlyph = QChar(0x2139); break;
        }
        switch (type) {
        case 0: v.textColor = theme::colorSuccess(); break;
        case 2: v.textColor = theme::colorWarning(); break;
        case 3: v.textColor = theme::colorDanger();  break;
        default: v.textColor = theme::colorInfo();   break;
        }
    }
    return v;
}

} // namespace style

#endif // STYLE_STYLE_H_
