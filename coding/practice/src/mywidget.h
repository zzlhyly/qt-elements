#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
class MyWidget : public QWidget
{
    Q_OBJECT
public:
    using QWidget::QWidget; // Inherit constructors from QWidget
    void initialize();

protected:
    void closeEvent(QCloseEvent *event) override;
};

#endif