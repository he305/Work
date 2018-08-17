#include "myplot.h"
#include "ui_myplot.h"

myPlot::myPlot(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::myPlot)
{
    // srand(QDateTime::currentDateTime().toTime_t());
    ui->setupUi(this);
    myEps=1.0e-6;


    ui->myPlotWidget->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes |
                                    QCP::iSelectLegend | QCP::iSelectPlottables);
    ui->myPlotWidget->xAxis->setRange(-8, 8);
    ui->myPlotWidget->yAxis->setRange(-5, 5);
    ui->myPlotWidget->axisRect()->setupFullAxesBox();

//    ui->myPlotWidget->plotLayout()->insertRow(0);
//    ui->myPlotWidget->plotLayout()->addElement(0, 0, new QCPPlotTitle(ui->myPlotWidget, "VH Пространство скорость - высота (км/ч , км) "));

//    ui->myPlotWidget->xAxis->setLabel("V Скорость (км/ч) ");
//    ui->myPlotWidget->yAxis->setLabel("H Высота (км) ");
    ui->myPlotWidget->legend->setVisible(true);
    QFont legendFont = font();
    legendFont.setPointSize(10);
    ui->myPlotWidget->legend->setFont(legendFont);
    ui->myPlotWidget->legend->setSelectedFont(legendFont);
    ui->myPlotWidget->legend->setSelectableParts(QCPLegend::spItems); // legend box shall not be selectable, only legend items

//    addRandomGraph();
//    addRandomGraph();
//    addRandomGraph();
//    addRandomGraph();

    // connect slot that ties some axis selections together (especially opposite axes):
    connect(ui->myPlotWidget, SIGNAL(selectionChangedByUser()), this, SLOT(selectionChanged()));
    // connect slots that takes care that when an axis is selected, only that direction can be dragged and zoomed:

//    connect(ui->myPlotWidget, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(mousePress()));
//    if( ui->checkBox_MovePoints->isChecked() ) ui->checkBox_MovePoints->toggle();

    connect(ui->myPlotWidget, SIGNAL(mouseWheel(QWheelEvent*)), this, SLOT(mouseWheel()));

    connect(ui->myPlotWidget, SIGNAL(mouseMove(QMouseEvent*)), this, SLOT(onMouseMove(QMouseEvent*)));
    // ui->myPlotWidget->setMouseTracking(false);

    // make bottom and left axes transfer their ranges to top and right axes:
    connect(ui->myPlotWidget->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->myPlotWidget->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->myPlotWidget->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->myPlotWidget->yAxis2, SLOT(setRange(QCPRange)));

    // connect some interaction slots:
    connect(ui->myPlotWidget, SIGNAL(titleDoubleClick(QMouseEvent*,QCPPlotTitle*)), this, SLOT(titleDoubleClick(QMouseEvent*,QCPPlotTitle*)));
    connect(ui->myPlotWidget, SIGNAL(axisDoubleClick(QCPAxis*,QCPAxis::SelectablePart,QMouseEvent*)), this, SLOT(axisLabelDoubleClick(QCPAxis*,QCPAxis::SelectablePart)));
    connect(ui->myPlotWidget, SIGNAL(legendDoubleClick(QCPLegend*,QCPAbstractLegendItem*,QMouseEvent*)), this, SLOT(legendDoubleClick(QCPLegend*,QCPAbstractLegendItem*)));

    // connect slot that shows a message in the status bar when a graph is clicked:
    connect(ui->myPlotWidget, SIGNAL(plottableClick(QCPAbstractPlottable*,QMouseEvent*)), this, SLOT(graphClicked(QCPAbstractPlottable*)));

    // setup policy and connect slot for context menu popup:
    ui->myPlotWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->myPlotWidget, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(contextMenuRequest(QPoint)));
}

//myPlot::myPlot(QString myTitle, QWidget *parent = 0)
//{
//    myPlot(parent);
//    ui->myPlotWidget->plotLayout()->insertRow(0);
//    ui->myPlotWidget->plotLayout()->addElement(0, 0, new QCPPlotTitle(ui->myPlotWidget, myTitle));
//}

myPlot::~myPlot()
{
    delete ui;
}

