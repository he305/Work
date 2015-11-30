#include "mainwindow.h"
#include "ui_mainwindow.h"

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
    interval = ui->intervalEdit->text().toDouble();

    double x = velocity*time/R;

    if (fm == nullptr)
    {
        fm = new FuncMaker(x, time, interval);
    }
    else
    {
        fm->refresh(x, time, interval);
    }

    ui->yEdit->setText(QString::number(fm->getY()));
    ui->y1Edit->setText(QString::number(fm->getY1()));
    ui->y2Edit->setText(QString::number(fm->getY2()));
    ui->funcEdit->setText(QString::number(fm->make()));

    fm->db(velocity, R);
}
