#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QUdpSocket>
#include <QDebug>
#include <QDateTime>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    int port;
    QUdpSocket* socket;
    void send(QByteArray data);
    void setSpeedXY(quint8 x, quint8 y);
    void getCurrentPoint();
    double xSpeed, ySpeed;

    double dMaxPAN, dMaxTILT, zeroX, zeroY, dStepPAN, dStepTILT;
    struct Point // структура для координат ОПУ - счетчики и углы
    {
        quint16 ix, iy; // счетчики шагов двигателей углов
        double  dx, dy; // азимут и угол места в градусах
    } setPoint, curPoint;

    void gradus2Steps(Point &mP);
    void steps2Gradus(Point &mP);
    int calcTimeOPU(Point &mP);
    int oldX, oldY;

    void findPelcoCS(QByteArray& command);

    quint8 sp, st;
    double azimutZero, azZeNew;
    double x0pan, y0pan,   // точки перехода на прямую по X и Y
           x0tilt, y0tilt,
           Kpan, Ktilt;

    int startTime;
    int endTime;
private slots:
    void read();
};

#endif // MAINWINDOW_H
