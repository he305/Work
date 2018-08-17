#ifndef MYINPUTWARNINGDIALOG_H
#define MYINPUTWARNINGDIALOG_H

#include <QDialog>

namespace Ui {
class myInputWarningDialog;
}

class myInputWarningDialog : public QDialog
{
    Q_OBJECT

public:
    explicit myInputWarningDialog(QWidget *parent = 0);
    ~myInputWarningDialog();

    void mySetText(QString &text);
private:
    Ui::myInputWarningDialog *ui;
};

#endif // MYINPUTWARNINGDIALOG_H
