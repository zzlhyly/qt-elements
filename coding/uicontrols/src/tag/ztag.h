#ifndef CODING_UICONTROLS_SRC_TAG_ZTAG_H_
#define CODING_UICONTROLS_SRC_TAG_ZTAG_H_

#include <QWidget>

class ZTag : public QWidget
{
    Q_OBJECT

public:
    enum TagType { kDefault, kSuccess, kInfo, kWarning, kDanger };
    enum TagEffect { kLight, kDark, kPlain };
    enum TagSize { kLarge, kMedium, kSmall };

    explicit ZTag(QWidget* parent = nullptr);
    ZTag(const QString& text, QWidget* parent = nullptr);

    void setText(const QString& text);
    QString text() const;

    void setTagType(TagType type);
    void setEffect(TagEffect effect);
    void setTagSize(TagSize size);
    void setClosable(bool closable);
    void setRound(bool round);
    void setHit(bool hit);

    TagType tagType() const;
    TagEffect effect() const;
    TagSize tagSize() const;
    bool isClosable() const;
    bool isRound() const;
    bool isHit() const;

    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;

signals:
    void closed();

protected:
    void paintEvent(QPaintEvent*) override;
    void mousePressEvent(QMouseEvent*) override;
    void mouseReleaseEvent(QMouseEvent*) override;
    void mouseMoveEvent(QMouseEvent*) override;

private:
    struct SizeSpec { int height; int fontSize; int radius; int padH; int closeSize; int closeMargin; };
    const SizeSpec& sizeSpec() const;
    QColor bgColor() const;
    QColor textColor() const;
    QColor borderColor() const;
    QRect closeButtonRect() const;

    TagType type_ = kDefault;
    TagEffect effect_ = kLight;
    TagSize size_ = kMedium;
    QString text_;
    bool closable_ = false;
    bool round_ = false;
    bool hit_ = false;
    bool close_hovered_ = false;
    bool close_pressed_ = false;
};

#endif // CODING_UICONTROLS_SRC_TAG_ZTAG_H_
