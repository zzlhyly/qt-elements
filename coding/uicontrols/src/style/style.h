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

} // namespace style

#endif // STYLE_STYLE_H_
