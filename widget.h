#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTimer>
#include <QMouseEvent>
#include <QPainter>
#include <math.h>
#include <QDebug>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
private:
    bool isOn = false;
    QTimer timer;
    int x;
    bool running = false;
private:
    void onTimer();
};
#endif // WIDGET_H
