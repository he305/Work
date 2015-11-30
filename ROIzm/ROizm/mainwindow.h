#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include <QDebug>

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
    double proizv(double);
    double proizv2(double);
    double velocity;
    double time;
    double R;
};

#endif // MAINWINDOW_H
