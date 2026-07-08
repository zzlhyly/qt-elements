#ifndef WIDGETS_RADIO_ZRADIO_H_
#define WIDGETS_RADIO_ZRADIO_H_

#include <QAbstractButton>

class ZRadio : public QAbstractButton
{
    Q_OBJECT

    Q_PROPERTY(bool border READ isBorder WRITE setBorder)

public:
    explicit ZRadio(QWidget* parent = nullptr);
    ZRadio(const QString& text, QWidget* parent = nullptr);

    void setBorder(bool border);
    bool isBorder() const { return border_; }

    QSize sizeHint() const override;

protected:
    void paintEvent(QPaintEvent*) override;

private:
    bool border_ = false;
};

#endif // WIDGETS_RADIO_ZRADIO_H_
