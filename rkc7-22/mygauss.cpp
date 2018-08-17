#include "mygauss.h"
#include "ui_mygauss.h"

myGauss::myGauss(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::myGauss)
{
    ui->setupUi(this);
    myEps=1.0e-6;


    ui->myGaussWidget->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes |
                                    QCP::iSelectLegend | QCP::iSelectPlottables);
    ui->myGaussWidget->xAxis->setRange(-8, 8);
    ui->myGaussWidget->yAxis->setRange(-5, 5);
    ui->myGaussWidget->axisRect()->setupFullAxesBox();

    // ui->myGaussWidget->plotLayout()->insertRow(0);
    // ui->myGaussWidget->plotLayout()->addElement(0, 0, new QCPPlotTitle(ui->myGaussWidget, "Interaction Example"));

    // ui->myGaussWidget->xAxis->setLabel("x Axis");
    // ui->myGaussWidget->yAxis->setLabel("y Axis");
    ui->myGaussWidget->legend->setVisible(true);
    QFont legendFont = font();
    legendFont.setPointSize(10);
    ui->myGaussWidget->legend->setFont(legendFont);
    ui->myGaussWidget->legend->setSelectedFont(legendFont);
    ui->myGaussWidget->legend->setSelectableParts(QCPLegend::spItems); // legend box shall not be selectable, only legend items

    // connect slot that ties some axis selections together (especially opposite axes):
    connect(ui->myGaussWidget, SIGNAL(selectionChangedByUser()), this, SLOT(selectionChanged()));
    // connect slots that takes care that when an axis is selected, only that direction can be dragged and zoomed:
    connect(ui->myGaussWidget, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(mousePress()));
    connect(ui->myGaussWidget, SIGNAL(mouseWheel(QWheelEvent*)), this, SLOT(mouseWheel()));

    // make bottom and left axes transfer their ranges to top and right axes:
    connect(ui->myGaussWidget->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->myGaussWidget->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->myGaussWidget->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->myGaussWidget->yAxis2, SLOT(setRange(QCPRange)));

    // connect some interaction slots:
    connect(ui->myGaussWidget, SIGNAL(titleDoubleClick(QMouseEvent*,QCPPlotTitle*)), this, SLOT(titleDoubleClick(QMouseEvent*,QCPPlotTitle*)));
    connect(ui->myGaussWidget, SIGNAL(axisDoubleClick(QCPAxis*,QCPAxis::SelectablePart,QMouseEvent*)), this, SLOT(axisLabelDoubleClick(QCPAxis*,QCPAxis::SelectablePart)));
    connect(ui->myGaussWidget, SIGNAL(legendDoubleClick(QCPLegend*,QCPAbstractLegendItem*,QMouseEvent*)), this, SLOT(legendDoubleClick(QCPLegend*,QCPAbstractLegendItem*)));

    // connect slot that shows a message in the status bar when a graph is clicked:
    // connect(ui->myGaussWidget, SIGNAL(plottableClick(QCPAbstractPlottable*,QMouseEvent*)), this, SLOT(graphClicked(QCPAbstractPlottable*)));

    // setup policy and connect slot for context menu popup:
    ui->myGaussWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->myGaussWidget, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(contextMenuRequest(QPoint)));
}

myGauss::~myGauss()
{
    delete ui;
}

void myGauss::addMyGauss2Graphs(QPointF &myGaussPt, QString myGraphName, QColor myColor)
{
    int n = 101;
    double t1, t2, t3;
    double x0 = myGaussPt.x() - 3.0 * myGaussPt.y();
    double dx = 6.0 * myGaussPt.y() / double(n-1) ;

    QVector<double> x(n), y(n);
    t1 = 2.0*myGaussPt.y()*myGaussPt.y();
    t2 = myGaussPt.y()*sqrt(2*3.141592653);
    for (int i=0; i<n; i++)
    {
        x[i] = x0+dx*double(i);
        t3 = (x[i]-myGaussPt.x())*(x[i]-myGaussPt.x());
        y[i] = exp(-t3/t1)/t2;
    }

    ui->myGaussWidget->addGraph();
    ui->myGaussWidget->graph()->setName(myGraphName);
    ui->myGaussWidget->graph()->setData(x, y);
    ui->myGaussWidget->graph()->setLineStyle(QCPGraph::lsLine);

//    QCPScatterStyle myScatter;
//    myScatter.setShape(QCPScatterStyle::ssCircle);
//    myScatter.setPen(myColor);
//    myScatter.setBrush(myColor);
//    myScatter.setSize(10);

    QPen graphPen;
    graphPen.setColor(myColor);
    graphPen.setWidthF(2.0);
    ui->myGaussWidget->graph()->setPen(graphPen);
    ui->myGaussWidget->graph()->addToLegend();
    ui->myGaussWidget->rescaleAxes(); // replot();
}

