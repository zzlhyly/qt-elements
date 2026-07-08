#ifndef WIDGETS_TEXT_ZTEXT_H_
#define WIDGETS_TEXT_ZTEXT_H_

#include <QWidget>

class ZText : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(TextType textType READ textType WRITE setTextType)
    Q_PROPERTY(TextSize textSize READ textSize WRITE setTextSize)
    Q_PROPERTY(bool truncated READ isTruncated WRITE setTruncated)

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
    QString text_;
    TextType type_ = kDefault;
    TextSize size_ = kSmall;
    bool truncated_ = false;
};

#endif // WIDGETS_TEXT_ZTEXT_H_
