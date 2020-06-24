#ifndef CLOCK_H
#define CLOCK_H
#include <QPaintEvent>

#include <QMainWindow>

class Clock : public QMainWindow
{
    Q_OBJECT

public:
    Clock(QWidget *parent = 0);
    ~Clock();

    void paintEvent(QPaintEvent *event);
};

#endif // CLOCK_H
