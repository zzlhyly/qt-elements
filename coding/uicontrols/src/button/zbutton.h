#include <QAbstractButton>

class ZButton : public QAbstractButton
{
public:
    enum ButtonSize
    {
        BS_Small,
        BS_Medium,
        BS_Large
    };

    enum ButtonType
    {
        BT_Normal,
        BT_Chips
    };

public:
    explicit ZButton(QWidget* parent = nullptr);
    void setButtonSize(ButtonSize size);
    void setButtonType(ButtonType type);

protected:
    virtual void paintEvent(QPaintEvent* event) override;

private:
    ButtonSize m_buttonSize = BS_Medium;
    ButtonType m_buttonType = BT_Normal;
    qreal m_radius = 8.0;
};