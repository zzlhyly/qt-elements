#ifndef WIDGETS_INPUT_ZINPUT_H_
#define WIDGETS_INPUT_ZINPUT_H_

#include <QWidget>
#include "theme/theme.h"
#include "statemachine/statemachine.h"

class QLineEdit;
class QPushButton;
class QPlainTextEdit;
class QLabel;

namespace statemachine { class StateTracker; }

// ZInput — Element Plus input component.
// Wraps QLineEdit (or QPlainTextEdit in textarea mode) with clear button,
// password toggle, prefix/suffix icons, word limit, and autosize.
// Manages its own layout internally — no external layout required.

class ZInput : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(InputSize inputSize READ inputSize WRITE setInputSize)
    Q_PROPERTY(bool clearable READ isClearable WRITE setClearable)
    Q_PROPERTY(bool passwordMode READ isPasswordMode WRITE setPasswordMode)
    Q_PROPERTY(QString placeholderText READ placeholderText WRITE setPlaceholderText)
    Q_PROPERTY(bool autosize READ isAutosize WRITE setAutosize)
    Q_PROPERTY(bool showWordLimit READ isShowWordLimit WRITE setShowWordLimit)

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

    void setPrependWidget(QWidget* widget);
    void setAppendWidget(QWidget* widget);

    void setAutosize(bool autosize);
    void setAutosizeMinRows(int rows);
    void setAutosizeMaxRows(int rows);
    bool isAutosize() const { return autosize_; }

    void setShowWordLimit(bool show);
    bool isShowWordLimit() const { return show_word_limit_; }
    void setMaxLength(int len);

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
    void updateWordLimit();

    QLineEdit* edit_;
    QPushButton* clear_btn_ = nullptr;
    QPushButton* password_btn_ = nullptr;
    QPlainTextEdit* textarea_ = nullptr;
    QWidget* prepend_widget_ = nullptr;
    QWidget* append_widget_ = nullptr;
    QLabel* word_limit_label_ = nullptr;

    InputSize size_ = kDefault;
    bool clearable_ = false;
    bool password_mode_ = false;
    QChar prefix_icon_;
    QChar suffix_icon_;
    int rows_ = 3;
    statemachine::StateTracker* state_tracker_;

    bool autosize_ = false;
    int autosize_min_rows_ = 2;
    int autosize_max_rows_ = 6;
    bool show_word_limit_ = false;
    int max_length_ = 0;
};

#endif // WIDGETS_INPUT_ZINPUT_H_
