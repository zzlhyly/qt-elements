#ifndef WIDGETS_TAG_ZTAG_H_
#define WIDGETS_TAG_ZTAG_H_

#include <QWidget>
#include "theme/theme.h"
#include "statemachine/statemachine.h"
#include "style/style.h"

namespace statemachine { class StateTracker; }

class ZTag : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(TagType tagType READ tagType WRITE setTagType)
    Q_PROPERTY(TagEffect effect READ effect WRITE setEffect)
    Q_PROPERTY(TagSize tagSize READ tagSize WRITE setTagSize)
    Q_PROPERTY(bool closable READ isClosable WRITE setClosable)
    Q_PROPERTY(bool round READ isRound WRITE setRound)
    Q_PROPERTY(bool hit READ isHit WRITE setHit)

public:
    enum TagType { kPrimary, kSuccess, kInfo, kWarning, kDanger };
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
    QRect closeButtonRect() const;

    TagType type_ = kPrimary;
    TagEffect effect_ = kLight;
    TagSize size_ = kMedium;
    QString text_;
    bool closable_ = false;
    bool round_ = false;
    bool hit_ = false;

    statemachine::StateTracker* close_state_;
};

#endif // WIDGETS_TAG_ZTAG_H_
