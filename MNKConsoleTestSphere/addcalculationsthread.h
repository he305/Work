#include <QThread>
#include <consoletest.h>
#include <time.h>

#ifndef ADDCALCULATIONSTHREAD_H
#define ADDCALCULATIONSTHREAD_H


class AddCalculationsThread : public QThread
{
public:
    void run();

private:
    void sleep(unsigned long s);
    std::vector<double>* x;
    std::vector<double>* y;
    std::vector<double>* z;
};


#endif // ADDCALCULATIONSTHREAD_H