void myPlot::addRandomGraph()
{
  int n = 50; // number of points in graph
  double xScale = (rand()/(double)RAND_MAX + 0.5)*2;
  double yScale = (rand()/(double)RAND_MAX + 0.5)*2;
  double xOffset = (rand()/(double)RAND_MAX - 0.5)*4;
  double yOffset = (rand()/(double)RAND_MAX - 0.5)*5;
  double r1 = (rand()/(double)RAND_MAX - 0.5)*2;
  double r2 = (rand()/(double)RAND_MAX - 0.5)*2;
  double r3 = (rand()/(double)RAND_MAX - 0.5)*2;
  double r4 = (rand()/(double)RAND_MAX - 0.5)*2;
  QVector<double> x(n), y(n);
  for (int i=0; i<n; i++)
  {
    x[i] = (i/(double)n-0.5)*10.0*xScale + xOffset;
    y[i] = (qSin(x[i]*r1*5)*qSin(qCos(x[i]*r2)*r4*3)+r3*qCos(qSin(x[i])*r4*2))*yScale + yOffset;
  }

  ui->myPlotWidget->addGraph();
  ui->myPlotWidget->graph()->setName(QString("New graph %1").arg(ui->myPlotWidget->graphCount()-1));
  ui->myPlotWidget->graph()->setData(x, y);
  ui->myPlotWidget->graph()->setLineStyle((QCPGraph::LineStyle)(rand()%5+1));
  if (rand()%100 > 75)
    ui->myPlotWidget->graph()->setScatterStyle(QCPScatterStyle((QCPScatterStyle::ScatterShape)(rand()%9+1)));
  QPen graphPen;
  graphPen.setColor(QColor(rand()%245+10, rand()%245+10, rand()%245+10));
  graphPen.setWidthF(rand()/(double)RAND_MAX*2+1);
  ui->myPlotWidget->graph()->setPen(graphPen);
  ui->myPlotWidget->replot();
}

void myPlot::titleDoubleClick(QMouseEvent* event, QCPPlotTitle* title)
{
  Q_UNUSED(event)
  // Set the plot title by double clicking on it
  bool ok;
  QString newTitle = QInputDialog::getText(this, "QCustomPlot example", "New plot title:", QLineEdit::Normal, title->text(), &ok);
  if (ok)
  {
    title->setText(newTitle);
    ui->myPlotWidget->replot();
  }
}

void myPlot::axisLabelDoubleClick(QCPAxis *axis, QCPAxis::SelectablePart part)
{
  // Set an axis label by double clicking on it
  if (part == QCPAxis::spAxisLabel) // only react when the actual axis label is clicked, not tick label or axis backbone
  {
    bool ok;
    QString newLabel = QInputDialog::getText(this, "QCustomPlot example", "New axis label:", QLineEdit::Normal, axis->label(), &ok);
    if (ok)
    {
      axis->setLabel(newLabel);
      ui->myPlotWidget->replot();
    }
  }
}

void myPlot::legendDoubleClick(QCPLegend *legend, QCPAbstractLegendItem *item)
{
  // Rename a graph by double clicking on its legend item
  Q_UNUSED(legend)
  if (item) // only react if item was clicked (user could have clicked on border padding of legend where there is no item, then item is 0)
  {
    QCPPlottableLegendItem *plItem = qobject_cast<QCPPlottableLegendItem*>(item);
    bool ok;
    QString newName = QInputDialog::getText(this, "QCustomPlot example", "New graph name:", QLineEdit::Normal, plItem->plottable()->name(), &ok);
    if (ok)
    {
      plItem->plottable()->setName(newName);
      ui->myPlotWidget->replot();
    }
  }
}

