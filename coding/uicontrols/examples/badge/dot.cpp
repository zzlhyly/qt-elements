#include <QHBoxLayout>
#include <QWidget>
#include "widgets/badge/zbadge.h"

QWidget* ZBadgeDemoDot() {
    auto* w = new QWidget();
    auto* row = new QHBoxLayout(w);
    row->setSpacing(16);
    const char* names[] = {"Primary", "Success", "Info", "Warning", "Danger"};
    const ZBadge::BadgeType types[] = {ZBadge::kPrimary, ZBadge::kSuccess, ZBadge::kInfo,
                                       ZBadge::kWarning, ZBadge::kDanger};
    for (int i = 0; i < 5; ++i) {
        auto* badge = new ZBadge(10, w);
        badge->setBadgeType(types[i]);
        badge->setDot(true);
        row->addWidget(badge);
    }
    row->addStretch();
    return w;
}
