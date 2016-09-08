#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "mnk.h"

#include <QMainWindow>
#include <QLineEdit>
#include <QString>
#include <fstream>

#include <iostream>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_nEdit_textChanged(const QString &arg1);

    void on_mnk_button_clicked();

    void on_outbaseButton_clicked();

    void on_inbaseButton_clicked();

private:
    Ui::MainWindow *ui;
    QLineEdit **xLine;
    QLineEdit **yLine;
    QLineEdit **zLine;
    QLineEdit **sLine;
    QLineEdit **resultLine;


    double *x;
    double *y;
    double *z;
    double *w;

    double *results;

    int size;
    int prevSize;
};

#endif // MAINWINDOW_H
