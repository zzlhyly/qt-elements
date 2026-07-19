#ifndef WIDGETS_TOOLTIP_ZTOOLTIP_H_
#define WIDGETS_TOOLTIP_ZTOOLTIP_H_

#include <QObject>
#include <QTimer>
#include "popup/zpopup.h"

class QWidget;

// ZTooltip — Element Plus tooltip overlay.
// Shows a popup with text on hover or manual trigger. Supports dark/light
// effects and configurable show/hide delays. Uses ZPopup for positioning.

class ZTooltip : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString text READ text WRITE setText)
    Q_PROPERTY(int showDelay READ showDelay WRITE setShowDelay)
    Q_PROPERTY(int hideDelay READ hideDelay WRITE setHideDelay)
    Q_PROPERTY(Effect effect READ effect WRITE setEffect)
    Q_PROPERTY(Trigger trigger READ trigger WRITE setTrigger)

public:
    enum Effect { kDark, kLight };
    enum Trigger { kHover, kManual };

    explicit ZTooltip(QObject* parent = nullptr);
    ~ZTooltip();

    void setTarget(QWidget* widget);
    void setText(const QString& text);
    QString text() const { return text_; }
    void setPlacement(ZPopup::Placement p);

    void setShowDelay(int ms);
    int showDelay() const { return showDelay_; }
    void setHideDelay(int ms);
    int hideDelay() const { return hideDelay_; }
    void setEffect(Effect e);
    Effect effect() const { return effect_; }
    void setTrigger(Trigger t);
    Trigger trigger() const { return trigger_; }

    void show();
    void hide();

    static void showText(QWidget* target, const QString& text,
                         Effect effect = kDark, int duration = 3000);
    static void install(QWidget* target, const QString& text,
                        ZPopup::Placement placement = ZPopup::kTop,
                        Effect effect = kDark);

private slots:
    void onHoverTimeout();

private:
    bool eventFilter(QObject* obj, QEvent* event) override;
    void showPopup();
    void hidePopup();
    void scheduleShow();
    void scheduleHide();

    QWidget* target_ = nullptr;
    QString text_;
    QTimer* show_timer_;
    QTimer* hide_timer_;
    ZPopup* popup_ = nullptr;
    ZPopup::Placement placement_ = ZPopup::kTop;
    Effect effect_ = kDark;
    Trigger trigger_ = kHover;
    int showDelay_ = 500;
    int hideDelay_ = 0;
};

#endif // WIDGETS_TOOLTIP_ZTOOLTIP_H_
