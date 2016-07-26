#include <iostream>
#include <addcalculationsthread.h>
#include <QApplication>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    AddCalculationsThread solveThread;
    solveThread.start();
    return app.exec();
}
