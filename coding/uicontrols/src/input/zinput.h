#ifndef CODING_UICONTROLS_SRC_INPUT_ZINPUT_H_
#define CODING_UICONTROLS_SRC_INPUT_ZINPUT_H_

#include <QWidget>

class QLineEdit;
class QPushButton;

class ZInput : public QWidget
{
    Q_OBJECT

public:
    enum InputSize { kLarge, kDefault, kSmall };

    explicit ZInput(QWidget* parent = nullptr);

    void setText(const QString& text);
    QString text() const;
    void setPlaceholderText(const QString& text);
    QString placeholderText() const;

    void setInputSize(InputSize size);
    void setClearable(bool clearable);
    void setPasswordMode(bool password);

    InputSize inputSize() const;
    bool isClearable() const;
    bool isPasswordMode() const;
    QLineEdit* lineEdit() const;

signals:
    void textChanged(const QString& text);

protected:
    void paintEvent(QPaintEvent*) override;
    bool eventFilter(QObject* obj, QEvent* event) override;

private:
    void updateLayout();
    void updateClearButton();

    QLineEdit* edit_;
    QPushButton* clear_btn_ = nullptr;
    QPushButton* password_btn_ = nullptr;
    InputSize size_ = kDefault;
    bool clearable_ = false;
    bool password_mode_ = false;
    bool hovered_ = false;
};

#endif // CODING_UICONTROLS_SRC_INPUT_ZINPUT_H_
