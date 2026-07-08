#include <QHBoxLayout>
#include <QWidget>
#include "widgets/badge/zbadge.h"

QWidget* ZBadgeDemoBasic() {
    auto* w = new QWidget();
    auto* row = new QHBoxLayout(w);
    row->setSpacing(16);
    const char* names[] = {"Primary", "Success", "Info", "Warning", "Danger"};
    const ZBadge::BadgeType types[] = {ZBadge::kPrimary, ZBadge::kSuccess, ZBadge::kInfo,
                                       ZBadge::kWarning, ZBadge::kDanger};
    for (int i = 0; i < 5; ++i) {
        auto* badge = new ZBadge(10, w);
        badge->setBadgeType(types[i]);
        row->addWidget(badge);
    }
    row->addStretch();
    return w;
}
