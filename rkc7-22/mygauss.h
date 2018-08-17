#ifndef MYGAUSS_H
#define MYGAUSS_H

#include <QDialog>
#include <QWidget>
#include "qcustomplot.h"

namespace Ui {
class myGauss;
}

class myGauss : public QDialog
{
    Q_OBJECT

public:
    explicit myGauss(QWidget *parent = 0);
    ~myGauss();

    void addMyTitle(QString myGraphName);
    void addMyGauss2Graphs(QPointF &myGauss, QString myGraphName, QColor myColor);
    void addMyLabels(QString myXaxeLabel, QString myYaxeLabel);
    QCPAbstractPlottable * mySelectedPlottable;

private slots:
    void titleDoubleClick(QMouseEvent *event, QCPPlotTitle *title);
    void axisLabelDoubleClick(QCPAxis* axis, QCPAxis::SelectablePart part);
    void legendDoubleClick(QCPLegend* legend, QCPAbstractLegendItem* item);
    void selectionChanged();
    void mousePress();
    void mouseWheel();
    // void addRandomGraph();
    void removeSelectedGraph();
    void removeAllGraphs();
    void contextMenuRequest(QPoint pos);
    void moveLegend();
    // void graphClicked(QCPAbstractPlottable *plottable);

private:
    Ui::myGauss *ui;
    double myEps;
};

#endif // MYGAUSS_H
