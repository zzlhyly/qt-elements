#include "zprogress.h"
#include "theme/theme.h"

#include <QFontMetrics>
#include <QPainter>
#include <QPainterPath>

ZProgress::ZProgress(QWidget* parent)
    : QWidget(parent)
{
    indTimer_ = new QTimer(this);
    indTimer_->setInterval(50);
    connect(indTimer_, &QTimer::timeout, this, [this]() {
        indPos_ += indDir_;
        if (indPos_ >= 70) indDir_ = -1;
        if (indPos_ <= 0) indDir_ = 1;
        update();
    });
}

void ZProgress::setPercentage(int p)   { percentage_ = qBound(0, p, 100); update(); }
void ZProgress::setType(ProgressType t){ type_ = t; updateGeometry(); update(); }
void ZProgress::setStrokeWidth(int w)  { strokeWidth_ = qMax(1, w); update(); }
void ZProgress::setStatus(ProgressStatus s) { status_ = s; update(); }
void ZProgress::setShowText(bool s)    { showText_ = s; update(); }
void ZProgress::setIndeterminate(bool i) {
    indeterminate_ = i;
    if (i) indTimer_->start(); else indTimer_->stop();
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
    p.setRenderHint(QPainter::TextAntialiasing);

    if (type_ == kDashboard) {
        // Dashboard (semi-circle gauge)
        int side = qMin(width(), height());
        qreal cx = width() / 2.0;
        qreal cy = height() / 2.0;
        qreal radius = (side - strokeWidth_) / 2.0;

        QRectF arcRect(cx - radius, cy - radius, radius * 2.0, radius * 2.0);

        // Background arc: 240 degrees, from -210 to +30
        p.setBrush(Qt::NoBrush);
        QPen bgPen(QColor(0xeb, 0xee, 0xf5), strokeWidth_);
        bgPen.setCapStyle(Qt::RoundCap);
        p.setPen(bgPen);
        p.drawArc(arcRect, -210 * 16, 240 * 16);

        // Foreground arc
        if (percentage_ > 0) {
            QPen fgPen(statusColor(), strokeWidth_);
            fgPen.setCapStyle(Qt::RoundCap);
            p.setPen(fgPen);
            int spanAngle = percentage_ * 240 / 100 * 16;
            p.drawArc(arcRect, -210 * 16, -spanAngle);
        }

        // Center text
        if (showText_) {
            QFont f = font();
            f.setPixelSize(14);
            f.setWeight(QFont::Normal);
            p.setFont(f);
            p.setPen(theme::textRegular());
            QString label = QString::number(percentage_) + QStringLiteral("%");
            if (percentage_ == 100 && status_ == kSuccess) {
                label = QString(QChar(0x2713));
            }
            p.drawText(QRectF(0, 0, width(), height()), Qt::AlignCenter, label);
        }
    } else if (type_ == kCircle) {
        // Circle mode
        int side = qMin(width(), height());
        qreal cx = width() / 2.0;
        qreal cy = height() / 2.0;
        qreal radius = (side - strokeWidth_) / 2.0;

        QRectF arcRect(cx - radius, cy - radius, radius * 2.0, radius * 2.0);

        // Background ring
        p.setBrush(Qt::NoBrush);
        QPen bgPen(QColor(0xeb, 0xee, 0xf5), strokeWidth_);
        bgPen.setCapStyle(Qt::RoundCap);
        p.setPen(bgPen);
        p.drawArc(arcRect, 0, 360 * 16);

        // Foreground arc - starts at 12 o'clock (-90)
        if (percentage_ > 0) {
            QPen fgPen(statusColor(), strokeWidth_);
            fgPen.setCapStyle(Qt::RoundCap);
            p.setPen(fgPen);
            int spanAngle = percentage_ * 360 / 100 * 16;
            p.drawArc(arcRect, -90 * 16, -spanAngle);
        }

        // Center text
        if (showText_) {
            QFont f = font();
            f.setPixelSize(14);
            f.setWeight(QFont::Normal);
            p.setFont(f);
            p.setPen(theme::textRegular());
            QString label = QString::number(percentage_) + QStringLiteral("%");
            if (percentage_ == 100 && status_ == kSuccess) {
                label = QString(QChar(0x2713));
            }
            p.drawText(QRectF(0, 0, width(), height()), Qt::AlignCenter, label);
        }
    } else {
        // Line mode
        int w = width();
        int h = height();
        int trackY = (h - strokeWidth_) / 2;
        int trackH = strokeWidth_;

        QFont f = font();
        f.setPixelSize(12);
        f.setWeight(QFont::Normal);
        QFontMetrics fm(f);

        QString label = QString::number(percentage_) + QStringLiteral("%");
        int textW = 0;
        if (showText_ && !textInside_ && !indeterminate_) {
            textW = fm.horizontalAdvance(label) + 8;
        }
        int barW = w - textW;

        // Track background
        QRectF trackRect(0, trackY, barW, trackH);
        QPainterPath trackPath;
        trackPath.addRoundedRect(trackRect, trackH / 2.0, trackH / 2.0);
        p.setBrush(QColor(0xeb, 0xee, 0xf5));
        p.setPen(Qt::NoPen);
        p.drawPath(trackPath);

        if (indeterminate_) {
            // Sliding block (30% width)
            int blockW = barW * 30 / 100;
            int blockX = indPos_ * barW / 100;
            QRectF blockRect(blockX, trackY, blockW, trackH);
            QPainterPath blockPath;
            blockPath.addRoundedRect(blockRect, trackH / 2.0, trackH / 2.0);
            blockPath = blockPath.intersected(trackPath);
            p.setBrush(theme::colorPrimary());
            p.setPen(Qt::NoPen);
            p.drawPath(blockPath);
        } else if (percentage_ > 0) {
            // Filled portion
            int fillW = qMax(trackH, barW * percentage_ / 100);
            QRectF fillRect(0, trackY, fillW, trackH);
            QPainterPath fillPath;
            fillPath.addRoundedRect(fillRect, trackH / 2.0, trackH / 2.0);
            fillPath = fillPath.intersected(trackPath);
            p.setBrush(statusColor());
            p.setPen(Qt::NoPen);
            p.drawPath(fillPath);

            // Text inside bar
            if (showText_ && textInside_) {
                p.setFont(f);
                p.setPen(Qt::white);
                QRectF textRect(0, trackY, fillW, trackH);
                p.drawText(textRect, Qt::AlignCenter, label);
            }
        }

        // Text outside (right side)
        if (showText_ && !textInside_ && !indeterminate_) {
            p.setFont(f);
            p.setPen(theme::textRegular());
            p.drawText(QRect(barW + 4, 0, textW, h), Qt::AlignLeft | Qt::AlignVCenter, label);
        }
    }
}
