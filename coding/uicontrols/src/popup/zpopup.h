#ifndef CODING_UICONTROLS_SRC_POPUP_ZPOPUP_H_
#define CODING_UICONTROLS_SRC_POPUP_ZPOPUP_H_

#include <QWidget>

class ZPopup : public QWidget
{
    Q_OBJECT

public:
    enum Placement { kBottom, kTop, kLeft, kRight };

    explicit ZPopup(QWidget* parent = nullptr);
    void setContent(QWidget* content);
    QWidget* content() const;

    void showAt(QWidget* target, Placement placement = kBottom);
    void showAt(const QPoint& globalPos);

    static ZPopup* createPopup(QWidget* target, QWidget* content, Placement placement = kBottom);

signals:
    void popupClosed();

protected:
    void paintEvent(QPaintEvent*) override;
    bool event(QEvent*) override;

private:
    void adjustPosition(const QPoint& pos);

    QWidget* content_ = nullptr;
    QWidget* target_ = nullptr;
    Placement placement_ = kBottom;
};

#endif // CODING_UICONTROLS_SRC_POPUP_ZPOPUP_H_