void myPlot::selectionChanged()
{
    // QString str;
    /*
   normally, axis base line, axis tick labels and axis labels are selectable separately, but we want
   the user only to be able to select the axis as a whole, so we tie the selected states of the tick labels
   and the axis base line together. However, the axis label shall be selectable individually.

   The selection state of the left and right axes shall be synchronized as well as the state of the
   bottom and top axes.

   Further, we want to synchronize the selection of the graphs with the selection state of the respective
   legend item belonging to that graph. So the user can select a graph by either clicking on the graph itself
   or on its legend item.
  */

    // make top and bottom axes be selected synchronously, and handle axis and tick labels as one selectable object:
    if (ui->myPlotWidget->xAxis->selectedParts().testFlag(QCPAxis::spAxis) || ui->myPlotWidget->xAxis->selectedParts().testFlag(QCPAxis::spTickLabels) ||
            ui->myPlotWidget->xAxis2->selectedParts().testFlag(QCPAxis::spAxis) || ui->myPlotWidget->xAxis2->selectedParts().testFlag(QCPAxis::spTickLabels))
    {
        ui->myPlotWidget->xAxis2->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
        ui->myPlotWidget->xAxis->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
    }
    // make left and right axes be selected synchronously, and handle axis and tick labels as one selectable object:
    if (ui->myPlotWidget->yAxis->selectedParts().testFlag(QCPAxis::spAxis) || ui->myPlotWidget->yAxis->selectedParts().testFlag(QCPAxis::spTickLabels) ||
            ui->myPlotWidget->yAxis2->selectedParts().testFlag(QCPAxis::spAxis) || ui->myPlotWidget->yAxis2->selectedParts().testFlag(QCPAxis::spTickLabels))
    {
        ui->myPlotWidget->yAxis2->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
        ui->myPlotWidget->yAxis->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
    }

    // synchronize selection of graphs with selection of corresponding legend items:

    // for (int i=0; i<ui->customPlot->graphCount(); ++i)
    for (int i=0; i<ui->myPlotWidget->plottableCount(); ++i)
    {
      QCPAbstractPlottable *plottable = ui->myPlotWidget->plottable(i);
      QCPPlottableLegendItem *item = ui->myPlotWidget->legend->itemWithPlottable(plottable);
      if (item->selected() || plottable->selected())
      {
        item->setSelected(true);
        plottable->setSelected(true);
        // ui->lineEdit_CurveName->setText(plottable->name());
      }
    }
}
//    for (int i=0; i<ui->myPlotWidget->graphCount(); ++i)
//    {
//        QCPAbstractPlottable * plottable = ui->myPlotWidget->selectedPlottables().first();
//        // qDebug() << "void myPlot::selectionChanged()  == QCPAbstractPlottable * plottable = => " << plottable->name();
//        // QCPCurve *graph = (QCPCurve *)plottable;
//        QCPPlottableLegendItem *item = ui->myPlotWidget->legend->itemWithPlottable(plottable);
        // qDebug() << "void myPlot::selectionChanged()  == QCPPlottableLegendItem *item = => " << item->plottable()->name();
//        if (plottable->selected())
//        {
//            // qDebug() << "void myPlot::selectionChanged() =>  if (plottable->selected())  => " << plottable->name();
//            item->setSelected(true);
//        }
            // plottable->setSelected(true);
//        if (item->selected())
//        {
//            // qDebug() << "void myPlot::selectionChanged() =>  if (item->selected()) => " << plottable->name();
//            plottable->setSelected(true);
//        }

//    }
// }

void myPlot::mousePress()
{
  // if an axis is selected, only allow the direction of that axis to be dragged
  // if no axis is selected, both directions may be dragged

  if (ui->myPlotWidget->xAxis->selectedParts().testFlag(QCPAxis::spAxis))
    ui->myPlotWidget->axisRect()->setRangeDrag(ui->myPlotWidget->xAxis->orientation());
  else if (ui->myPlotWidget->yAxis->selectedParts().testFlag(QCPAxis::spAxis))
    ui->myPlotWidget->axisRect()->setRangeDrag(ui->myPlotWidget->yAxis->orientation());
  else
    ui->myPlotWidget->axisRect()->setRangeDrag(Qt::Horizontal|Qt::Vertical);
}

void myPlot::mouseWheel()
{
  // if an axis is selected, only allow the direction of that axis to be zoomed
  // if no axis is selected, both directions may be zoomed

  if (ui->myPlotWidget->xAxis->selectedParts().testFlag(QCPAxis::spAxis))
    ui->myPlotWidget->axisRect()->setRangeZoom(ui->myPlotWidget->xAxis->orientation());
  else if (ui->myPlotWidget->yAxis->selectedParts().testFlag(QCPAxis::spAxis))
    ui->myPlotWidget->axisRect()->setRangeZoom(ui->myPlotWidget->yAxis->orientation());
  else
    ui->myPlotWidget->axisRect()->setRangeZoom(Qt::Horizontal|Qt::Vertical);
}

