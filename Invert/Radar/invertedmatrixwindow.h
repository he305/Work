#ifndef INVERTEDMATRIXWINDOW_H
#define INVERTEDMATRIXWINDOW_H

#include <QWidget>
#include <QString>

namespace Ui {
class InvertedMatrixWindow;
}

class InvertedMatrixWindow : public QWidget
{
    Q_OBJECT

public:
    explicit InvertedMatrixWindow(QWidget *parent = 0,
                                  double **inverted = 0,
                                  int size = 0,
                                  QString = "");
    ~InvertedMatrixWindow();

private:
    Ui::InvertedMatrixWindow *ui;
};

#endif // INVERTEDMATRIXWINDOW_H
