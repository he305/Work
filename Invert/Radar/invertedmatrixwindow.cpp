#include "invertedmatrixwindow.h"
#include "ui_invertedmatrixwindow.h"
#include <QLineEdit>

InvertedMatrixWindow::InvertedMatrixWindow(QWidget *parent,
                                           double **inverted,
                                           int size,
                                           QString str) :
    QWidget(parent),
    ui(new Ui::InvertedMatrixWindow)
{
    ui->setupUi(this);

    setFixedSize(641, 468);
    move(500, 100);
    QFont font("Times", 10, QFont::Bold);

    ui->label_matrix_type->setAlignment(Qt::AlignHCenter);
    ui->label_matrix_type->setText(str);

    QLineEdit ***line = new QLineEdit **[size];
    for (int i = 0; i < size; i++){
        line[i] = new QLineEdit *[size];
        for (int j = 0; j < size; j++){
            line[i][j] = new QLineEdit(this);
            line[i][j]->setFont(font);
            line[i][j]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            line[i][j]->setAlignment(Qt::AlignHCenter);
            line[i][j]->setText(QString::number(inverted[i][j]));
            ui->grid_matrix->addWidget(line[i][j], i, j);
        }
    }
}

InvertedMatrixWindow::~InvertedMatrixWindow()
{
    delete ui;
}
