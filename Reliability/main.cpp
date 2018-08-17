#include "mainwindow.h"
#include <QApplication>
#include <iostream>
#include <mnk.h>
#include <memory>
#include <QVector>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    std::vector<double> x = {1, 2, 3, 4, 5};
    std::vector<double> y = {3, 4, 6, 8, 10};
    int size = 5;

    std::unique_ptr<MNK> mnk(new MNK(x, y, size));

    //std::unique_ptr<MNK> mnk(x, y, size);
    auto answer = mnk->Calculate();

    for (int i = 0; i < answer.size(); i++)
    {
        std::cout << answer[i] << std::endl;
    }


    w.show();

    return a.exec();
}