void myPlot::removeSelectedGraph()
{
  if (ui->myPlotWidget->selectedGraphs().size() > 0)
  {
    ui->myPlotWidget->removeGraph(ui->myPlotWidget->selectedGraphs().first());
    ui->myPlotWidget->replot();
  }
}

void myPlot::removeAllGraphs()
{
  ui->myPlotWidget->clearGraphs();
  ui->myPlotWidget->replot();
}

void myPlot::contextMenuRequest(QPoint pos)
{
  QMenu *menu = new QMenu(this);
  menu->setAttribute(Qt::WA_DeleteOnClose);

  if (ui->myPlotWidget->legend->selectTest(pos, false) >= 0) // context menu on legend requested
  {
    menu->addAction("Move to top left", this, SLOT(moveLegend()))->setData((int)(Qt::AlignTop|Qt::AlignLeft));
    menu->addAction("Move to top center", this, SLOT(moveLegend()))->setData((int)(Qt::AlignTop|Qt::AlignHCenter));
    menu->addAction("Move to top right", this, SLOT(moveLegend()))->setData((int)(Qt::AlignTop|Qt::AlignRight));
    menu->addAction("Move to bottom right", this, SLOT(moveLegend()))->setData((int)(Qt::AlignBottom|Qt::AlignRight));
    menu->addAction("Move to bottom left", this, SLOT(moveLegend()))->setData((int)(Qt::AlignBottom|Qt::AlignLeft));
  } else  // general context menu on graphs requested
  {
    menu->addAction("Add random graph", this, SLOT(addRandomGraph()));
    if (ui->myPlotWidget->selectedGraphs().size() > 0)
      menu->addAction("Remove selected graph", this, SLOT(removeSelectedGraph()));
    if (ui->myPlotWidget->graphCount() > 0)
      menu->addAction("Remove all graphs", this, SLOT(removeAllGraphs()));
  }

  menu->popup(ui->myPlotWidget->mapToGlobal(pos));
}

void myPlot::moveLegend()
{
  if (QAction* contextAction = qobject_cast<QAction*>(sender())) // make sure this slot is really called by a context menu action, so it carries the data we need
  {
    bool ok;
    int dataInt = contextAction->data().toInt(&ok);
    if (ok)
    {
      ui->myPlotWidget->axisRect()->insetLayout()->setInsetAlignment(0, (Qt::Alignment)dataInt);
      ui->myPlotWidget->replot();
    }
  }
}

void myPlot::graphClicked(QCPAbstractPlottable *plottable)
{
    QString str = plottable->name();
    mySelectedPlottable=plottable;
    // QCPPlottableLegendItem * item = ui->myPlotWidget->legend->itemWithPlottable(plottable);
    // qDebug() << "QString str = plottable->name() = " << str;
    QCPCurve *curve = (QCPCurve *) mySelectedPlottable; // (QCPCurve *) qobject_cast<QCPCurve*>(mySelectedPlottable);
    if (curve)
    {
        myCurveData = curve->data();

//        qDebug() << "myCurveData->size() = " << myCurveData->size();
    }

    // QString("Clicked on graph '%1'.").arg(plottable->name());
    // ui->statusBar->showMessage(str, 2000);
    // ui->lineEdit_CurveName->setText(str);

    ui->myPlotWidget->setMouseTracking(true);
    // ui->statusBar->showMessage(QString("Clicked on graph '%1'.").arg(plottable->name()), 1000);
}

