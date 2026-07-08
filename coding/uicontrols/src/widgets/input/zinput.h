#ifndef WIDGETS_INPUT_ZINPUT_H_
#define WIDGETS_INPUT_ZINPUT_H_

#include <QWidget>
#include "theme/theme.h"
#include "statemachine/statemachine.h"

class QLineEdit;
class QPushButton;
class QPlainTextEdit;

namespace statemachine { class StateTracker; }

class ZInput : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(InputSize inputSize READ inputSize WRITE setInputSize)
    Q_PROPERTY(bool clearable READ isClearable WRITE setClearable)
    Q_PROPERTY(bool passwordMode READ isPasswordMode WRITE setPasswordMode)
    Q_PROPERTY(QString placeholderText READ placeholderText WRITE setPlaceholderText)

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
    void setTextarea(int rows);
    void setPrefixIcon(const QChar& icon);
    void setSuffixIcon(const QChar& icon);

    InputSize inputSize() const;
    bool isClearable() const;
    bool isPasswordMode() const;
    QLineEdit* lineEdit() const;
    int rows() const { return rows_; }

signals:
    void textChanged(const QString& text);

protected:
    void paintEvent(QPaintEvent*) override;
    bool eventFilter(QObject* obj, QEvent* event) override;
    void changeEvent(QEvent*) override;

private:
    void updateLayout();
    void updateClearButton();

    QLineEdit* edit_;
    QPushButton* clear_btn_ = nullptr;
    QPushButton* password_btn_ = nullptr;
    QPlainTextEdit* textarea_ = nullptr;
    InputSize size_ = kDefault;
    bool clearable_ = false;
    bool password_mode_ = false;
    int rows_ = 0;
    QChar prefix_icon_;
    QChar suffix_icon_;

    statemachine::StateTracker* state_tracker_;
};

#endif // WIDGETS_INPUT_ZINPUT_H_
