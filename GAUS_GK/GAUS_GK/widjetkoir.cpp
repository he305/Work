#include "widjetkoir.h"
#include "ui_widjetkoir.h"
#include "calc.h"
#include <math.h>

WidjetKOIR::WidjetKOIR(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidjetKOIR)
{
    ui->setupUi(this);
}

WidjetKOIR::~WidjetKOIR()
{
    delete ui;
}

void WidjetKOIR::on_RunCalcformationTaget_clicked()
{
    // Считывание

    ceilX = ui->ceilX->text().toDouble();
    ceilY = ui->ceilY->text().toDouble();
    ceilZ = ui->ceilZ->text().toDouble();
    velX = ui->Vxceil->text().toDouble();
    velY = ui->Vyceil->text().toDouble();
    BopuCur = ui->BopuCur->text().toDouble();
    FormationTagetOPU(ceilX, ceilY,  ceilZ, // Координаты целеуказания, м
                            BopuCur*M_PI/180,                           // Текущий  азимут ОПУ, радианы
                            velX,  velY,                 // Скорости в горизонтальной плоскости, м/с
                            &bOPU,&eOPU, &dT);              // Требуемй азимут и угол места ОПУ, радианы и время поворота
    ui->Bopu->setText(QString::number(bOPU*180/M_PI, 'f',3));
    ui->Eopu->setText(QString::number(eOPU*180/M_PI, 'f',3));
    ceilX = ceilX + velX*dT;
    ceilY = ceilY + velY*dT;
    /* Расчет азимута в радианах */
    double Bc;
    if ((ceilX > 0) && (ceilY > 0))
         Bc = atan((ceilY )/(ceilX));
    else
    if ((ceilX > 0) && (ceilY < 0))
         Bc = 2*M_PI +
                      atan((ceilY )/(ceilX));
    else
    if ((ceilX < 0) && (ceilY != 0))
        Bc = M_PI +
                     atan((ceilY )/(ceilX));
    else
    if ((ceilX > 0) && (ceilY == 0))
         Bc = 0;
    else
    if ((ceilX < 0) && (ceilY == 0))
         Bc = M_PI;
    else
    if ((ceilX == 0) && (ceilY > 0))
        Bc = M_PI/2;
    else
    if ((ceilX == 0) && (ceilY < 0))
         Bc = 3*M_PI/2;
    ui->Bceil->setText(QString::number(Bc*180/M_PI, 'f',3));
    ui->dT->setText(QString::number(dT, 'f',3));


}
