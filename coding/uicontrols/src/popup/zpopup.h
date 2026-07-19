#ifndef CODING_UICONTROLS_SRC_POPUP_ZPOPUP_H_
#define CODING_UICONTROLS_SRC_POPUP_ZPOPUP_H_

#include <QWidget>

// ZPopup — Lightweight positioned popup container.
// Shows content relative to a target widget at a given placement (top/bottom/left/right).
// Auto-fits to screen boundaries. Used by ZTooltip and other overlay components.

class ZPopup : public QWidget
{
    Q_OBJECT
public:
    enum Placement { kBottom, kTop, kLeft, kRight };

    explicit ZPopup(QWidget* parent = nullptr);
    void setContent(QWidget* content);
    QWidget* content() const;

    void showAt(QWidget* target, Placement placement = kBottom);

    static ZPopup* createPopup(QWidget* target, QWidget* content, Placement placement = kBottom);

signals:
    void popupClosed();

protected:
    bool event(QEvent*) override;

private:
    void fitToScreen(const QPoint& pos);

    QWidget* content_ = nullptr;
    QWidget* target_ = nullptr;
    Placement placement_ = kBottom;
};

#endif // CODING_UICONTROLS_SRC_POPUP_ZPOPUP_H_
