#ifndef CODING_UICONTROLS_SRC_SWITCH_ZSWITCH_H_
#define CODING_UICONTROLS_SRC_SWITCH_ZSWITCH_H_

#include <QAbstractButton>
#include <QPropertyAnimation>

class ZSwitch : public QAbstractButton
{
    Q_OBJECT
    Q_PROPERTY(qreal offset READ offset WRITE setOffset)

public:
    explicit ZSwitch(QWidget* parent = nullptr);

    QSize sizeHint() const override;

    qreal offset() const { return offset_; }
    void setOffset(qreal o);

protected:
    void paintEvent(QPaintEvent*) override;
    void nextCheckState() override;

private:
    QPropertyAnimation* anim_;
    qreal offset_ = 0.0;
};

#endif // CODING_UICONTROLS_SRC_SWITCH_ZSWITCH_H_
