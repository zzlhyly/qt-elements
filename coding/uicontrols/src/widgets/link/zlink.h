#ifndef WIDGETS_LINK_ZLINK_H_
#define WIDGETS_LINK_ZLINK_H_

#include <QWidget>
#include "theme/theme.h"
#include "statemachine/statemachine.h"

namespace statemachine { class StateTracker; }

class ZLink : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(LinkType linkType READ linkType WRITE setLinkType)
    Q_PROPERTY(bool underline READ isUnderline WRITE setUnderline)

public:
    enum LinkType { kDefault, kPrimary, kSuccess, kWarning, kDanger, kInfo };

    explicit ZLink(QWidget* parent = nullptr);
    ZLink(const QString& text, QWidget* parent = nullptr);

    void setText(const QString& text);
    void setLinkType(LinkType type);
    void setUnderline(bool underline);

    QString text() const;
    LinkType linkType() const;
    bool isUnderline() const;

    QSize sizeHint() const override;

protected:
    void paintEvent(QPaintEvent*) override;
    void enterEvent(QEvent*) override;
    void leaveEvent(QEvent*) override;
    void mousePressEvent(QMouseEvent*) override;

signals:
    void clicked();

private:
    QString text_;
    LinkType type_ = kDefault;
    bool underline_ = false;
    statemachine::StateTracker* state_tracker_;
};

#endif  // WIDGETS_LINK_ZLINK_H_
