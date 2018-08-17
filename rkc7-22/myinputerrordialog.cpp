#include "myinputerrordialog.h"
#include "ui_myinputerrordialog.h"

myInputErrorDialog::myInputErrorDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::myInputErrorDialog)
{
    ui->setupUi(this);
    connect(ui->pushButton_NotDoubleError, SIGNAL( clicked() ), this, SLOT(close()) );
}

myInputErrorDialog::~myInputErrorDialog()
{
    delete ui;
}

void myInputErrorDialog::mySetText(QString &text )
{
    // QString str=QString(text) ;
    ui->textEdit_Error->setPlainText( text );
            //_Warning->setPlainText( text );
}