void myGauss::addMyTitle(QString myGraphName)
{
    ui->myGaussWidget->plotLayout()->insertRow(0);
    ui->myGaussWidget->plotLayout()->addElement(0, 0, new QCPPlotTitle(ui->myGaussWidget, myGraphName));
}

void myGauss::addMyLabels(QString myXaxeLabel, QString myYaxeLabel)
{
    ui->myGaussWidget->xAxis->setLabel(myXaxeLabel);
    ui->myGaussWidget->yAxis->setLabel(myYaxeLabel);
//    ui->myPlotWidget->plotLayout()->insertRow(0);
//    ui->myPlotWidget->plotLayout()->addElement(0, 0, new QCPPlotTitle(ui->myPlotWidget, myGraphName));
}

void myGauss::titleDoubleClick(QMouseEvent* event, QCPPlotTitle* title)
{
  Q_UNUSED(event)
  // Set the plot title by double clicking on it
  bool ok;
  QString newTitle = QInputDialog::getText(this, "QCustomPlot example", "New plot title:", QLineEdit::Normal, title->text(), &ok);
  if (ok)
  {
    title->setText(newTitle);
    ui->myGaussWidget->replot();
  }
}

void myGauss::axisLabelDoubleClick(QCPAxis *axis, QCPAxis::SelectablePart part)
{
  // Set an axis label by double clicking on it
  if (part == QCPAxis::spAxisLabel) // only react when the actual axis label is clicked, not tick label or axis backbone
  {
    bool ok;
    QString newLabel = QInputDialog::getText(this, "QCustomPlot example", "New axis label:", QLineEdit::Normal, axis->label(), &ok);
    if (ok)
    {
      axis->setLabel(newLabel);
      ui->myGaussWidget->replot();
    }
  }
}

void myGauss::legendDoubleClick(QCPLegend *legend, QCPAbstractLegendItem *item)
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
      ui->myGaussWidget->replot();
    }
  }
}

void myGauss::selectionChanged()
{
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
  if (ui->myGaussWidget->xAxis->selectedParts().testFlag(QCPAxis::spAxis) || ui->myGaussWidget->xAxis->selectedParts().testFlag(QCPAxis::spTickLabels) ||
      ui->myGaussWidget->xAxis2->selectedParts().testFlag(QCPAxis::spAxis) || ui->myGaussWidget->xAxis2->selectedParts().testFlag(QCPAxis::spTickLabels))
  {
    ui->myGaussWidget->xAxis2->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
    ui->myGaussWidget->xAxis->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
  }
  // make left and right axes be selected synchronously, and handle axis and tick labels as one selectable object:
  if (ui->myGaussWidget->yAxis->selectedParts().testFlag(QCPAxis::spAxis) || ui->myGaussWidget->yAxis->selectedParts().testFlag(QCPAxis::spTickLabels) ||
      ui->myGaussWidget->yAxis2->selectedParts().testFlag(QCPAxis::spAxis) || ui->myGaussWidget->yAxis2->selectedParts().testFlag(QCPAxis::spTickLabels))
  {
    ui->myGaussWidget->yAxis2->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
    ui->myGaussWidget->yAxis->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
  }

  // synchronize selection of graphs with selection of corresponding legend items:
  for (int i=0; i<ui->myGaussWidget->graphCount(); ++i)
  {
    QCPGraph *graph = ui->myGaussWidget->graph(i);
    QCPPlottableLegendItem *item = ui->myGaussWidget->legend->itemWithPlottable(graph);
    if (item->selected() || graph->selected())
    {
      item->setSelected(true);
      graph->setSelected(true);
    }
  }
}

