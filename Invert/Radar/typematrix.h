#ifndef TYPEMATRIX_H
#define TYPEMATRIX_H

#include <QDialog>

namespace Ui {
class Typematrix;
}

class Typematrix : public QDialog
{
    Q_OBJECT

public:
    explicit Typematrix(QWidget *parent = 0, QString str = "");
    ~Typematrix();

private:
    Ui::Typematrix *ui;
};

#endif // TYPEMATRIX_H
