#ifndef MYINPUTERRORDIALOG_H
#define MYINPUTERRORDIALOG_H

#include <QDialog>

namespace Ui {
class myInputErrorDialog;
}

class myInputErrorDialog : public QDialog
{
    Q_OBJECT

public:
    explicit myInputErrorDialog(QWidget *parent = 0);
    ~myInputErrorDialog();

    void mySetText(QString &text);
private:
    Ui::myInputErrorDialog *ui;
};

#endif // MYINPUTERRORDIALOG_H
