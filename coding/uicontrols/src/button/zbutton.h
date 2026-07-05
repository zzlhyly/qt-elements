#ifndef CODING_UICONTROLS_SRC_BUTTON_ZBUTTON_H_
#define CODING_UICONTROLS_SRC_BUTTON_ZBUTTON_H_

#include <QAbstractButton>

class ZButton : public QAbstractButton
{
    Q_OBJECT

public:
    enum ButtonType { kDefault, kPrimary, kSuccess, kWarning, kDanger, kInfo };
    enum ButtonSize { kLarge, kMedium, kSmall };
    enum ButtonVariant { kSolid, kPlain, kText, kLink, kDashed };

    explicit ZButton(QWidget* parent = nullptr);
    ZButton(const QString& text, QWidget* parent = nullptr);

    void setButtonType(ButtonType type);
    void setButtonSize(ButtonSize size);
    void setButtonVariant(ButtonVariant variant);
    void setRound(bool round);
    void setCircle(bool circle);
    void setLoading(bool loading);
    bool isLoading() const;

    ButtonType buttonType() const;
    ButtonSize buttonSize() const;
    ButtonVariant buttonVariant() const;
    bool isRound() const;
    bool isCircle() const;

    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;

protected:
    void paintEvent(QPaintEvent*) override;
    void timerEvent(QTimerEvent*) override;
    void enterEvent(QEvent*) override;
    void leaveEvent(QEvent*) override;
    void focusInEvent(QFocusEvent*) override;
    void mousePressEvent(QMouseEvent*) override;
    void keyPressEvent(QKeyEvent*) override;
    void changeEvent(QEvent*) override;

private:
    struct SizeSpec { int height; int fontSize; int radius; int padH; int border; int iconGap; };
    const SizeSpec& sizeSpec() const;
    qreal borderRadius() const;
    QColor bgColor() const;
    QColor textColor() const;
    QColor borderColor() const;

    ButtonType type_ = kDefault;
    bool loading_ = false;
    int loading_timer_id_ = 0;
    int loading_angle_ = 0;
    ButtonSize size_ = kMedium;
    ButtonVariant variant_ = kSolid;
    bool round_ = false;
    bool circle_ = false;
    bool hovered_ = false;
    bool focus_keyboard_ = false;
};

#endif // CODING_UICONTROLS_SRC_BUTTON_ZBUTTON_H_
