#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "radspeed.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QList<RadSpeed> *list = new QList<RadSpeed>();
    int a = 3;
    int b = 3;
    int c = 4;
    int d = 5;
    RadSpeed* rd = new RadSpeed(&a, &b, &c, &d);
    list->append(*rd);
    for (int i = 0; i < list->size(); i++)
    {
        qDebug() << *(list->at(i).angle);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
