#include "clock.h"
#include <QTimer>
#include <QTime>
#include <QPainter>
#include <QDebug>

Clock::Clock(QWidget *parent)
    : QMainWindow(parent)
{
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(1000);

    setWindowTitle(tr("Analog Clock"));
    resize(400, 400);
}

Clock::~Clock()
{

}

void Clock::paintEvent(QPaintEvent *)
{
    static const QPoint hourHand[3] =
    {
            QPoint(7, 8),
            QPoint(-7, 8),
            QPoint(0, -40)
    };
        static const QPoint minuteHand[3] = {
            QPoint(7, 8),
            QPoint(-7, 8),
            QPoint(0, -70)
        };
        static const QPoint secondHand[3] = {
            QPoint(7, 8),
            QPoint(-7, 8),
            QPoint(0, -90)
        };

        QColor hourColor(127, 0, 127);
        QColor minuteColor(0, 127, 127, 191);
        QColor secondColor(0, 12, 127, 127);

        int side = qMin(width(), height());
        QTime time = QTime::currentTime();

        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing, true); // 抗锯齿

        painter.translate(width()/2, height()/2);   //移动坐标系
        painter.scale(side/200.0, side/200.0);      //缩放 - 通过水平的 sx 和垂直的 sy 缩放坐标系

        painter.setPen(Qt::NoPen);
        painter.setBrush(hourColor);

        painter.save();
        painter.rotate(30.0 * ((time.hour() + time.minute() / 60.0)));  //旋转 - 对指定的轴用给定的角度反时针旋转坐标系统
        painter.drawConvexPolygon(hourHand, 3);
        painter.restore();

        painter.setPen(hourColor);  //画刻度
        for (int i = 0; i < 12; ++i)
        {
            painter.drawLine(88, 0, 96, 0);
            painter.rotate(30.0);
        }

        //-----画分钟-------
        painter.setPen(Qt::NoPen);
        painter.setBrush(minuteColor);

        painter.save();
        painter.rotate(6.0 * (time.minute() + time.second() / 60.0));
        painter.drawConvexPolygon(minuteHand, 3);
        painter.restore();

        painter.setPen(minuteColor);
        for (int j = 0; j < 60; ++j)
        {
            if ((j % 5) != 0)
                painter.drawLine(92, 0, 96, 0);
            painter.rotate(6.0);
        }

        //-----画秒钟
        painter.setPen(Qt::NoPen);
        painter.setBrush(secondColor);

        painter.save();
        painter.rotate(6.0 * time.second());
        painter.drawConvexPolygon(secondHand, 3);
        painter.restore();

        painter.end();

}
