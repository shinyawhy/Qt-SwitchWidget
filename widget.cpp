#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{

    setWindowFlag(Qt::FramelessWindowHint);  // 去掉标题栏
    setAttribute(Qt::WA_TranslucentBackground,true);
    connect(&timer, &QTimer::timeout, this, &Widget::onTimer);
    timer.setInterval(40);

    QTimer::singleShot(100, [this]{
        QRect rect = this->rect();
        QRect outRoundRect = rect.adjusted(3, 3, -3, -3);
        x = outRoundRect.x() + 2;
        this->update();
    });
}

Widget::~Widget()
{
}

void Widget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.save();
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
    painter.setRenderHint(QPainter::TextAntialiasing, true);
    painter.setPen(Qt::transparent);

    QRect rect = this->rect();
    QRect outRoundRect = rect.adjusted(3, 3, -3, -3);

    if(x > outRoundRect.x() + outRoundRect.width() *0.45 - 2)
    {
        x = outRoundRect.x() +outRoundRect.width() * 0.45 - 2;
        if(running)
        {
            timer.stop();
            running = false;
        }
    }
    if(x < outRoundRect.x() + 2)
    {
        x = outRoundRect.x() + 2;
        if(running)
        {
            timer.stop();
            running = false;
        }
    }

    if(isOn)
    {
        if(running)
            painter.setBrush(QColor("#E7E7E7"));
        else
            painter.setBrush(QColor("#D93152"));

        painter.drawRoundedRect(outRoundRect, 6, 6);
        painter.setBrush(Qt::white);

        QRect innerRect;
        if(running)
            innerRect = QRect(x, outRoundRect.y() + 2,
                              outRoundRect.width() * 0.55, outRoundRect.height() - 4);
        else
            innerRect = QRect(outRoundRect.x() + outRoundRect.width() * 0.45 - 2 , outRoundRect.y() + 2,
                              outRoundRect.width() * 0.55, outRoundRect.height() - 4);

        painter.drawRoundedRect(innerRect, 8, 8);
    }
    else
    {
        if(running)
            painter.setBrush(QColor("#E7E7E7"));
        else
            painter.setBrush(QColor("#D93152"));
        painter.drawRoundRect(outRoundRect,6,6);
        painter.setBrush(Qt::white);

        QRect innerRect;
        if(running)
            innerRect = QRect(x,outRoundRect.y() + 2,outRoundRect.width() * 0.55,outRoundRect.height() - 4);
        else
            innerRect = QRect(outRoundRect.x() + 2,outRoundRect.y() + 2,outRoundRect.width() * 0.55,outRoundRect.height() - 4);
        painter.drawRoundRect(innerRect,8,8);

    }
    painter.restore();
}

void Widget::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        isOn = !isOn;
        timer.start();
    }
    return QWidget::mousePressEvent(event);
}

void Widget::mouseReleaseEvent(QMouseEvent *event)
{
    return QWidget::mouseReleaseEvent(event);
}

void Widget::onTimer()
{
    running = true;
    QRect rect = this->rect();
    if(isOn)
    {
        x += rect.width() * 0.072;
    }
    else
    {
        x -= rect.width() *0.072;
    }

    update();
}

