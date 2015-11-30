#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <math.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    on_refreshButton_clicked();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_refreshButton_clicked()
{
    velocity = ui->velEdit->text().toDouble();
    time = ui->timeEdit->text().toDouble();
    R = ui->REdit->text().toDouble();

    double x = velocity*time/R;
    double y = atan(x);
    qDebug() << y;
    qDebug() << proizv(x);
    qDebug() << proizv2(x);
}

double MainWindow::proizv(double x)
{
    return 1/(pow(x, 2) + 1);
}

double MainWindow::proizv2(double x)
{
    return -2*x/(pow((pow(x, 2) + 1), 2));
}
