#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "widjetkoir.h"
#include "calc.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
   delete ui;
}


int MainWindow::CalcGeoToGK_KAM ()
{
    /*Расчет коордиант в проекции ГК камеры */
//    ui->lineEdit_X_GK_KAM ->setText(QString::number(00.00));
//    ui->lineEdit_Y_GK_KAM ->setText(QString::number(00.00));
//    ui->lineEdit_Z_GK_KAM ->setText(QString::number(00.00));
    B_kam = ui->lineEdit_B_KAM->text().toDouble();
    L_kam = ui->lineEdit_L_KAM->text().toDouble();
    H_kam = ui->lineEdit_H_KAM->text().toDouble();
    RezCalc = gauss(B_kam,L_kam,H_kam,&Xgk_kam,&Ygk_kam, &Zgk_kam);
    if (RezCalc == 2)
    {
        ui->lineEdit_B_KAM->setStyleSheet("color: rgb(255, 0, 0)");
        ui->lineEdit_B_KAM->setText(trUtf8("|B| > 90"));

    }
    if (RezCalc == 3)
    {
        ui->lineEdit_L_KAM->setStyleSheet("color: rgb(255, 0, 0)");
        ui->lineEdit_L_KAM->setText(trUtf8("|L| > 180"));

    }
    if (RezCalc == 2 || RezCalc == 3) return 1;

    ui->lineEdit_X_GK_KAM ->setText(QString::number(Xgk_kam, 'f', 1));
    ui->lineEdit_Y_GK_KAM ->setText(QString::number(Ygk_kam, 'f', 1));
    ui->lineEdit_Z_GK_KAM->setText(QString::number(Zgk_kam,'f',1));
    return 0;

}

void MainWindow::on_CalcGeoToGK_clicked()
{

    /*Расчет коордиант в проекции ГК ориентира */
//    ui->lineEdit_X_GK ->setText(QString::number(00.00));
//    ui->lineEdit_Y_GK ->setText(QString::number(00.00));
//    ui->lineEdit_Z_GK ->setText(QString::number(00.00));
    B = ui->lineEdit_B->text().toDouble();
    L = ui->lineEdit_L->text().toDouble();
    H = ui->lineEdit_H->text().toDouble();
    if (B == 0.0 || B_kam ==0.0)
    {
        ui->label_Attention->setStyleSheet("color: rgb(255, 0, 0)");
        ui->label_Attention->setText(trUtf8("Отсутствуют геодезические координаты!"));
        return;
    }
    else

     RezCalc = gauss(B,L,H,&Xgk,&Ygk, &Zgk);
    if (RezCalc == 2)
    {
        ui->lineEdit_B->setStyleSheet("color: rgb(255, 0, 0)");
        ui->lineEdit_B->setText(trUtf8("|B| > 90"));

    }
    if (RezCalc == 3)
    {
        ui->lineEdit_L->setStyleSheet("color: rgb(255, 0, 0)");
        ui->lineEdit_L->setText(trUtf8("|L| > 180"));

    }
    if (RezCalc == 2 || RezCalc == 3)
    {
        ui->label_Attention->setStyleSheet("color: rgb(255, 0, 0)");
        ui->label_Attention->setText(trUtf8("Гео координаты вне существующего диапазона!"));
        return;
    }

    if ( CalcGeoToGK_KAM () == 1)
    {
        ui->label_Attention->setStyleSheet("color: rgb(255, 0, 0)");
        ui->label_Attention->setText(trUtf8("Гео координаты вне существующего диапазона!"));
        return;
    }
    ui->label_Attention->setStyleSheet("color: rgb(0, 0, 0)");
    ui->label_Attention->setText(trUtf8("Рассчет координат в проекции ГК произведен!"));
    ui->lineEdit_X_GK->setStyleSheet("color: rgb(0, 0, 0)");
    ui->lineEdit_X_GK ->setText(QString::number(Xgk, 'f', 1));
    ui->lineEdit_Y_GK->setStyleSheet("color: rgb(0, 0, 0)");
    ui->lineEdit_Y_GK ->setText(QString::number(Ygk, 'f', 1));
    ui->lineEdit_Z_GK->setStyleSheet("color: rgb(0, 0, 0)");
    ui->lineEdit_Z_GK->setText(QString::number(Zgk,'f',1));
}

