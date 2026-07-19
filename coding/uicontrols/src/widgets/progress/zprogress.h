#ifndef WIDGETS_PROGRESS_ZPROGRESS_H_
#define WIDGETS_PROGRESS_ZPROGRESS_H_

#include <QWidget>
#include "animation/animation_manager.h"

// ZProgress — Element Plus progress bar.
// Supports line/circle/dashboard types, status coloring (normal/success/exception/warning),
// indeterminate animation, and optional text inside or outside the bar.

class ZProgress : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(int percentage READ percentage WRITE setPercentage)
    Q_PROPERTY(ProgressType type READ type WRITE setType)
    Q_PROPERTY(int strokeWidth READ strokeWidth WRITE setStrokeWidth)
    Q_PROPERTY(ProgressStatus status READ status WRITE setStatus)
    Q_PROPERTY(bool showText READ isShowText WRITE setShowText)
    Q_PROPERTY(bool indeterminate READ isIndeterminate WRITE setIndeterminate)
    Q_PROPERTY(bool textInside READ isTextInside WRITE setTextInside)

public:
    enum ProgressType { kLine, kCircle, kDashboard };
    enum ProgressStatus { kNormal, kSuccess, kException, kWarning };

    explicit ZProgress(QWidget* parent = nullptr);

    void setPercentage(int percentage);
    void setType(ProgressType type);
    void setStrokeWidth(int width);
    void setStatus(ProgressStatus status);
    void setShowText(bool show);
    void setIndeterminate(bool ind);
    void setTextInside(bool inside);

    int percentage() const { return percentage_; }
    ProgressType type() const { return type_; }
    int strokeWidth() const { return strokeWidth_; }
    ProgressStatus status() const { return status_; }
    bool isShowText() const { return showText_; }
    bool isIndeterminate() const { return indeterminate_; }
    bool isTextInside() const { return textInside_; }

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
    bool indeterminate_ = false;
    bool textInside_ = false;
    AnimationManager* anim_manager_;
    AnimHandle ind_anim_;
    int ind_pos_ = 0;
    int ind_dir_ = 1;
};

#endif // WIDGETS_PROGRESS_ZPROGRESS_H_
