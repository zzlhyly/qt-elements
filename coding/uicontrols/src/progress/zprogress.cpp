#include "zprogress.h"
#include "theme/theme.h"

#include <QFontMetrics>
#include <QPainter>
#include <QPainterPath>

ZProgress::ZProgress(QWidget* parent)
    : QWidget(parent)
{
}

void ZProgress::setPercentage(int p)   { percentage_ = qBound(0, p, 100); update(); }
void ZProgress::setType(ProgressType t){ type_ = t; updateGeometry(); update(); }
void ZProgress::setStrokeWidth(int w)  { strokeWidth_ = qMax(1, w); update(); }
void ZProgress::setStatus(ProgressStatus s) { status_ = s; update(); }
void ZProgress::setShowText(bool s)    { showText_ = s; update(); }
void ZProgress::setIndeterminate(bool i) {
    if (i) {
        if (!indTimer_) {
            indTimer_ = new QTimer(this);
            indTimer_->setInterval(50);
            connect(indTimer_, &QTimer::timeout, this, [this]() {
                indPos_ += indDir_;
                if (indPos_ >= 70) indDir_ = -1;
                if (indPos_ <= 0) indDir_ = 1;
                update();
            });
        }
        indTimer_->start();
    } else if (indTimer_) {
        indTimer_->stop();
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
    p.setRenderHint(QPainter::TextAntialiasing);

    if (type_ == kDashboard) {
        drawDashboard(p);
    } else if (type_ == kCircle) {
        drawCircle(p);
    } else {
        drawLine(p);
    }
}

void ZProgress::drawCircle(QPainter& p)
{
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
        f.setWeight(QFont::Normal);
        p.setFont(f);
        p.setPen(theme::textRegular());
        QString label = QString::number(percentage_) + QStringLiteral("%");
        if (percentage_ == 100 && status_ == kSuccess)
            label = QString(QChar(0x2713));
        p.drawText(QRectF(0, 0, width(), height()), Qt::AlignCenter, label);
    }
}

void ZProgress::drawDashboard(QPainter& p)
{
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
        f.setWeight(QFont::Normal);
        p.setFont(f);
        p.setPen(theme::textRegular());
        QString label = QString::number(percentage_) + QStringLiteral("%");
        if (percentage_ == 100 && status_ == kSuccess)
            label = QString(QChar(0x2713));
        p.drawText(QRectF(0, 0, width(), height()), Qt::AlignCenter, label);
    }
}

void ZProgress::drawLine(QPainter& p)
{
    int w = width();
    int h = height();
    int trackY = (h - strokeWidth_) / 2;
    int trackH = strokeWidth_;

    // Reserve space for outside text
    int textW = 0;
    if (showText_ && !textInside_ && !indeterminate_) {
        QFont f = font();
        f.setPixelSize(12);
        QFontMetrics fm(f);
        QString label = QString::number(percentage_) + QStringLiteral("%");
        textW = fm.horizontalAdvance(label) + 8;
    }
    int barW = qMax(w - textW, 20);

    // Track background
    QRectF trackRect(0, trackY, barW, trackH);
    QPainterPath trackPath;
    trackPath.addRoundedRect(trackRect, trackH / 2.0, trackH / 2.0);
    p.setBrush(QColor(0xeb, 0xee, 0xf5));
    p.setPen(Qt::NoPen);
    p.drawPath(trackPath);

    if (indeterminate_) {
        int blockW = barW * 30 / 100;
        int blockX = indPos_ * barW / 100;
        QRectF blockRect(blockX, trackY, blockW, trackH);
        QPainterPath blockPath;
        blockPath.addRoundedRect(blockRect, trackH / 2.0, trackH / 2.0);
        blockPath = blockPath.intersected(trackPath);
        p.setBrush(theme::colorPrimary());
        p.drawPath(blockPath);
    } else if (percentage_ > 0) {
        int fillW = qMax(trackH, barW * percentage_ / 100);
        QRectF fillRect(0, trackY, fillW, trackH);
        QPainterPath fillPath;
        fillPath.addRoundedRect(fillRect, trackH / 2.0, trackH / 2.0);
        fillPath = fillPath.intersected(trackPath);
        p.setBrush(statusColor());
        p.drawPath(fillPath);

        // Inside text
        if (showText_ && textInside_) {
            QFont f = font();
            f.setPixelSize(12);
            f.setWeight(QFont::Normal);
            p.setFont(f);
            p.setPen(Qt::white);
            QString label = QString::number(percentage_) + QStringLiteral("%");
            p.drawText(QRectF(0, trackY, fillW, trackH), Qt::AlignCenter, label);
        }
    }

    // Outside text
    if (showText_ && !textInside_ && !indeterminate_) {
        QFont f = font();
        f.setPixelSize(12);
        f.setWeight(QFont::Normal);
        p.setFont(f);
        p.setPen(theme::textRegular());
        QString label = QString::number(percentage_) + QStringLiteral("%");
        p.drawText(QRect(barW + 4, 0, textW, h), Qt::AlignLeft | Qt::AlignVCenter, label);
    }
}