void MainWindow::CalcGKtoGeo_KAM()

/*Расчет геодезических координат Камеры*/
{
//    ui->lineEdit_B_KAM ->setText(QString::number(00.0000000));
//    ui->lineEdit_L_KAM ->setText(QString::number(00.0000000));
//    ui->lineEdit_H_KAM ->setText(QString::number(00.0000000));
    Xgk_kam = ui->lineEdit_X_GK_KAM->text().toDouble();
    Ygk_kam = ui->lineEdit_Y_GK_KAM->text().toDouble();
    Zgk_kam = ui->lineEdit_Z_GK_KAM->text().toDouble();
    Gauss_Geo(Xgk_kam, Ygk_kam, Zgk_kam, &B_kam, &L_kam, &H_kam);
    ui->lineEdit_B_KAM->setStyleSheet("color: rgb(0, 0, 0)");
    ui->lineEdit_B_KAM ->setText(QString::number(B_kam, 'f',7));
    ui->lineEdit_L_KAM->setStyleSheet("color: rgb(0, 0, 0)");
    ui->lineEdit_L_KAM ->setText(QString::number(L_kam, 'f',7));
    ui->lineEdit_H_KAM->setStyleSheet("color: rgb(0, 0, 0)");
    ui->lineEdit_H_KAM ->setText(QString::number(H_kam, 'f',1));
}



void MainWindow::on_CalcGKtoGeo_clicked()

/*Расчет геодезических координат ориентира*/
{
    CalcGKtoGeo_KAM();
//    ui->lineEdit_B ->setText(QString::number(00.0000000));
//    ui->lineEdit_L ->setText(QString::number(00.0000000));
//    ui->lineEdit_H ->setText(QString::number(00.0000000));
    Xgk = ui->lineEdit_X_GK->text().toDouble();
    Ygk = ui->lineEdit_Y_GK->text().toDouble();
    Zgk = ui->lineEdit_Z_GK->text().toDouble();
    if (Xgk == 0.0 || Xgk_kam ==0.0)
    {
        ui->label_Attention->setStyleSheet("color: rgb(255, 0, 0)");
        ui->label_Attention->setText(trUtf8("Отсутствуют координаты в проекции ГК!"));
        return;
    }
    else
    {
        ui->label_Attention->setStyleSheet("color: rgb(0, 0, 0)");
        ui->label_Attention->setText(trUtf8("Рассчет геодезических координат произведен!"));
    }
        Gauss_Geo(Xgk, Ygk, Zgk, &B, &L, &H);
    ui->lineEdit_B->setStyleSheet("color: rgb(0, 0, 0)");
    ui->lineEdit_B ->setText(QString::number(B, 'f',7));
    ui->lineEdit_L->setStyleSheet("color: rgb(0, 0, 0)");
    ui->lineEdit_L ->setText(QString::number(L, 'f',7));
    ui->lineEdit_H->setStyleSheet("color: rgb(0, 0, 0)");
    ui->lineEdit_H ->setText(QString::number(H, 'f',1));
}



