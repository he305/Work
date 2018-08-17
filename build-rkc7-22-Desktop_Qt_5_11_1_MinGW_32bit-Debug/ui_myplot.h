/********************************************************************************
** Form generated from reading UI file 'myplot.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYPLOT_H
#define UI_MYPLOT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_myPlot
{
public:
    QVBoxLayout *verticalLayout;
    QFrame *frame_p;
    QHBoxLayout *horizontalLayout_2;
    QCustomPlot *myPlotWidget;
    QFrame *frame_p2;
    QWidget *widget;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_p;
    QLineEdit *lineEdit_pX;
    QHBoxLayout *horizontalLayout;
    QLabel *label_p2;
    QLineEdit *lineEdit_pY;

    void setupUi(QWidget *myPlot)
    {
        if (myPlot->objectName().isEmpty())
            myPlot->setObjectName(QStringLiteral("myPlot"));
        myPlot->resize(1000, 800);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(myPlot->sizePolicy().hasHeightForWidth());
        myPlot->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(myPlot);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        frame_p = new QFrame(myPlot);
        frame_p->setObjectName(QStringLiteral("frame_p"));
        sizePolicy.setHeightForWidth(frame_p->sizePolicy().hasHeightForWidth());
        frame_p->setSizePolicy(sizePolicy);
        frame_p->setFrameShape(QFrame::StyledPanel);
        frame_p->setFrameShadow(QFrame::Raised);
        horizontalLayout_2 = new QHBoxLayout(frame_p);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        myPlotWidget = new QCustomPlot(frame_p);
        myPlotWidget->setObjectName(QStringLiteral("myPlotWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::MinimumExpanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(myPlotWidget->sizePolicy().hasHeightForWidth());
        myPlotWidget->setSizePolicy(sizePolicy1);
        myPlotWidget->setMinimumSize(QSize(400, 300));

        horizontalLayout_2->addWidget(myPlotWidget);


        verticalLayout->addWidget(frame_p);

        frame_p2 = new QFrame(myPlot);
        frame_p2->setObjectName(QStringLiteral("frame_p2"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(frame_p2->sizePolicy().hasHeightForWidth());
        frame_p2->setSizePolicy(sizePolicy2);
        frame_p2->setMinimumSize(QSize(0, 55));
        frame_p2->setFrameShape(QFrame::StyledPanel);
        frame_p2->setFrameShadow(QFrame::Raised);
        widget = new QWidget(frame_p2);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(830, 0, 141, 52));
        verticalLayout_2 = new QVBoxLayout(widget);
        verticalLayout_2->setSpacing(1);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_p = new QLabel(widget);
        label_p->setObjectName(QStringLiteral("label_p"));

        horizontalLayout_3->addWidget(label_p);

        lineEdit_pX = new QLineEdit(widget);
        lineEdit_pX->setObjectName(QStringLiteral("lineEdit_pX"));
        QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(lineEdit_pX->sizePolicy().hasHeightForWidth());
        lineEdit_pX->setSizePolicy(sizePolicy3);
        lineEdit_pX->setAlignment(Qt::AlignCenter);

        horizontalLayout_3->addWidget(lineEdit_pX);


        verticalLayout_2->addLayout(horizontalLayout_3);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_p2 = new QLabel(widget);
        label_p2->setObjectName(QStringLiteral("label_p2"));
        QSizePolicy sizePolicy4(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(label_p2->sizePolicy().hasHeightForWidth());
        label_p2->setSizePolicy(sizePolicy4);

        horizontalLayout->addWidget(label_p2);

        lineEdit_pY = new QLineEdit(widget);
        lineEdit_pY->setObjectName(QStringLiteral("lineEdit_pY"));
        sizePolicy3.setHeightForWidth(lineEdit_pY->sizePolicy().hasHeightForWidth());
        lineEdit_pY->setSizePolicy(sizePolicy3);
        lineEdit_pY->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(lineEdit_pY);


        verticalLayout_2->addLayout(horizontalLayout);


        verticalLayout->addWidget(frame_p2);


        retranslateUi(myPlot);

        QMetaObject::connectSlotsByName(myPlot);
    } // setupUi

    void retranslateUi(QWidget *myPlot)
    {
        myPlot->setWindowTitle(QApplication::translate("myPlot", "Form", nullptr));
        label_p->setText(QApplication::translate("myPlot", "V, \320\272\320\274/\321\207 (X) : ", nullptr));
        lineEdit_pX->setText(QString());
        label_p2->setText(QApplication::translate("myPlot", "H, \320\272\320\274  (Y) : ", nullptr));
    } // retranslateUi

};

namespace Ui {
    class myPlot: public Ui_myPlot {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYPLOT_H
