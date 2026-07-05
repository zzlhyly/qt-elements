#ifndef CODING_UICONTROLS_SRC_RADIO_ZRADIO_H_
#define CODING_UICONTROLS_SRC_RADIO_ZRADIO_H_

#include <QAbstractButton>

class ZRadio : public QAbstractButton
{
    Q_OBJECT

public:
    explicit ZRadio(QWidget* parent = nullptr);
    ZRadio(const QString& text, QWidget* parent = nullptr);

    QSize sizeHint() const override;

protected:
    void paintEvent(QPaintEvent*) override;
};

#endif // CODING_UICONTROLS_SRC_RADIO_ZRADIO_H_
