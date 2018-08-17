/********************************************************************************
** Form generated from reading UI file 'mygauss.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYGAUSS_H
#define UI_MYGAUSS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_myGauss
{
public:
    QHBoxLayout *horizontalLayout;
    QCustomPlot *myGaussWidget;

    void setupUi(QDialog *myGauss)
    {
        if (myGauss->objectName().isEmpty())
            myGauss->setObjectName(QStringLiteral("myGauss"));
        myGauss->resize(800, 600);
        horizontalLayout = new QHBoxLayout(myGauss);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        myGaussWidget = new QCustomPlot(myGauss);
        myGaussWidget->setObjectName(QStringLiteral("myGaussWidget"));

        horizontalLayout->addWidget(myGaussWidget);


        retranslateUi(myGauss);

        QMetaObject::connectSlotsByName(myGauss);
    } // setupUi

    void retranslateUi(QDialog *myGauss)
    {
        myGauss->setWindowTitle(QApplication::translate("myGauss", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class myGauss: public Ui_myGauss {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYGAUSS_H
