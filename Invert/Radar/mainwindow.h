#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>

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
    void on_button_invert_clicked();

    void on_button_freezeMatrix_clicked();

    void on_size_line_textChanged(const QString &arg1);

    void on_method_box_currentTextChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
    QLineEdit ***line;
    void init();
    double **matrix;
    int size;
    int prevSize;
};

#endif // MAINWINDOW_H
