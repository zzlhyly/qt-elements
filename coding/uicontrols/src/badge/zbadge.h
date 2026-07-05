#ifndef CODING_UICONTROLS_SRC_BADGE_ZBADGE_H_
#define CODING_UICONTROLS_SRC_BADGE_ZBADGE_H_

#include <QWidget>
#include "theme/theme.h"

class ZBadge : public QWidget
{
    Q_OBJECT

public:
    enum BadgeType { kPrimary, kSuccess, kInfo, kWarning, kDanger };

    explicit ZBadge(QWidget* parent = nullptr);
    ZBadge(int value, QWidget* parent = nullptr);

    void setValue(int value);
    void setBadgeType(BadgeType type);
    void setMax(int max);
    void setDot(bool dot);
    void setBadgeHidden(bool hidden);

    int value() const;
    BadgeType badgeType() const;
    int max() const;
    bool isDot() const;
    bool isBadgeHidden() const;

    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;

protected:
    void paintEvent(QPaintEvent*) override;

private:
    int value_ = 0;
    BadgeType type_ = kDanger;
    int max_ = 99;
    bool dot_ = false;
    bool hidden_ = false;
};

#endif // CODING_UICONTROLS_SRC_BADGE_ZBADGE_H_
