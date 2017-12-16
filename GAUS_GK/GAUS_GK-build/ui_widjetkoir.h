/********************************************************************************
** Form generated from reading UI file 'widjetkoir.ui'
**
** Created by: Qt User Interface Compiler version 4.8.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDJETKOIR_H
#define UI_WIDJETKOIR_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QTabWidget>
#include <QtGui/QWidget>

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
            WidjetKOIR->setObjectName(QString::fromUtf8("WidjetKOIR"));
        WidjetKOIR->resize(600, 496);
        formationTagetOPU = new QTabWidget(WidjetKOIR);
        formationTagetOPU->setObjectName(QString::fromUtf8("formationTagetOPU"));
        formationTagetOPU->setGeometry(QRect(40, 30, 571, 451));
        FormationTagetOPU = new QWidget();
        FormationTagetOPU->setObjectName(QString::fromUtf8("FormationTagetOPU"));
        label = new QLabel(FormationTagetOPU);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 20, 46, 13));
        ceilX = new QLineEdit(FormationTagetOPU);
        ceilX->setObjectName(QString::fromUtf8("ceilX"));
        ceilX->setGeometry(QRect(50, 20, 61, 20));
        ceilY = new QLineEdit(FormationTagetOPU);
        ceilY->setObjectName(QString::fromUtf8("ceilY"));
        ceilY->setGeometry(QRect(150, 20, 61, 20));
        label_2 = new QLabel(FormationTagetOPU);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(120, 20, 46, 13));
        ceilZ = new QLineEdit(FormationTagetOPU);
        ceilZ->setObjectName(QString::fromUtf8("ceilZ"));
        ceilZ->setGeometry(QRect(250, 20, 61, 20));
        label_3 = new QLabel(FormationTagetOPU);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(220, 20, 46, 13));
        Vxceil = new QLineEdit(FormationTagetOPU);
        Vxceil->setObjectName(QString::fromUtf8("Vxceil"));
        Vxceil->setGeometry(QRect(350, 20, 61, 20));
        label_4 = new QLabel(FormationTagetOPU);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(320, 20, 31, 16));
        Vyceil = new QLineEdit(FormationTagetOPU);
        Vyceil->setObjectName(QString::fromUtf8("Vyceil"));
        Vyceil->setGeometry(QRect(460, 20, 61, 20));
        label_5 = new QLabel(FormationTagetOPU);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(430, 20, 41, 20));
        BopuCur = new QLineEdit(FormationTagetOPU);
        BopuCur->setObjectName(QString::fromUtf8("BopuCur"));
        BopuCur->setGeometry(QRect(70, 60, 61, 20));
        label_6 = new QLabel(FormationTagetOPU);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(20, 60, 46, 13));
        Bopu = new QLineEdit(FormationTagetOPU);
        Bopu->setObjectName(QString::fromUtf8("Bopu"));
        Bopu->setGeometry(QRect(50, 100, 61, 20));
        Eopu = new QLineEdit(FormationTagetOPU);
        Eopu->setObjectName(QString::fromUtf8("Eopu"));
        Eopu->setGeometry(QRect(150, 100, 61, 20));
        label_7 = new QLabel(FormationTagetOPU);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(20, 100, 46, 13));
        label_8 = new QLabel(FormationTagetOPU);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(120, 100, 46, 13));
        RunCalcformationTaget = new QPushButton(FormationTagetOPU);
        RunCalcformationTaget->setObjectName(QString::fromUtf8("RunCalcformationTaget"));
        RunCalcformationTaget->setGeometry(QRect(20, 190, 75, 23));
        Bceil = new QLineEdit(FormationTagetOPU);
        Bceil->setObjectName(QString::fromUtf8("Bceil"));
        Bceil->setGeometry(QRect(50, 130, 61, 20));
        label_9 = new QLabel(FormationTagetOPU);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(120, 133, 46, 13));
        label_10 = new QLabel(FormationTagetOPU);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(20, 133, 46, 13));
        dT = new QLineEdit(FormationTagetOPU);
        dT->setObjectName(QString::fromUtf8("dT"));
        dT->setGeometry(QRect(150, 130, 61, 20));
        formationTagetOPU->addTab(FormationTagetOPU, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        formationTagetOPU->addTab(tab_2, QString());
        formationResult = new QWidget();
        formationResult->setObjectName(QString::fromUtf8("formationResult"));
        formationTagetOPU->addTab(formationResult, QString());

        retranslateUi(WidjetKOIR);

        formationTagetOPU->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(WidjetKOIR);
    } // setupUi

    void retranslateUi(QWidget *WidjetKOIR)
    {
        WidjetKOIR->setWindowTitle(QApplication::translate("WidjetKOIR", "Form", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("WidjetKOIR", "ceilX", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("WidjetKOIR", "ceilY", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("WidjetKOIR", "ceilZ", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("WidjetKOIR", "VelX", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("WidjetKOIR", "VelY", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("WidjetKOIR", "BopuCur", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("WidjetKOIR", "Bopu", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("WidjetKOIR", "Eopu", 0, QApplication::UnicodeUTF8));
        RunCalcformationTaget->setText(QApplication::translate("WidjetKOIR", "Calc", 0, QApplication::UnicodeUTF8));
        Bceil->setText(QString());
        label_9->setText(QApplication::translate("WidjetKOIR", "dTl", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("WidjetKOIR", "Bceil", 0, QApplication::UnicodeUTF8));
        dT->setText(QString());
        formationTagetOPU->setTabText(formationTagetOPU->indexOf(FormationTagetOPU), QApplication::translate("WidjetKOIR", "FormationTagetOPU", 0, QApplication::UnicodeUTF8));
        formationTagetOPU->setTabText(formationTagetOPU->indexOf(tab_2), QApplication::translate("WidjetKOIR", "Tab 2", 0, QApplication::UnicodeUTF8));
        formationTagetOPU->setTabText(formationTagetOPU->indexOf(formationResult), QApplication::translate("WidjetKOIR", "formationResult", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class WidjetKOIR: public Ui_WidjetKOIR {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDJETKOIR_H
