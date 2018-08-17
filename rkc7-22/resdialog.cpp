#include "resdialog.h"
#include "ui_resdialog.h"

ResDialog::ResDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ResDialog)
{
    ui->setupUi(this);
}

ResDialog::~ResDialog()
{
    delete ui;
}

void ResDialog::mySetText(QString &text )
{
    ui->textEdit_Res->setPlainText( text );
}
