#ifndef CODING_UICONTROLS_SRC_TESTWIDGET_H_
#define CODING_UICONTROLS_SRC_TESTWIDGET_H_

#include <QWidget>

class QListWidget;
class QStackedWidget;

class TestWidget : public QWidget
{
public:
    explicit TestWidget(QWidget* parent = nullptr);

private:
    QListWidget* sidebar_ = nullptr;
    QStackedWidget* stack_ = nullptr;
};

#endif // CODING_UICONTROLS_SRC_TESTWIDGET_H_
