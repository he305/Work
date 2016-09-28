#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    qDebug() << qApp->applicationDirPath();
    this->setFixedSize(477, 461);
    ui->setupUi(this);
    ui->nEdit->setAlignment(Qt::AlignRight);

    xLine = nullptr;
    yLine = nullptr;
    zLine = nullptr;
    sLine = nullptr;
    resultLine = nullptr;

    x = nullptr;
    y = nullptr;
    z = nullptr;
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
    QString v = arg1;
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

        while ((item = ui->zLayout->layout()->takeAt(0))!= NULL)
        {
            delete item->widget();
            delete item;
        }


        while ((item = ui->sLayout->layout()->takeAt(0))!= NULL)
        {
            delete item->widget();
            delete item;
        }

        while ((item = ui->resLayout->layout()->takeAt(0))!= NULL)
        {
            delete item->widget();
            delete item;
        }

        delete[] xLine;
        delete[] yLine;
        delete[] zLine;
        delete[] sLine;
        delete[] resultLine;
    }
    /*==========================================================*/

    size = ui->nEdit->text().toInt();

    xLine = new QLineEdit *[size];
    yLine = new QLineEdit *[size];
    zLine = new QLineEdit *[size];
    sLine = new QLineEdit *[size];
    for (int i = 0; i < size; i++)
    {
        xLine[i] = new QLineEdit();
        yLine[i] = new QLineEdit();
        zLine[i] = new QLineEdit();
        sLine[i] = new QLineEdit();

        xLine[i]->setAlignment(Qt::AlignCenter);
        yLine[i]->setAlignment(Qt::AlignCenter);
        zLine[i]->setAlignment(Qt::AlignCenter);
        sLine[i]->setAlignment(Qt::AlignCenter);

        xLine[i]->setText(QString::number(0));
        yLine[i]->setText(QString::number(0));
        zLine[i]->setText(QString::number(0));
        sLine[i]->setText(QString::number(1));

        ui->xLayout->addWidget(xLine[i]);
        ui->yLayout->addWidget(yLine[i]);
        ui->zLayout->addWidget(zLine[i]);
        ui->sLayout->addWidget(sLine[i]);
    }
}

void MainWindow::on_mnk_button_clicked()
{

    QLayoutItem* item;
    while ((item = ui->resLayout->layout()->takeAt(0))!= NULL)
    {
        delete item->widget();
        delete item;
    }
    delete[] resultLine;

    if (x != nullptr || y != nullptr || w != nullptr || z != nullptr)
    {
        delete[] x;
        delete[] y;
        delete[] z;
        delete[] w;
    }

    x = new double[size];
    y = new double[size];
    z = new double[size];
    w = new double[size];

    for (int i = 0; i < size; i++)
    {
        w[i] = sLine[i]->text().toDouble();
        x[i] = xLine[i]->text().toDouble();
        y[i] = yLine[i]->text().toDouble();
        z[i] = zLine[i]->text().toDouble();
    }

    int *polynomeSize = new int[2];
    int polNumber = ui->polynomeBox->currentIndex();
    switch(polNumber)
    {
    case 0:
        polynomeSize[0] = 1;
        polynomeSize[1] = 1;
        break;
    case 1:
        polynomeSize[0] = 1;
        polynomeSize[1] = 2;
        break;
    case 2:
        polynomeSize[0] = 2;
        polynomeSize[1] = 1;
        break;
    case 3:
        polynomeSize[0] = 2;
        polynomeSize[1] = 2;
    }

    MNK *mnk = new MNK(x, y, z, w, size, polynomeSize);
    results = mnk->calculate();

    resultLine = new QLineEdit *[3];
    for (int i = 0; i < 3; i++)
    {
        resultLine[i] = new QLineEdit();
        resultLine[i]->setAlignment(Qt::AlignCenter);

        QString resultString = char(i+97) + QString::fromUtf8(" = ") + QString::number(results[i]);
        resultLine[i]->setText(resultString);
        ui->resLayout->addWidget(resultLine[i]);
    }
    ui->inbaseButton->setEnabled(true);
    delete polynomeSize;
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
    QString dataPath = "/../data.csv";
    dataBase.open((qApp->applicationDirPath()+dataPath).toStdString().c_str());

    for (int i = 0; i < size; i++)
    {
        if (i == 0)
        {
            dataBase << "X" << ";" << "Y" << ";" << "Z" << ";" << "W" << std::endl;
        }
        dataBase << x[i] << ";" << y[i] << ";" << z[i] << ";" << w[i];

        dataBase << std::endl;
    }

    dataBase.close();
}
