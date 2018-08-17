#ifndef MYPLOT_H
#define MYPLOT_H

#include <QWidget>
#include "qcustomplot.h"

namespace Ui {
class myPlot;
}

class myPlot : public QWidget
{
    Q_OBJECT

public:
    explicit myPlot(QWidget *parent = 0); // explicit
    // myPlot(QString myTitle, QWidget *parent = 0);
    ~myPlot();

    void addMyPoly2Graphs(QPolygonF &myPlotPoly0, QPolygonF &myPlotPoly1, QString myGraphName, QColor myColor);
    void addMyPoint2Graphs(QPointF &myPPoint, QString myGraphName, QColor myColor);
    void addMyTitle(QString myGraphName);
    void addMyGauss2Graphs(QPointF &myGauss, QString myGraphName, QColor myColor);
    void addMyLabels(QString myXaxeLabel, QString myYaxeLabel);
    QCPAbstractPlottable * mySelectedPlottable;
    QCPCurveDataMap * myCurveData;

private slots:
    void titleDoubleClick(QMouseEvent *event, QCPPlotTitle *title);
    void axisLabelDoubleClick(QCPAxis* axis, QCPAxis::SelectablePart part);
    void legendDoubleClick(QCPLegend* legend, QCPAbstractLegendItem* item);
    void selectionChanged();
    void mousePress();
    void mouseWheel();
    void addRandomGraph();
    void removeSelectedGraph();
    void removeAllGraphs();
    void contextMenuRequest(QPoint pos);
    void moveLegend();
    void graphClicked(QCPAbstractPlottable *plottable);

    void onMouseMove(QMouseEvent *event);

//    void on_checkBox_MovePoints_clicked();

private:
    Ui::myPlot *ui;
    double myEps;
};

#endif // MYPLOT_H
