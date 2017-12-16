#include "calckoir.h"
#include "ui_calckoir.h"

CALCKOIR::CALCKOIR(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CALCKOIR)
{
    ui->setupUi(this);
}

CALCKOIR::~CALCKOIR()
{
    delete ui;
}
