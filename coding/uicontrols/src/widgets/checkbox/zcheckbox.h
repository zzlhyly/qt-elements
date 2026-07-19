#ifndef WIDGETS_CHECKBOX_ZCHECKBOX_H_
#define WIDGETS_CHECKBOX_ZCHECKBOX_H_

#include <QAbstractButton>

// ZCheckbox — Element Plus checkbox with indeterminate state support.
// Renders via QPainter: custom checkbox indicator + optional text label.

class ZCheckbox : public QAbstractButton
{
    Q_OBJECT

    Q_PROPERTY(bool indeterminate READ isIndeterminate WRITE setIndeterminate)

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

#endif // WIDGETS_CHECKBOX_ZCHECKBOX_H_