void myGauss::mousePress()
{
  // if an axis is selected, only allow the direction of that axis to be dragged
  // if no axis is selected, both directions may be dragged

  if (ui->myGaussWidget->xAxis->selectedParts().testFlag(QCPAxis::spAxis))
    ui->myGaussWidget->axisRect()->setRangeDrag(ui->myGaussWidget->xAxis->orientation());
  else if (ui->myGaussWidget->yAxis->selectedParts().testFlag(QCPAxis::spAxis))
    ui->myGaussWidget->axisRect()->setRangeDrag(ui->myGaussWidget->yAxis->orientation());
  else
    ui->myGaussWidget->axisRect()->setRangeDrag(Qt::Horizontal|Qt::Vertical);
}

void myGauss::mouseWheel()
{
  // if an axis is selected, only allow the direction of that axis to be zoomed
  // if no axis is selected, both directions may be zoomed

  if (ui->myGaussWidget->xAxis->selectedParts().testFlag(QCPAxis::spAxis))
    ui->myGaussWidget->axisRect()->setRangeZoom(ui->myGaussWidget->xAxis->orientation());
  else if (ui->myGaussWidget->yAxis->selectedParts().testFlag(QCPAxis::spAxis))
    ui->myGaussWidget->axisRect()->setRangeZoom(ui->myGaussWidget->yAxis->orientation());
  else
    ui->myGaussWidget->axisRect()->setRangeZoom(Qt::Horizontal|Qt::Vertical);
}

void myGauss::removeSelectedGraph()
{
  if (ui->myGaussWidget->selectedGraphs().size() > 0)
  {
    ui->myGaussWidget->removeGraph(ui->myGaussWidget->selectedGraphs().first());
    ui->myGaussWidget->replot();
  }
}

void myGauss::removeAllGraphs()
{
  ui->myGaussWidget->clearGraphs();
  ui->myGaussWidget->replot();
}

void myGauss::contextMenuRequest(QPoint pos)
{
  QMenu *menu = new QMenu(this);
  menu->setAttribute(Qt::WA_DeleteOnClose);

  if (ui->myGaussWidget->legend->selectTest(pos, false) >= 0) // context menu on legend requested
  {
    menu->addAction("Move to top left", this, SLOT(moveLegend()))->setData((int)(Qt::AlignTop|Qt::AlignLeft));
    menu->addAction("Move to top center", this, SLOT(moveLegend()))->setData((int)(Qt::AlignTop|Qt::AlignHCenter));
    menu->addAction("Move to top right", this, SLOT(moveLegend()))->setData((int)(Qt::AlignTop|Qt::AlignRight));
    menu->addAction("Move to bottom right", this, SLOT(moveLegend()))->setData((int)(Qt::AlignBottom|Qt::AlignRight));
    menu->addAction("Move to bottom left", this, SLOT(moveLegend()))->setData((int)(Qt::AlignBottom|Qt::AlignLeft));
  } else  // general context menu on graphs requested
  {
    menu->addAction("Add random graph", this, SLOT(addRandomGraph()));
    if (ui->myGaussWidget->selectedGraphs().size() > 0)
      menu->addAction("Remove selected graph", this, SLOT(removeSelectedGraph()));
    if (ui->myGaussWidget->graphCount() > 0)
      menu->addAction("Remove all graphs", this, SLOT(removeAllGraphs()));
  }

  menu->popup(ui->myGaussWidget->mapToGlobal(pos));
}

void myGauss::moveLegend()
{
  if (QAction* contextAction = qobject_cast<QAction*>(sender())) // make sure this slot is really called by a context menu action, so it carries the data we need
  {
    bool ok;
    int dataInt = contextAction->data().toInt(&ok);
    if (ok)
    {
      ui->myGaussWidget->axisRect()->insetLayout()->setInsetAlignment(0, (Qt::Alignment)dataInt);
      ui->myGaussWidget->replot();
    }
  }
}

//void myGauss::graphClicked(QCPAbstractPlottable *plottable)
//{
//    qDebug() << plottable->name();
//  // ui->statusBar->showMessage(QString("Clicked on graph '%1'.").arg(plottable->name()), 1000);
//}
