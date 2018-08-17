#include "myinputwarningdialog.h"
#include "ui_myinputwarningdialog.h"

myInputWarningDialog::myInputWarningDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::myInputWarningDialog)
{
    ui->setupUi(this);
}

myInputWarningDialog::~myInputWarningDialog()
{
    delete ui;
}

void myInputWarningDialog::mySetText(QString &text )
{
    // QString str=QString(text) ;
    ui->textEdit_Warning->setPlainText( text );
            //_Warning->setPlainText( text );
}
