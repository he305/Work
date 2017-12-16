/********************************************************************************
** Form generated from reading UI file 'widjetkoir.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDJETKOIR_H
#define UI_WIDJETKOIR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WidjetKOIR
{
public:
    QTabWidget *formationTagetOPU;
    QWidget *FormationTagetOPU;
    QLabel *label;
    QLineEdit *ceilX;
    QLineEdit *ceilY;
    QLabel *label_2;
    QLineEdit *ceilZ;
    QLabel *label_3;
    QLineEdit *Vxceil;
    QLabel *label_4;
    QLineEdit *Vyceil;
    QLabel *label_5;
    QLineEdit *BopuCur;
    QLabel *label_6;
    QLineEdit *Bopu;
    QLineEdit *Eopu;
    QLabel *label_7;
    QLabel *label_8;
    QPushButton *RunCalcformationTaget;
    QLineEdit *Bceil;
    QLabel *label_9;
    QLabel *label_10;
    QLineEdit *dT;
    QWidget *tab_2;
    QWidget *formationResult;

    void setupUi(QWidget *WidjetKOIR)
    {
        if (WidjetKOIR->objectName().isEmpty())
            WidjetKOIR->setObjectName(QStringLiteral("WidjetKOIR"));
        WidjetKOIR->resize(600, 496);
        formationTagetOPU = new QTabWidget(WidjetKOIR);
        formationTagetOPU->setObjectName(QStringLiteral("formationTagetOPU"));
        formationTagetOPU->setGeometry(QRect(40, 30, 571, 451));
        FormationTagetOPU = new QWidget();
        FormationTagetOPU->setObjectName(QStringLiteral("FormationTagetOPU"));
        label = new QLabel(FormationTagetOPU);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 20, 46, 13));
        ceilX = new QLineEdit(FormationTagetOPU);
        ceilX->setObjectName(QStringLiteral("ceilX"));
        ceilX->setGeometry(QRect(50, 20, 61, 20));
        ceilY = new QLineEdit(FormationTagetOPU);
        ceilY->setObjectName(QStringLiteral("ceilY"));
        ceilY->setGeometry(QRect(150, 20, 61, 20));
        label_2 = new QLabel(FormationTagetOPU);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(120, 20, 46, 13));
        ceilZ = new QLineEdit(FormationTagetOPU);
        ceilZ->setObjectName(QStringLiteral("ceilZ"));
        ceilZ->setGeometry(QRect(250, 20, 61, 20));
        label_3 = new QLabel(FormationTagetOPU);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(220, 20, 46, 13));
        Vxceil = new QLineEdit(FormationTagetOPU);
        Vxceil->setObjectName(QStringLiteral("Vxceil"));
        Vxceil->setGeometry(QRect(350, 20, 61, 20));
        label_4 = new QLabel(FormationTagetOPU);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(320, 20, 31, 16));
        Vyceil = new QLineEdit(FormationTagetOPU);
        Vyceil->setObjectName(QStringLiteral("Vyceil"));
        Vyceil->setGeometry(QRect(460, 20, 61, 20));
        label_5 = new QLabel(FormationTagetOPU);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(430, 20, 41, 20));
        BopuCur = new QLineEdit(FormationTagetOPU);
        BopuCur->setObjectName(QStringLiteral("BopuCur"));
        BopuCur->setGeometry(QRect(70, 60, 61, 20));
        label_6 = new QLabel(FormationTagetOPU);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(20, 60, 46, 13));
        Bopu = new QLineEdit(FormationTagetOPU);
        Bopu->setObjectName(QStringLiteral("Bopu"));
        Bopu->setGeometry(QRect(50, 100, 61, 20));
        Eopu = new QLineEdit(FormationTagetOPU);
        Eopu->setObjectName(QStringLiteral("Eopu"));
        Eopu->setGeometry(QRect(150, 100, 61, 20));
        label_7 = new QLabel(FormationTagetOPU);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(20, 100, 46, 13));
        label_8 = new QLabel(FormationTagetOPU);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(120, 100, 46, 13));
        RunCalcformationTaget = new QPushButton(FormationTagetOPU);
        RunCalcformationTaget->setObjectName(QStringLiteral("RunCalcformationTaget"));
        RunCalcformationTaget->setGeometry(QRect(20, 190, 75, 23));
        Bceil = new QLineEdit(FormationTagetOPU);
        Bceil->setObjectName(QStringLiteral("Bceil"));
        Bceil->setGeometry(QRect(50, 130, 61, 20));
        label_9 = new QLabel(FormationTagetOPU);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(120, 133, 46, 13));
        label_10 = new QLabel(FormationTagetOPU);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(20, 133, 46, 13));
        dT = new QLineEdit(FormationTagetOPU);
        dT->setObjectName(QStringLiteral("dT"));
        dT->setGeometry(QRect(150, 130, 61, 20));
        formationTagetOPU->addTab(FormationTagetOPU, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        formationTagetOPU->addTab(tab_2, QString());
        formationResult = new QWidget();
        formationResult->setObjectName(QStringLiteral("formationResult"));
        formationTagetOPU->addTab(formationResult, QString());

        retranslateUi(WidjetKOIR);

        formationTagetOPU->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(WidjetKOIR);
    } // setupUi

    void retranslateUi(QWidget *WidjetKOIR)
    {
        WidjetKOIR->setWindowTitle(QApplication::translate("WidjetKOIR", "Form", Q_NULLPTR));
        label->setText(QApplication::translate("WidjetKOIR", "ceilX", Q_NULLPTR));
        label_2->setText(QApplication::translate("WidjetKOIR", "ceilY", Q_NULLPTR));
        label_3->setText(QApplication::translate("WidjetKOIR", "ceilZ", Q_NULLPTR));
        label_4->setText(QApplication::translate("WidjetKOIR", "VelX", Q_NULLPTR));
        label_5->setText(QApplication::translate("WidjetKOIR", "VelY", Q_NULLPTR));
        label_6->setText(QApplication::translate("WidjetKOIR", "BopuCur", Q_NULLPTR));
        label_7->setText(QApplication::translate("WidjetKOIR", "Bopu", Q_NULLPTR));
        label_8->setText(QApplication::translate("WidjetKOIR", "Eopu", Q_NULLPTR));
        RunCalcformationTaget->setText(QApplication::translate("WidjetKOIR", "Calc", Q_NULLPTR));
        Bceil->setText(QString());
        label_9->setText(QApplication::translate("WidjetKOIR", "dTl", Q_NULLPTR));
        label_10->setText(QApplication::translate("WidjetKOIR", "Bceil", Q_NULLPTR));
        dT->setText(QString());
        formationTagetOPU->setTabText(formationTagetOPU->indexOf(FormationTagetOPU), QApplication::translate("WidjetKOIR", "FormationTagetOPU", Q_NULLPTR));
        formationTagetOPU->setTabText(formationTagetOPU->indexOf(tab_2), QApplication::translate("WidjetKOIR", "Tab 2", Q_NULLPTR));
        formationTagetOPU->setTabText(formationTagetOPU->indexOf(formationResult), QApplication::translate("WidjetKOIR", "formationResult", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class WidjetKOIR: public Ui_WidjetKOIR {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDJETKOIR_H
