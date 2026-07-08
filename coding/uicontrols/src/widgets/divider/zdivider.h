#ifndef WIDGETS_DIVIDER_ZDIVIDER_H_
#define WIDGETS_DIVIDER_ZDIVIDER_H_

#include <QWidget>
#include "theme/theme.h"

class ZDivider : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(Direction direction READ direction WRITE setDirection)
    Q_PROPERTY(ContentPosition contentPosition READ contentPosition WRITE setContentPosition)
    Q_PROPERTY(BorderStyle borderStyle READ borderStyle WRITE setBorderStyle)

public:
    enum Direction { kHorizontal, kVertical };
    enum ContentPosition { kLeft, kCenter, kRight };
    enum BorderStyle { kSolid, kDashed, kDotted };

    explicit ZDivider(QWidget* parent = nullptr);
    ZDivider(const QString& text, QWidget* parent = nullptr);

    void setText(const QString& text);
    void setDirection(Direction dir);
    void setContentPosition(ContentPosition pos);
    void setBorderStyle(BorderStyle style);

    QString text() const;
    Direction direction() const;
    ContentPosition contentPosition() const;
    BorderStyle borderStyle() const;

    QSize sizeHint() const override;

protected:
    void paintEvent(QPaintEvent*) override;

private:
    QString text_;
    Direction direction_ = kHorizontal;
    ContentPosition contentPos_ = kCenter;
    BorderStyle borderStyle_ = kSolid;
};

#endif // WIDGETS_DIVIDER_ZDIVIDER_H_
