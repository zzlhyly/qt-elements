#ifndef CODING_UICONTROLS_SRC_CHECKBOX_ZCHECKBOX_H_
#define CODING_UICONTROLS_SRC_CHECKBOX_ZCHECKBOX_H_

#include <QAbstractButton>

class ZCheckbox : public QAbstractButton
{
    Q_OBJECT

public:
    explicit ZCheckbox(QWidget* parent = nullptr);
    ZCheckbox(const QString& text, QWidget* parent = nullptr);

    void setIndeterminate(bool ind);
    bool isIndeterminate() const { return indeterminate_; }

    QSize sizeHint() const override;

protected:
    void paintEvent(QPaintEvent*) override;
    void nextCheckState() override;

private:
    bool indeterminate_ = false;
};

#endif // CODING_UICONTROLS_SRC_CHECKBOX_ZCHECKBOX_H_
