#ifndef CODING_UICONTROLS_SRC_LINK_ZLINK_H_
#define CODING_UICONTROLS_SRC_LINK_ZLINK_H_

#include <QWidget>
#include "theme/theme.h"

class ZLink : public QWidget
{
    Q_OBJECT

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
    bool hovered_ = false;
};

#endif // CODING_UICONTROLS_SRC_LINK_ZLINK_H_
