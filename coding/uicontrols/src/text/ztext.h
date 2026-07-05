#ifndef CODING_UICONTROLS_SRC_TEXT_ZTEXT_H_
#define CODING_UICONTROLS_SRC_TEXT_ZTEXT_H_

#include <QWidget>

class ZText : public QWidget
{
    Q_OBJECT

public:
    enum TextType { kDefault, kPrimary, kSuccess, kInfo, kWarning, kDanger };
    enum TextSize { kLarge, kMedium, kSmall };

    explicit ZText(QWidget* parent = nullptr);
    ZText(const QString& text, QWidget* parent = nullptr);

    void setText(const QString& text);
    void setTextType(TextType type);
    void setTextSize(TextSize size);
    void setTruncated(bool truncated);

    QString text() const;
    TextType textType() const;
    TextSize textSize() const;
    bool isTruncated() const;

    QSize sizeHint() const override;

protected:
    void paintEvent(QPaintEvent*) override;

private:
    QColor resolveColor() const;
    int resolveFontSize() const;

    QString text_;
    TextType type_ = kDefault;
    TextSize size_ = kSmall;
    bool truncated_ = false;
};

#endif // CODING_UICONTROLS_SRC_TEXT_ZTEXT_H_