void MainWindow::on_CalcSfer_clicked()
{
    Xgk = ui->lineEdit_X_GK->text().toDouble();
    Ygk = ui->lineEdit_Y_GK->text().toDouble();
    Zgk = ui->lineEdit_Z_GK->text().toDouble();
    Xgk_kam = ui->lineEdit_X_GK_KAM->text().toDouble();
    Ygk_kam = ui->lineEdit_Y_GK_KAM->text().toDouble();
    Zgk_kam = ui->lineEdit_Z_GK_KAM->text().toDouble();
    if (Xgk == 0.0 || Xgk_kam ==0.0)
    {
        ui->label_Attention->setStyleSheet("color: rgb(255, 0, 0)");
        ui->label_Attention->setText(trUtf8("Отсутствуют координаты в проекции ГК!"));
        return;
    }

    else
    {
            /*Расчет дальности и азимута ориентира относительно УТ (Камеры)*/
        RezCalc = CalcDist(Xgk,Ygk, Zgk, Xgk_kam, Ygk_kam, Zgk_kam, &r, &b, &e);
        if (RezCalc == 1)
        {
            ui->label_Attention->setStyleSheet("color: rgb(255, 0, 0)");
            ui->label_Attention->setText(trUtf8("№ зоны ГК вне сущеcтвующего диапазона!"));
            return;
        };

   }

    ui->label_Attention->setStyleSheet("color: rgb(0, 0, 0)");
    ui->label_Attention->setText(trUtf8("Рассчет сферических координат произведен!"));
    ui->lineEdit_b_or->setText(QString::number(b, 'f',3));
    ui->lineEdit_e_or->setText(QString::number(e, 'f',3));
    ui->lineEdit_r_or->setText(QString::number(r, 'f',1));

  }

void MainWindow::on_CalcMPTSKi_clicked()
{
   b = ui->lineEdit_b_or->text().toDouble();
   e = ui->lineEdit_e_or->text().toDouble();
   r = ui->lineEdit_r_or->text().toDouble();
   if (r==0.0)
   {
       ui->label_Attention->setStyleSheet("color: rgb(255, 0, 0)");
       ui->label_Attention->setText(trUtf8("Отсутствуют сферические коордианты!"));
       return;
   }
   CalcMPTSKi(r,b,e,&x,&y,&z);
   ui->lineEdit_x_or->setText(QString::number(x, 'f',3));
   ui->lineEdit_y_or->setText(QString::number(y, 'f',3));
   ui->lineEdit_z_or->setText(QString::number(z, 'f',1));
   ui->label_Attention->setStyleSheet("color: rgb(0, 0, 0)");
   ui->label_Attention->setText(trUtf8("Рассчет координат МПТСК произведен!"));
}

//void MainWindow::on_CalcKamGK_clicked()
//{
//    Xgk_prl = ui->lineEdit_X_GK_PRL->text().toDouble();
//     Ygk_prl = ui->lineEdit_Y_GK_PRL->text().toDouble();
//      Zgk_prl = ui->lineEdit_Z_GK_PRL->text().toDouble();
//        B_prl = ui->lineEdit_B_PRL->text().toDouble();
//   x_kam_prl = ui->lineEdit_X_kam_prl->text().toDouble();
//     y_kam_prl = ui->lineEdit_Y_kam_prl->text().toDouble();
//       z_kam_prl = ui->lineEdit_Z_kam_prl->text().toDouble();

//       CalcGEOKAM( Xgk_prl, Ygk_prl, Zgk_prl, B_prl,
//                       x_kam_prl, y_kam_prl, z_kam_prl,
//                       &Xgk_kam, &Ygk_kam, &Zgk_kam, &B_kam,&L_kam,&H_kam);
//       ui->lineEdit_X_GK_KAM ->setText(QString::number(Xgk_kam, 'f', 1));
//       ui->lineEdit_Y_GK_KAM ->setText(QString::number(Ygk_kam, 'f', 1));
//       ui->lineEdit_Z_GK_KAM->setText(QString::number(Zgk_kam,'f',1));
//       ui->lineEdit_B_KAM->setStyleSheet("color: rgb(0, 0, 0)");
//       ui->lineEdit_B_KAM ->setText(QString::number(B_kam, 'f',7));
//       ui->lineEdit_L_KAM->setStyleSheet("color: rgb(0, 0, 0)");
//       ui->lineEdit_L_KAM ->setText(QString::number(L_kam, 'f',7));
//       ui->lineEdit_H_KAM->setStyleSheet("color: rgb(0, 0, 0)");
//       ui->lineEdit_H_KAM ->setText(QString::number(H_kam, 'f',1));

//}

void MainWindow::on_CalcCOIR_clicked()
{
     WidjetKOIR* pWidjetKOIR = new WidjetKOIR();
     pWidjetKOIR->show();
}
