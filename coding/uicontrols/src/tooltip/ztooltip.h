#ifndef CODING_UICONTROLS_SRC_TOOLTIP_ZTOOLTIP_H_
#define CODING_UICONTROLS_SRC_TOOLTIP_ZTOOLTIP_H_

#include <QObject>
#include <QTimer>

class QWidget;
class ZPopup;

class ZTooltip : public QObject
{
    Q_OBJECT

public:
    explicit ZTooltip(QObject* parent = nullptr);
    ~ZTooltip();

    void setTarget(QWidget* widget);
    void setText(const QString& text);

    static void showText(QWidget* target, const QString& text, int duration = 3000);
    static void install(QWidget* target, const QString& text);

private slots:
    void onHoverTimeout();

private:
    bool eventFilter(QObject* obj, QEvent* event) override;
    void showPopup();

    QWidget* target_ = nullptr;
    QString text_;
    QTimer* timer_;
    ZPopup* popup_ = nullptr;
};

#endif // CODING_UICONTROLS_SRC_TOOLTIP_ZTOOLTIP_H_
