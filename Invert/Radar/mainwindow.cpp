#include "mainwindow.h"
#include "qmessagebox"
#include "ui_mainwindow.h"
#include "invertedmatrixwindow.h"
#include <invert.h>
#include <ctime>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    setFixedSize(765, 484);
    ui->label_det->setVisible(false);
    init();
}

void MainWindow::init(){
    ui->size_line->setMaxLength(2);
    size = ui->size_line->text().toInt();
    prevSize = size;

    QFont font("Times", 10, QFont::Bold);

    line = new QLineEdit **[size];
    matrix = new double *[size];
    for (int i = 0; i < size; i++){
        matrix[i] = new double[size];
        line[i] = new QLineEdit *[size];
        for (int j = 0; j < size; j++){
            line[i][j] = new QLineEdit(this);
            line[i][j]->setFont(font);
            line[i][j]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            line[i][j]->setAlignment(Qt::AlignHCenter);
            ui->gridMatrix->addWidget(line[i][j], i, j);
        }
    }


    ui->size_line->setFont(font);

    ui->method_box->addItem("Random");
    ui->method_box->addItem("Hilbert");
    ui->method_box->addItem("Input");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_button_freezeMatrix_clicked()
{
    if (matrix != nullptr){
        for (int i = 0; i < prevSize; i++){
            delete[] matrix[i];
        }
        delete[] matrix;
    }

    matrix = new double *[size];
    for (int i = 0; i < size; i++){
        matrix[i] = new double[size];
        for (int j = 0; j < size; j++){
            matrix[i][j] = line[i][j]->text().toDouble();
        }
    }
    ui->button_invert->setEnabled(true);
    prevSize = size;
}

void MainWindow::on_button_invert_clicked()
{
    ui->label_det->setVisible(false);

    Invert *inv = new Invert(size);
    inv->invert(matrix);
    double **inverted = inv->getInvertedMatrix();

    QString str = inv->getMatrixType();

    if (inv->getDet(matrix, size) == 0){
        ui->label_det->setVisible(true);
    }
    else{
    InvertedMatrixWindow *form = new InvertedMatrixWindow(0, inverted, size, str);
    form->show();
    }

    for (int i = 0; i < size; i++){
        delete[] inverted[i];
    }
    delete[] inverted;
    inverted = nullptr;

    delete inv;

    ui->button_invert->setEnabled(false);
}

void MainWindow::on_size_line_textChanged(const QString &arg1)
{
    ui->label_det->setVisible(false);
    srand(time(NULL));

    if (ui->gridMatrix->layout() != NULL )
    {
        QLayoutItem* item;
        while ((item = ui->gridMatrix->layout()->takeAt(0))!= NULL)
        {
            delete item->widget();
            delete item;
        }
    }

    size = arg1.toInt();
    QFont font("Times", 10, QFont::Bold);

    line = new QLineEdit **[size];
    for (int i = 0; i < size; i++){
        line[i] = new QLineEdit *[size];
        for (int j = 0; j < size; j++){
            line[i][j] = new QLineEdit(this);
            line[i][j]->setFont(font);
            line[i][j]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            line[i][j]->setAlignment(Qt::AlignHCenter);

            if (ui->method_box->currentText() == "Hilbert"){
                line[i][j]->setText(QString::number(1.0/(i+j+1)));
            }

            else if(ui->method_box->currentText() == "Random"){
                line[i][j]->setText(QString::number(rand()%10+1));
            }

            else if(ui->method_box->currentText() == "Input"){
                line[i][j]->setText(QString::number(0));
            }

            ui->gridMatrix->addWidget(line[i][j], i, j);
        }
    }

}

void MainWindow::on_method_box_currentTextChanged(const QString &arg1)
{
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            if (arg1 == "Hilbert"){
                line[i][j]->setText(QString::number(1.0/(i+j+1)));
            }

            else if(arg1 == "Random"){
                line[i][j]->setText(QString::number(rand()%10+1));
            }

            else if(arg1 == "Input"){
                line[i][j]->setText(QString::number(0));
            }
        }
    }
}