void myPlot::addMyPoly2Graphs(QPolygonF &myPPoly0, QPolygonF &myPPoly1, QString myGraphName, QColor myColor)
{
    QString str;
    QPolygonF myPlotPoly0 = QPolygonF(myPPoly0);
    QPolygonF myPlotPoly1 = QPolygonF(myPPoly1);
    int n = myPlotPoly0.size();
    if(myPlotPoly0[0] != myPlotPoly0[n-1])  myPlotPoly0 << myPlotPoly0[0];
    // qDebug() << myPlotPoly0;
    if(myPlotPoly1[0] != myPlotPoly1[n-1]) myPlotPoly1 << myPlotPoly1[0];
    n = myPlotPoly0.size();
    // qDebug() << myPlotPoly1;
    QVector<double> I(n), x0(n), y0(n), x1(n), y1(n);
    for (int i=0; i<n; i++)
    {
        I[i]=double(i);
        x0[i] = myPlotPoly0[i].x();
        y0[i] = myPlotPoly0[i].y();
        x1[i] = myPlotPoly1[i].x();
        y1[i] = myPlotPoly1[i].y();
    }

    QCPCurve *newCurve0 = new QCPCurve(ui->myPlotWidget->xAxis, ui->myPlotWidget->yAxis); // add it to the customPlot with QCustomPlot::addPlottable:
    ui->myPlotWidget->addPlottable(newCurve0); // and then modify the properties of the newly created plottable, e.g.:
    str = myGraphName;
    str.append("_0");
    newCurve0->setName(str);
    newCurve0->setData(I, x0, y0);
    newCurve0->setLineStyle(QCPCurve::lsLine);
    QCPScatterStyle myScatter0;
    myScatter0.setShape(QCPScatterStyle::ssCircle);
    myScatter0.setSize(10);
    newCurve0->setScatterStyle(myScatter0);
    QPen graphPen0;
    graphPen0.setColor(myColor);
    graphPen0.setWidthF(4.0);
    newCurve0->setPen(graphPen0);
    // newCurve->rescaleAxes(); //replot();
    newCurve0->addToLegend();

    QCPCurve *newCurve1 = new QCPCurve(ui->myPlotWidget->xAxis, ui->myPlotWidget->yAxis); // add it to the customPlot with QCustomPlot::addPlottable:
    ui->myPlotWidget->addPlottable(newCurve1); // and then modify the properties of the newly created plottable, e.g.:
    str = myGraphName;
    str.append("_1");
    newCurve1->setName(str);
    newCurve1->setData(I, x1, y1);
    newCurve1->setLineStyle(QCPCurve::lsLine);
    QCPScatterStyle myScatter1;
    myScatter1.setShape(QCPScatterStyle::ssCircle);
    myScatter1.setSize(5);
    newCurve1->setScatterStyle(myScatter1);
    QPen graphPen1;
    graphPen1.setColor(myColor);
    graphPen1.setWidthF(2.0);
    newCurve1->setPen(graphPen1);

//    ui->myPlotWidget->plotLayout()->insertRow(0);
//    ui->myPlotWidget->plotLayout()->addElement(0, 0, new QCPPlotTitle(ui->myPlotWidget, "VH Пространство скорость - высота (м/с , м) "));

//    ui->myPlotWidget->xAxis->setLabel("V Скорость (м/с) ");
//    ui->myPlotWidget->yAxis->setLabel("H Высота (м) ");
    ui->myPlotWidget->rescaleAxes();


//    QCPRange myRmin, myRmax;
//    newCurve->
}

void myPlot::addMyPoint2Graphs(QPointF &myPPoint, QString myGraphName, QColor myColor)
{
    QString str=myGraphName;
//    QPolygonF myPlotPoly0 = QPolygonF(myPPoint);
//    QPolygonF myPlotPoly1 = QPolygonF(myPPoly1);
//    int n = myPlotPoly0.size();
//    if(myPlotPoly0[0] != myPlotPoly0[n-1])  myPlotPoly0 << myPlotPoly0[0];
    // qDebug() << myPlotPoly0;
//    if(myPlotPoly1[0] != myPlotPoly1[n-1]) myPlotPoly1 << myPlotPoly1[0];
//    n = myPlotPoly0.size();
    // qDebug() << myPlotPoly1;
    QVector<double> x0(1), y0(1);
    x0[0] = myPPoint.x();
    y0[0] = myPPoint.y();

    QCPCurve *newCurve0 = new QCPCurve(ui->myPlotWidget->xAxis, ui->myPlotWidget->yAxis); // add it to the customPlot with QCustomPlot::addPlottable:
    ui->myPlotWidget->addPlottable(newCurve0); // and then modify the properties of the newly created plottable, e.g.:
//    str = myGraphName;
//    str.append("_0");
    newCurve0->setName(str);
    newCurve0->setData(x0, y0);
    newCurve0->setLineStyle(QCPCurve::lsNone);
    QCPScatterStyle myScatter0;
    myScatter0.setShape(QCPScatterStyle::ssCrossCircle);
    myScatter0.setSize(20);
    newCurve0->setScatterStyle(myScatter0);
    QPen graphPen0;
    graphPen0.setColor(myColor);
    graphPen0.setWidthF(3.0);
    newCurve0->setPen(graphPen0);
    // newCurve->rescaleAxes(); //replot();
    newCurve0->addToLegend();

    ui->myPlotWidget->rescaleAxes();
}

