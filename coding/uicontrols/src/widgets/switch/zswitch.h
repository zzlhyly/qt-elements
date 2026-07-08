#ifndef WIDGETS_SWITCH_ZSWITCH_H_
#define WIDGETS_SWITCH_ZSWITCH_H_

#include <QAbstractButton>
#include <QString>
#include "animation/animation_manager.h"

class ZSwitch : public QAbstractButton
{
    Q_OBJECT

    Q_PROPERTY(SwitchSize switchSize READ switchSize WRITE setSwitchSize)
    Q_PROPERTY(bool loading READ isLoading WRITE setLoading)
    Q_PROPERTY(QString activeText READ activeText WRITE setActiveText)
    Q_PROPERTY(QString inactiveText READ inactiveText WRITE setInactiveText)

public:
    enum SwitchSize { kLarge, kDefault, kSmall };

    explicit ZSwitch(QWidget* parent = nullptr);

    QSize sizeHint() const override;

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
    void startSlideAnimation();
    void startLoadingAnimation();
    void stopLoadingAnimation();

    qreal offset_ = 0.0;
    SwitchSize size_ = kDefault;
    bool loading_ = false;
    QString active_text_;
    QString inactive_text_;
    AnimationManager* anim_manager_;
    AnimHandle slide_anim_;
    AnimHandle loading_anim_;
    qreal loading_angle_ = 0;
};

#endif // WIDGETS_SWITCH_ZSWITCH_H_
