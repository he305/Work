#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "widjetkoir.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    int CalcGeoToGK_KAM();
    void on_CalcGeoToGK_clicked();
    void CalcGKtoGeo_KAM();
    void on_CalcGKtoGeo_clicked();
    void on_CalcSfer_clicked();
    void on_CalcMPTSKi_clicked();

 //   void on_CalcKamGK_clicked();

    void on_CalcCOIR_clicked();

private:
    Ui::MainWindow *ui;
    double B_kam,L_kam,H_kam, Xgk_kam, Ygk_kam, Zgk_kam; // Геодезические координаты и координаты в проекции гаусса крюгера камеры
    double B,L,H, Xgk, Ygk, Zgk; // Геодезические координаты и координаты в проекции гаусса крюгера ориентира
    double r,b,e;                // Сферические координаты орниентира относительно камеры
    double x,y,z;                // Координаты в МПТСКи
    double Lat_kmplx, Longt_kmplx, Z_kmplx, B_kmplx; // Коордианты и азимут ПРЛ
    double x_kam_kmplx, y_kam_kmplx, z_kam_kmplx;  // Коордианты камеры на ПРЛ
    int RezCalc;
};

#endif // MAINWINDOW_H
