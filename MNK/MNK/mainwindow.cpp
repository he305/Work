#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->setFixedSize(477, 461);
    ui->setupUi(this);
    ui->nEdit->setAlignment(Qt::AlignRight);

    xLine = nullptr;
    yLine = nullptr;
    sLine = nullptr;

    x = nullptr;
    y = nullptr;
    w = nullptr;
    ui->inbaseButton->setEnabled(false);
    ui->outbaseButton->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_nEdit_textChanged(const QString &arg1)
{
    if (ui->inbaseButton->isEnabled())
        ui->inbaseButton->setEnabled(false);

    if (ui->xLayout->layout() != NULL )
    {
        QLayoutItem* item;

        /*==========Очиста предыдущих значений и виджетов======*/
        while ((item = ui->xLayout->layout()->takeAt(0))!= NULL)
        {
            delete item->widget();
            delete item;
        }

        while ((item = ui->yLayout->layout()->takeAt(0))!= NULL)
        {
            delete item->widget();
            delete item;
        }


        while ((item = ui->sLayout->layout()->takeAt(0))!= NULL)
        {
            delete item->widget();
            delete item;
        }
        delete[] xLine;
        delete[] yLine;
        delete[] sLine;
    }
    /*==========================================================*/

    size = arg1.toInt();

    xLine = new QLineEdit *[size];
    yLine = new QLineEdit *[size];
    sLine = new QLineEdit *[size];
    for (int i = 0; i < size; i++)
    {
        xLine[i] = new QLineEdit();
        yLine[i] = new QLineEdit();
        sLine[i] = new QLineEdit();

        xLine[i]->setAlignment(Qt::AlignCenter);
        yLine[i]->setAlignment(Qt::AlignCenter);
        sLine[i]->setAlignment(Qt::AlignCenter);

        xLine[i]->setText(QString::number(0));
        yLine[i]->setText(QString::number(0));
        sLine[i]->setText(QString::number(1));

        ui->xLayout->addWidget(xLine[i]);
        ui->yLayout->addWidget(yLine[i]);
        ui->sLayout->addWidget(sLine[i]);
    }
}

void MainWindow::on_mnk_button_clicked()
{
    if (x != nullptr || y != nullptr || w != nullptr)
    {
        delete[] x;
        delete[] y;
        delete[] w;
    }

    x = new double[size];
    y = new double[size];
    w = new double[size];

    for (int i = 0; i < size; i++)
    {
        w[i] = sLine[i]->text().toDouble();
        x[i] = xLine[i]->text().toDouble();
        y[i] = yLine[i]->text().toDouble();
    }

    MNK *mnk = new MNK(x, y, w, size);
    a = mnk->getA();
    b = mnk->getB();
    ui->aXAnswer->setText(QString::number(a));
    ui->bXAnswer->setText(QString::number(b));
    ui->inbaseButton->setEnabled(true);
}

void MainWindow::on_outbaseButton_clicked()
{
    std::ifstream dataBase;
    std::ofstream log;
    dataBase.open("C:/Users/Admin/Documents/Work/Work/MNK/data.csv");
    //log.open("D:\\Dropbox\\log.txt");
    std::string text;
    dataBase >> text;
    while(!dataBase.eof())
    {
        dataBase >> text;
        log << text;
    }
    log.close();
    dataBase.close();
}

void MainWindow::on_inbaseButton_clicked()
{
    if (x != nullptr || y != nullptr)
    {
        delete[] x;
        delete[] y;
    }

    x = new double[size];
    y = new double[size];
    for (int i = 0; i < size; i++)
    {
        x[i] = xLine[i]->text().toDouble();
        y[i] = yLine[i]->text().toDouble();
    }

    std::ofstream dataBase;
    dataBase.open("C:\\Users\\Admin\\Desktop\\data.csv");
    dataBase << "X;Y;W;A;B" << std::endl;

    for (int i = 0; i < size; i++)
    {
        dataBase << x[i] << ";" << y[i] << ";" << w[i];
        if (i == 0)
        {
            dataBase << ";" << a << ";" << b;
        }

        dataBase << std::endl;
    }

    dataBase.close();
}