void myPlot::addMyTitle(QString myGraphName)
{
    ui->myPlotWidget->plotLayout()->insertRow(0);
    ui->myPlotWidget->plotLayout()->addElement(0, 0, new QCPPlotTitle(ui->myPlotWidget, myGraphName));
}

void myPlot::addMyLabels(QString myXaxeLabel, QString myYaxeLabel)
{
    ui->myPlotWidget->xAxis->setLabel(myXaxeLabel);
    ui->myPlotWidget->yAxis->setLabel(myYaxeLabel);
//    ui->myPlotWidget->plotLayout()->insertRow(0);
//    ui->myPlotWidget->plotLayout()->addElement(0, 0, new QCPPlotTitle(ui->myPlotWidget, myGraphName));
}

void myPlot::addMyGauss2Graphs(QPointF &myGauss, QString myGraphName, QColor myColor)
{
    int n = 101;
    double t1, t2, t3;
    double x0 = myGauss.x() - 3.0 * myGauss.y();
    double dx = 6.0 * myGauss.y() / double(n-1) ;

    QVector<double> x(n), y(n);
    t1 = 2.0*myGauss.y()*myGauss.y();
    t2 = myGauss.y()*sqrt(2*3.141592653);
    for (int i=0; i<n; i++)
    {
        x[i] = x0+dx*double(i);
        t3 = (x[i]-myGauss.x())*(x[i]-myGauss.x());
        y[i] = exp(-t3/t1)/t2;
    }

    ui->myPlotWidget->addGraph();
    ui->myPlotWidget->graph()->setName(myGraphName);
    ui->myPlotWidget->graph()->setData(x, y);
    ui->myPlotWidget->graph()->setLineStyle(QCPGraph::lsLine);

//    QCPScatterStyle myScatter;
//    myScatter.setShape(QCPScatterStyle::ssCircle);
//    myScatter.setPen(myColor);
//    myScatter.setBrush(myColor);
//    myScatter.setSize(10);

    QPen graphPen;
    graphPen.setColor(myColor);
    graphPen.setWidthF(2.0);
    ui->myPlotWidget->graph()->setPen(graphPen);
    ui->myPlotWidget->graph()->addToLegend();
    ui->myPlotWidget->rescaleAxes(); // replot();
}

void myPlot::onMouseMove(QMouseEvent *event)
{
    double x, y;

//    QCPCurve *curve = (QCPCurve *) mySelectedPlottable;
//    // QCPCurve *curve = qobject_cast<QCPCurve *>( ui->myPlotWidget->selectedPlottables().first());
//    QCPCurveDataMap * myCurveData = curve->data();
//    QCPCurveDataMapIterator iData;
    QString str;
    if( ui->myPlotWidget->axisRect()->rect().contains( event->pos() ) && ui->myPlotWidget->hasMouseTracking() )
    {
        x = this->ui->myPlotWidget->xAxis->pixelToCoord(event->pos().x()); // this->
        y = this->ui->myPlotWidget->yAxis->pixelToCoord(event->pos().y());
        str=QString("%1").arg( x, 0, 'f', 0); // QString str;
        ui->lineEdit_pX->setText(str); // lineEdit_pX
        str=QString("%1").arg( y, 0, 'f', 2);
        ui->lineEdit_pY->setText(str); // lineEdit_pY

        // qDebug() << x << "&" << y;
    }

    if( ui->myPlotWidget->selectedPlottables().size() )
    {
//        // qDebug() << "ui->myPlotWidget->selectedPlottables().size() = " << ui->myPlotWidget->selectedPlottables().size();
//        str = mySelectedPlottable->name();
//        // qDebug() << "mySelectedPlottable->name() = " << str;
//        ui->lineEdit_CurveName->setText(str);
    }
}

//void myPlot::on_checkBox_MovePoints_clicked()
//{
//    if( ui->checkBox_MovePoints->isChecked() )
//    {
//        disconnect(ui->myPlotWidget, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(mousePress()));
//        connect(ui->myPlotWidget, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(mousePress()));
//    }
//    else
//    {
//        disconnect(ui->myPlotWidget, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(mousePress()));
//        connect(ui->myPlotWidget, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(mousePress()));
//    }
//}
