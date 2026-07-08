#ifndef WIDGETS_BUTTON_ZBUTTON_H_
#define WIDGETS_BUTTON_ZBUTTON_H_

#include <QAbstractButton>
#include <QIcon>
#include "theme/theme.h"

// Foundation modules
#include "statemachine/statemachine.h"
#include "animation/animation_manager.h"

namespace statemachine { class StateTracker; }
class AnimHandle;
class AnimationManager;

class ZButton : public QAbstractButton
{
    Q_OBJECT

    Q_PROPERTY(ButtonType buttonType READ buttonType WRITE setButtonType)
    Q_PROPERTY(ButtonSize buttonSize READ buttonSize WRITE setButtonSize)
    Q_PROPERTY(ButtonVariant buttonVariant READ buttonVariant WRITE setButtonVariant)
    Q_PROPERTY(bool round READ isRound WRITE setRound)
    Q_PROPERTY(bool circle READ isCircle WRITE setCircle)
    Q_PROPERTY(bool loading READ isLoading WRITE setLoading)

public:
    enum ButtonType { kDefault, kPrimary, kSuccess, kWarning, kDanger, kInfo };
    enum ButtonSize { kLarge, kMedium, kSmall };
    enum ButtonVariant { kSolid, kPlain, kText, kLink, kDashed };

    explicit ZButton(QWidget* parent = nullptr);
    ZButton(const QString& text, QWidget* parent = nullptr);
    ~ZButton() override;

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
    void enterEvent(QEvent*) override;
    void leaveEvent(QEvent*) override;
    void focusInEvent(QFocusEvent*) override;
    void mousePressEvent(QMouseEvent*) override;
    void keyPressEvent(QKeyEvent*) override;
    void changeEvent(QEvent*) override;

private:
    theme::SizeSpec sizeSpec() const;

    ButtonType type_ = kDefault;
    ButtonSize size_ = kMedium;
    ButtonVariant variant_ = kSolid;
    bool round_ = false;
    bool circle_ = false;
    bool loading_ = false;
    qreal loading_angle_ = 0;

    statemachine::StateTracker* state_tracker_;
    AnimationManager* anim_manager_;
    AnimHandle loading_anim_;
};

#endif // WIDGETS_BUTTON_ZBUTTON_H_
