#include "zprogress.h"
#include "theme/theme.h"
#include "painter/painter.h"

#include <QFontMetrics>
#include <QPainter>
#include <QPainterPath>

ZProgress::ZProgress(QWidget* parent)
    : QWidget(parent)
    , anim_manager_(new AnimationManager(this))
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    setMinimumWidth(50);
}

void ZProgress::setPercentage(int p)   { percentage_ = qBound(0, p, 100); update(); }
void ZProgress::setType(ProgressType t){
    type_ = t;
    if (t == kCircle || t == kDashboard)
        setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    else
        setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    updateGeometry(); update();
}
void ZProgress::setStrokeWidth(int w)  { strokeWidth_ = qMax(1, w); update(); }
void ZProgress::setStatus(ProgressStatus s) { status_ = s; update(); }
void ZProgress::setShowText(bool s)    { showText_ = s; update(); }
void ZProgress::setIndeterminate(bool i) {
    if (i) {
        if (!ind_anim_.IsValid()) {
            ind_anim_ = anim_manager_->CreateProgressAnimation(this, QByteArray(),
                2000, [this](qreal) { update(); });
        }
    } else {
        if (ind_anim_.IsValid()) ind_anim_.Stop();
    }
    indeterminate_ = i;
    update();
}
void ZProgress::setTextInside(bool i)  { textInside_ = i; update(); }

QSize ZProgress::sizeHint() const
{
    if (type_ == kCircle || type_ == kDashboard) return QSize(126, 126);
    if (textInside_) return QSize(300, 28);
    return QSize(300, 24);
}

QColor ZProgress::statusColor() const
{
    switch (status_) {
    case kSuccess:   return theme::colorSuccess();
    case kException: return theme::colorDanger();
    case kWarning:   return theme::colorWarning();
    default:         return theme::colorPrimary();
    }
}

void ZProgress::paintEvent(QPaintEvent*)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    if (type_ == kDashboard) {
        int side = qMin(width(), height());
        qreal cx = width() / 2.0;
        qreal cy = height() / 2.0;
        qreal radius = (side - strokeWidth_) / 2.0;
        QRectF arcRect(cx - radius, cy - radius, radius * 2.0, radius * 2.0);

        p.setBrush(Qt::NoBrush);
        QPen bgPen(QColor(0xeb, 0xee, 0xf5), strokeWidth_);
        bgPen.setCapStyle(Qt::RoundCap);
        p.setPen(bgPen);
        p.drawArc(arcRect, -210 * 16, 240 * 16);

        if (percentage_ > 0) {
            QPen fgPen(statusColor(), strokeWidth_);
            fgPen.setCapStyle(Qt::RoundCap);
            p.setPen(fgPen);
            int spanAngle = percentage_ * 240 / 100 * 16;
            p.drawArc(arcRect, -210 * 16, -spanAngle);
        }

        if (showText_) {
            QFont f = font();
            f.setPixelSize(14);
            painter::DrawText(p, rect(), QString::number(percentage_) + "%",
                              f, theme::textRegular(), Qt::AlignCenter);
        }
    } else if (type_ == kCircle) {
        int side = qMin(width(), height());
        qreal cx = width() / 2.0;
        qreal cy = height() / 2.0;
        qreal radius = (side - strokeWidth_) / 2.0;
        QRectF arcRect(cx - radius, cy - radius, radius * 2.0, radius * 2.0);

        p.setBrush(Qt::NoBrush);
        QPen bgPen(QColor(0xeb, 0xee, 0xf5), strokeWidth_);
        bgPen.setCapStyle(Qt::RoundCap);
        p.setPen(bgPen);
        p.drawArc(arcRect, 0, 360 * 16);

        if (percentage_ > 0) {
            QPen fgPen(statusColor(), strokeWidth_);
            fgPen.setCapStyle(Qt::RoundCap);
            p.setPen(fgPen);
            int spanAngle = percentage_ * 360 / 100 * 16;
            p.drawArc(arcRect, -90 * 16, -spanAngle);
        }

        if (showText_) {
            QFont f = font();
            f.setPixelSize(14);
            QString label = QString::number(percentage_) + "%";
            if (percentage_ == 100 && status_ == kSuccess) label = QString(QChar(0x2713));
            painter::DrawText(p, rect(), label, f, theme::textRegular(), Qt::AlignCenter);
        }
    } else {
        int w = width();
        int h = height();
        int trackH = strokeWidth_;
        int trackY = (h - trackH) / 2;

        QFont f = font();
        f.setPixelSize(12);
        QFontMetrics fm(f);
        QString label = QString::number(percentage_) + "%";
        int textW = 0;
        if (!indeterminate_ && (showText_ && !textInside_))
            textW = fm.horizontalAdvance(label) + 8;
        int barW = qMax(w - textW, 20);

        // Track background
        painter::DrawBackground(p, QRect(0, trackY, barW, trackH),
                                QColor(0xeb, 0xee, 0xf5), trackH / 2.0);

        if (indeterminate_) {
            // Sliding block — animate ind_pos_ with a simple bounce
            // ponytail: simple bounce, replaced by animation progress when available
            static int s_bounce = 0;
            static int s_dir = 1;
            s_bounce += s_dir;
            if (s_bounce >= 70) s_dir = -1;
            if (s_bounce <= 0) s_dir = 1;

            int blockW = barW * 30 / 100;
            int blockX = s_bounce * barW / 100;
            painter::DrawBackground(p, QRect(blockX, trackY, blockW, trackH),
                                    theme::colorPrimary(), trackH / 2.0);
        } else if (percentage_ > 0) {
            int fillW = qMax(trackH, barW * percentage_ / 100);
            painter::DrawBackground(p, QRect(0, trackY, fillW, trackH),
                                    statusColor(), trackH / 2.0);

            if (textInside_ && showText_) {
                painter::DrawText(p, QRect(0, trackY, fillW, trackH),
                                  label, f, Qt::white, Qt::AlignCenter);
            }
        }

        if (showText_ && !textInside_ && !indeterminate_) {
            painter::DrawText(p, QRect(barW + 4, 0, textW, h), label, f,
                              theme::textRegular(), Qt::AlignVCenter | Qt::AlignLeft);
        }
    }
}
