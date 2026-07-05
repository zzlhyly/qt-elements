#ifndef CODING_UICONTROLS_SRC_ALERT_ZALERT_H_
#define CODING_UICONTROLS_SRC_ALERT_ZALERT_H_

#include <QWidget>

class ZAlert : public QWidget
{
    Q_OBJECT

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
    QColor bgColor() const;
    QColor borderColor() const;
    QColor textColor() const;
    QChar iconGlyph() const;
    QRect closeButtonRect() const;

    QString title_;
    AlertType type_ = kInfo;
    AlertEffect effect_ = kLight;
    bool closable_ = false;
    bool showIcon_ = true;
    bool center_ = false;
    bool close_hovered_ = false;
    bool close_pressed_ = false;
};

#endif // CODING_UICONTROLS_SRC_ALERT_ZALERT_H_
