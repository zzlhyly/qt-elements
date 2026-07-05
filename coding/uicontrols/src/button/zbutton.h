#ifndef ZBUTTON_H
#define ZBUTTON_H

#include <QAbstractButton>

class ZButton : public QAbstractButton
{
    Q_OBJECT

public:
    enum ButtonType { BT_Default, BT_Primary, BT_Success, BT_Warning, BT_Danger, BT_Info };
    enum ButtonSize { BS_Large, BS_Default, BS_Small };
    enum ButtonVariant { BV_Solid, BV_Plain, BV_Text };

    explicit ZButton(QWidget* parent = nullptr);
    ZButton(const QString& text, QWidget* parent = nullptr);

    void setButtonType(ButtonType type);
    void setButtonSize(ButtonSize size);
    void setButtonVariant(ButtonVariant variant);
    void setRound(bool round);
    void setCircle(bool circle);

    ButtonType buttonType() const;
    ButtonSize buttonSize() const;
    ButtonVariant buttonVariant() const;
    bool isRound() const;
    bool isCircle() const;

    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;

protected:
    void paintEvent(QPaintEvent*) override;
    void enterEvent(QEvent*) override;
    void leaveEvent(QEvent*) override;
    void keyPressEvent(QKeyEvent*) override;
    void changeEvent(QEvent*) override;

private:
    struct SizeSpec { int height; int fontSize; int radius; int padH; int border; int iconGap; };
    const SizeSpec& sizeSpec() const;
    qreal borderRadius() const;
    QColor bgColor() const;
    QColor textColor() const;
    QColor borderColor() const;

    ButtonType m_type = BT_Default;
    ButtonSize m_size = BS_Default;
    ButtonVariant m_variant = BV_Solid;
    bool m_round = false;
    bool m_circle = false;
    bool m_hovered = false;
};

#endif // ZBUTTON_H
