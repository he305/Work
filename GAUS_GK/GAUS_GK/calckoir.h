#ifndef CALCKOIR_H
#define CALCKOIR_H

#include <QWidget>

namespace Ui {
class CALCKOIR;
}

class CALCKOIR : public QWidget
{
    Q_OBJECT

public:
    explicit CALCKOIR(QWidget *parent = 0);
    ~CALCKOIR();

private:
    Ui::CALCKOIR *ui;
};

#endif // CALCKOIR_H
