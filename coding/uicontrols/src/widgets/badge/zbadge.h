#ifndef WIDGETS_BADGE_ZBADGE_H_
#define WIDGETS_BADGE_ZBADGE_H_

#include <QWidget>
#include "theme/theme.h"

class ZBadge : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(int value READ value WRITE setValue)
    Q_PROPERTY(BadgeType badgeType READ badgeType WRITE setBadgeType)
    Q_PROPERTY(int max READ max WRITE setMax)
    Q_PROPERTY(bool dot READ isDot WRITE setDot)
    Q_PROPERTY(bool badgeHidden READ isBadgeHidden WRITE setBadgeHidden)

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

#endif // WIDGETS_BADGE_ZBADGE_H_
