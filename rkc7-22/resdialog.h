#ifndef RESDIALOG_H
#define RESDIALOG_H

#include <QDialog>

namespace Ui {
class ResDialog;
}

class ResDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ResDialog(QWidget *parent = 0);
    ~ResDialog();
    void mySetText(QString &text );

private:
    Ui::ResDialog *ui;
};

#endif // RESDIALOG_H
