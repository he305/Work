#include "mainwindow.h"
#include <QApplication>
#include <iostream>
#include <mnk.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    std::vector<double> x = {1, 2, 3, 4, 5};
    std::vector<double> y = {1, 2, 3, 4, 5};
    int size = 5;

    MNK mnk(x, y, size);

    std::vector<double> answer = mnk.Calculate();

    for (int i = 0; i < answer.size(); i++)
    {
        std::cout << answer[i] << std::endl;
    }

    w.show();

    return a.exec();
}
