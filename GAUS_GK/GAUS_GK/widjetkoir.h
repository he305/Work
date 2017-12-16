#ifndef WIDJETKOIR_H
#define WIDJETKOIR_H

#include <QWidget>

namespace Ui {
class WidjetKOIR;
}

class WidjetKOIR : public QWidget
{
    Q_OBJECT

public:
    explicit WidjetKOIR(QWidget *parent = 0);
    ~WidjetKOIR();

private slots:
     void on_RunCalcformationTaget_clicked();

private:
    Ui::WidjetKOIR *ui;
    double ceilX, ceilY,ceilZ, velX, velY, BopuCur;
    double bOPU,eOPU, dT;                //Требуемые азимут и угол места ОПУ
};

#endif // WIDJETKOIR_H
