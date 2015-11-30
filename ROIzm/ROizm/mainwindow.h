#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include <QDebug>
#include "funcmaker.h"

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
    void on_refreshButton_clicked();

private:
    Ui::MainWindow *ui;
    double velocity;
    double time;
    double R;
    double interval;

    FuncMaker* fm = nullptr;
};

#endif // MAINWINDOW_H
