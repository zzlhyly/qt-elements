#ifndef WIDGETS_ALERT_ZALERT_H_
#define WIDGETS_ALERT_ZALERT_H_

#include <QWidget>
#include "style/style.h"
#include "statemachine/statemachine.h"

namespace statemachine { class StateTracker; }

// ZAlert — Element Plus alert banner.
// Supports success/info/warning/error types, light/dark effects,
// optional icon, close button, and centered text.

class ZAlert : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(AlertType type READ type WRITE setType)
    Q_PROPERTY(AlertEffect effect READ effect WRITE setEffect)
    Q_PROPERTY(bool closable READ isClosable WRITE setClosable)
    Q_PROPERTY(bool showIcon READ isShowIcon WRITE setShowIcon)
    Q_PROPERTY(bool center READ isCenter WRITE setCenter)
    Q_PROPERTY(QString title READ title WRITE setTitle)

public:
    enum AlertType { kSuccess, kInfo, kWarning, kError };
    enum AlertEffect { kLight, kDark };

    explicit ZAlert(QWidget* parent = nullptr);
    explicit ZAlert(const QString& title, AlertType type = kInfo, QWidget* parent = nullptr);

    void setTitle(const QString& title);
    void setType(AlertType type);
    void setEffect(AlertEffect effect);
    void setClosable(bool closable);
    void setShowIcon(bool show);
    void setCenter(bool center);

    QString title() const;
    AlertType type() const;
    AlertEffect effect() const;
    bool isClosable() const;
    bool isShowIcon() const;
    bool isCenter() const;

    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;

signals:
    void closed();

protected:
    void paintEvent(QPaintEvent*) override;
    void mousePressEvent(QMouseEvent*) override;
    void mouseMoveEvent(QMouseEvent*) override;
    void mouseReleaseEvent(QMouseEvent*) override;

private:
    void Init();
    QRect closeButtonRect() const;

    QString title_;
    AlertType type_ = kInfo;
    AlertEffect effect_ = kLight;
    bool closable_ = false;
    bool showIcon_ = true;
    bool center_ = false;
    statemachine::StateTracker* close_state_;
};

#endif  // WIDGETS_ALERT_ZALERT_H_
