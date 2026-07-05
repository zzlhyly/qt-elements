#ifndef CODING_UICONTROLS_SRC_PROGRESS_ZPROGRESS_H_
#define CODING_UICONTROLS_SRC_PROGRESS_ZPROGRESS_H_

#include <QWidget>

class ZProgress : public QWidget
{
    Q_OBJECT

public:
    enum ProgressType { kLine, kCircle };
    enum ProgressStatus { kNormal, kSuccess, kException, kWarning };

    explicit ZProgress(QWidget* parent = nullptr);

    void setPercentage(int percentage);
    void setType(ProgressType type);
    void setStrokeWidth(int width);
    void setStatus(ProgressStatus status);
    void setShowText(bool show);

    int percentage() const { return percentage_; }
    ProgressType type() const { return type_; }
    int strokeWidth() const { return strokeWidth_; }
    ProgressStatus status() const { return status_; }
    bool isShowText() const { return showText_; }

    QSize sizeHint() const override;

protected:
    void paintEvent(QPaintEvent*) override;

private:
    QColor statusColor() const;

    int percentage_ = 0;
    ProgressType type_ = kLine;
    int strokeWidth_ = 6;
    ProgressStatus status_ = kNormal;
    bool showText_ = true;
};

#endif // CODING_UICONTROLS_SRC_PROGRESS_ZPROGRESS_H_
