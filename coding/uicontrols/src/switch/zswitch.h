#ifndef CODING_UICONTROLS_SRC_SWITCH_ZSWITCH_H_
#define CODING_UICONTROLS_SRC_SWITCH_ZSWITCH_H_

#include <QAbstractButton>
#include <QPropertyAnimation>
#include <QTimer>
#include <QString>

class ZSwitch : public QAbstractButton
{
    Q_OBJECT
    Q_PROPERTY(qreal offset READ offset WRITE setOffset)

public:
    enum SwitchSize { kLarge, kDefault, kSmall };

    explicit ZSwitch(QWidget* parent = nullptr);

    QSize sizeHint() const override;

    qreal offset() const { return offset_; }
    void setOffset(qreal o);

    void setSwitchSize(SwitchSize size);
    void setLoading(bool loading);
    void setActiveText(const QString& text);
    void setInactiveText(const QString& text);

    SwitchSize switchSize() const { return size_; }
    bool isLoading() const { return loading_; }
    QString activeText() const { return active_text_; }
    QString inactiveText() const { return inactive_text_; }

protected:
    void paintEvent(QPaintEvent*) override;
    void nextCheckState() override;
    void checkStateSet() override;

private:
    QPropertyAnimation* anim_;
    qreal offset_ = 0.0;
    SwitchSize size_ = kDefault;
    bool loading_ = false;
    QString active_text_;
    QString inactive_text_;
    QTimer* loading_timer_ = nullptr;
    int loading_angle_ = 0;
};

#endif // CODING_UICONTROLS_SRC_SWITCH_ZSWITCH_H_
