/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action_3;
    QAction *action_4;
    QAction *action_5;
    QWidget *centralWidget;
    QLabel *label_7;
    QLineEdit *lineEdit_H;
    QLabel *label_6;
    QLabel *label_2;
    QLineEdit *lineEdit_Z_GK;
    QLabel *label_4;
    QLabel *label_5;
    QLineEdit *lineEdit_B;
    QLineEdit *lineEdit_X_GK;
    QLineEdit *lineEdit_Y_GK;
    QLabel *label_3;
    QLabel *label;
    QPushButton *CalcGeoToGK;
    QPushButton *CalcGKtoGeo;
    QLineEdit *lineEdit_L;
    QLabel *label_8;
    QLineEdit *lineEdit_L_KAM;
    QLineEdit *lineEdit_B_KAM;
    QLineEdit *lineEdit_H_KAM;
    QLabel *label_9;
    QLabel *label_10;
    QLabel *label_11;
    QLabel *label_12;
    QLineEdit *lineEdit_Z_GK_KAM;
    QLineEdit *lineEdit_X_GK_KAM;
    QLineEdit *lineEdit_Y_GK_KAM;
    QLabel *label_13;
    QLineEdit *lineEdit_e_or;
    QLineEdit *lineEdit_r_or;
    QLineEdit *lineEdit_b_or;
    QLabel *label_14;
    QLabel *label_15;
    QLabel *label_16;
    QPushButton *CalcSfer;
    QLabel *label_Attention;
    QPushButton *CalcMPTSKi;
    QLabel *label_17;
    QLabel *label_18;
    QLabel *label_19;
    QLineEdit *lineEdit_y_or;
    QLabel *label_20;
    QLineEdit *lineEdit_z_or;
    QLineEdit *lineEdit_x_or;
    QLabel *label_21;
    QLineEdit *lineEdit_Lat_kmplx;
    QLineEdit *lineEdit_longt_kmplx;
    QLineEdit *lineEdit_Z_kmplx;
    QLabel *label_22;
    QLabel *label_23;
    QLabel *label_24;
    QLineEdit *lineEdit_X_kam_kmplx;
    QLabel *label_25;
    QLineEdit *lineEdit_Y_kam_kmplx;
    QLineEdit *lineEdit_Z_kam_kmplx;
    QLabel *label_26;
    QLabel *label_27;
    QLabel *label_28;
    QPushButton *CalcKamGK;
    QLineEdit *lineEdit_B_kmplx;
    QLabel *label_29;
    QPushButton *CalcCOIR;
    QMenuBar *menuBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(972, 747);
        action_3 = new QAction(MainWindow);
        action_3->setObjectName(QStringLiteral("action_3"));
        action_4 = new QAction(MainWindow);
        action_4->setObjectName(QStringLiteral("action_4"));
        action_5 = new QAction(MainWindow);
        action_5->setObjectName(QStringLiteral("action_5"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(330, 100, 21, 16));
        QFont font;
        font.setPointSize(10);
        label_7->setFont(font);
        lineEdit_H = new QLineEdit(centralWidget);
        lineEdit_H->setObjectName(QStringLiteral("lineEdit_H"));
        lineEdit_H->setGeometry(QRect(650, 70, 113, 22));
        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(700, 100, 21, 20));
        label_6->setFont(font);
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(480, 10, 71, 16));
        label_2->setFont(font);
        lineEdit_Z_GK = new QLineEdit(centralWidget);
        lineEdit_Z_GK->setObjectName(QStringLiteral("lineEdit_Z_GK"));
        lineEdit_Z_GK->setGeometry(QRect(650, 160, 113, 22));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(30, 30, 141, 71));
        label_4->setFont(font);
        label_4->setAcceptDrops(true);
        label_4->setMidLineWidth(0);
        label_4->setWordWrap(true);
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(30, 120, 141, 71));
        label_5->setFont(font);
        label_5->setWordWrap(true);
        lineEdit_B = new QLineEdit(centralWidget);
        lineEdit_B->setObjectName(QStringLiteral("lineEdit_B"));
        lineEdit_B->setGeometry(QRect(290, 70, 113, 22));
        lineEdit_X_GK = new QLineEdit(centralWidget);
        lineEdit_X_GK->setObjectName(QStringLiteral("lineEdit_X_GK"));
        lineEdit_X_GK->setGeometry(QRect(290, 160, 113, 22));
        lineEdit_Y_GK = new QLineEdit(centralWidget);
        lineEdit_Y_GK->setObjectName(QStringLiteral("lineEdit_Y_GK"));
        lineEdit_Y_GK->setGeometry(QRect(460, 160, 113, 22));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(700, 10, 31, 20));
        label_3->setFont(font);
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(300, 10, 71, 16));
        label->setFont(font);
        CalcGeoToGK = new QPushButton(centralWidget);
        CalcGeoToGK->setObjectName(QStringLiteral("CalcGeoToGK"));
        CalcGeoToGK->setGeometry(QRect(380, 360, 281, 28));
        CalcGeoToGK->setFont(font);
        CalcGKtoGeo = new QPushButton(centralWidget);
        CalcGKtoGeo->setObjectName(QStringLiteral("CalcGKtoGeo"));
        CalcGKtoGeo->setGeometry(QRect(380, 390, 281, 28));
        CalcGKtoGeo->setFont(font);
        lineEdit_L = new QLineEdit(centralWidget);
        lineEdit_L->setObjectName(QStringLiteral("lineEdit_L"));
        lineEdit_L->setGeometry(QRect(460, 70, 113, 22));
        label_8 = new QLabel(centralWidget);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(500, 100, 21, 16));
        label_8->setFont(font);
        lineEdit_L_KAM = new QLineEdit(centralWidget);
        lineEdit_L_KAM->setObjectName(QStringLiteral("lineEdit_L_KAM"));
        lineEdit_L_KAM->setGeometry(QRect(460, 40, 113, 22));
        lineEdit_B_KAM = new QLineEdit(centralWidget);
        lineEdit_B_KAM->setObjectName(QStringLiteral("lineEdit_B_KAM"));
        lineEdit_B_KAM->setGeometry(QRect(290, 40, 113, 22));
        lineEdit_H_KAM = new QLineEdit(centralWidget);
        lineEdit_H_KAM->setObjectName(QStringLiteral("lineEdit_H_KAM"));
        lineEdit_H_KAM->setGeometry(QRect(650, 40, 113, 22));
        label_9 = new QLabel(centralWidget);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(180, 40, 101, 21));
        label_9->setFont(font);
        label_9->setAcceptDrops(true);
        label_9->setMidLineWidth(0);
        label_9->setWordWrap(true);
        label_10 = new QLabel(centralWidget);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(180, 70, 101, 21));
        label_10->setFont(font);
        label_10->setAcceptDrops(true);
        label_10->setMidLineWidth(0);
        label_10->setWordWrap(true);
        label_11 = new QLabel(centralWidget);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(180, 160, 111, 21));
        label_11->setFont(font);
        label_11->setAcceptDrops(true);
        label_11->setMidLineWidth(0);
        label_11->setWordWrap(true);
        label_12 = new QLabel(centralWidget);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setGeometry(QRect(180, 130, 101, 21));
        label_12->setFont(font);
        label_12->setAcceptDrops(true);
        label_12->setMidLineWidth(0);
        label_12->setWordWrap(true);
        lineEdit_Z_GK_KAM = new QLineEdit(centralWidget);
        lineEdit_Z_GK_KAM->setObjectName(QStringLiteral("lineEdit_Z_GK_KAM"));
        lineEdit_Z_GK_KAM->setGeometry(QRect(650, 130, 113, 22));
        lineEdit_X_GK_KAM = new QLineEdit(centralWidget);
        lineEdit_X_GK_KAM->setObjectName(QStringLiteral("lineEdit_X_GK_KAM"));
        lineEdit_X_GK_KAM->setGeometry(QRect(290, 130, 113, 22));
        lineEdit_Y_GK_KAM = new QLineEdit(centralWidget);
        lineEdit_Y_GK_KAM->setObjectName(QStringLiteral("lineEdit_Y_GK_KAM"));
        lineEdit_Y_GK_KAM->setGeometry(QRect(460, 130, 113, 22));
        label_13 = new QLabel(centralWidget);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setGeometry(QRect(30, 190, 231, 71));
        label_13->setFont(font);
        label_13->setWordWrap(true);
        lineEdit_e_or = new QLineEdit(centralWidget);
        lineEdit_e_or->setObjectName(QStringLiteral("lineEdit_e_or"));
        lineEdit_e_or->setGeometry(QRect(650, 220, 113, 22));
        lineEdit_r_or = new QLineEdit(centralWidget);
        lineEdit_r_or->setObjectName(QStringLiteral("lineEdit_r_or"));
        lineEdit_r_or->setGeometry(QRect(290, 220, 113, 22));
        lineEdit_b_or = new QLineEdit(centralWidget);
        lineEdit_b_or->setObjectName(QStringLiteral("lineEdit_b_or"));
        lineEdit_b_or->setGeometry(QRect(460, 220, 113, 22));
        label_14 = new QLabel(centralWidget);
        label_14->setObjectName(QStringLiteral("label_14"));
        label_14->setGeometry(QRect(500, 200, 21, 16));
        label_14->setFont(font);
        label_15 = new QLabel(centralWidget);
        label_15->setObjectName(QStringLiteral("label_15"));
        label_15->setGeometry(QRect(320, 200, 21, 16));
        label_15->setFont(font);
        label_16 = new QLabel(centralWidget);
        label_16->setObjectName(QStringLiteral("label_16"));
        label_16->setGeometry(QRect(690, 200, 21, 20));
        label_16->setFont(font);
        CalcSfer = new QPushButton(centralWidget);
        CalcSfer->setObjectName(QStringLiteral("CalcSfer"));
        CalcSfer->setGeometry(QRect(380, 420, 281, 28));
        CalcSfer->setFont(font);
        label_Attention = new QLabel(centralWidget);
        label_Attention->setObjectName(QStringLiteral("label_Attention"));
        label_Attention->setGeometry(QRect(270, 310, 511, 31));
        QFont font1;
        font1.setPointSize(13);
        label_Attention->setFont(font1);
        CalcMPTSKi = new QPushButton(centralWidget);
        CalcMPTSKi->setObjectName(QStringLiteral("CalcMPTSKi"));
        CalcMPTSKi->setGeometry(QRect(380, 450, 281, 28));
        CalcMPTSKi->setFont(font);
        label_17 = new QLabel(centralWidget);
        label_17->setObjectName(QStringLiteral("label_17"));
        label_17->setGeometry(QRect(30, 250, 181, 71));
        label_17->setFont(font);
        label_17->setWordWrap(true);
        label_18 = new QLabel(centralWidget);
        label_18->setObjectName(QStringLiteral("label_18"));
        label_18->setGeometry(QRect(320, 260, 21, 16));
        label_18->setFont(font);
        label_19 = new QLabel(centralWidget);
        label_19->setObjectName(QStringLiteral("label_19"));
        label_19->setGeometry(QRect(500, 260, 21, 16));
        label_19->setFont(font);
        lineEdit_y_or = new QLineEdit(centralWidget);
        lineEdit_y_or->setObjectName(QStringLiteral("lineEdit_y_or"));
        lineEdit_y_or->setGeometry(QRect(460, 280, 113, 22));
        label_20 = new QLabel(centralWidget);
        label_20->setObjectName(QStringLiteral("label_20"));
        label_20->setGeometry(QRect(690, 260, 21, 20));
        label_20->setFont(font);
        lineEdit_z_or = new QLineEdit(centralWidget);
        lineEdit_z_or->setObjectName(QStringLiteral("lineEdit_z_or"));
        lineEdit_z_or->setGeometry(QRect(650, 280, 113, 22));
        lineEdit_x_or = new QLineEdit(centralWidget);
        lineEdit_x_or->setObjectName(QStringLiteral("lineEdit_x_or"));
        lineEdit_x_or->setGeometry(QRect(290, 280, 113, 22));
        label_21 = new QLabel(centralWidget);
        label_21->setObjectName(QStringLiteral("label_21"));
        label_21->setGeometry(QRect(170, 530, 181, 31));
        label_21->setFont(font);
        label_21->setWordWrap(true);
        lineEdit_Lat_kmplx = new QLineEdit(centralWidget);
        lineEdit_Lat_kmplx->setObjectName(QStringLiteral("lineEdit_Lat_kmplx"));
        lineEdit_Lat_kmplx->setGeometry(QRect(20, 600, 113, 22));
        lineEdit_longt_kmplx = new QLineEdit(centralWidget);
        lineEdit_longt_kmplx->setObjectName(QStringLiteral("lineEdit_longt_kmplx"));
        lineEdit_longt_kmplx->setGeometry(QRect(150, 600, 113, 22));
        lineEdit_Z_kmplx = new QLineEdit(centralWidget);
        lineEdit_Z_kmplx->setObjectName(QStringLiteral("lineEdit_Z_kmplx"));
        lineEdit_Z_kmplx->setGeometry(QRect(280, 600, 113, 22));
        label_22 = new QLabel(centralWidget);
        label_22->setObjectName(QStringLiteral("label_22"));
        label_22->setGeometry(QRect(330, 570, 21, 20));
        label_22->setFont(font);
        label_23 = new QLabel(centralWidget);
        label_23->setObjectName(QStringLiteral("label_23"));
        label_23->setGeometry(QRect(200, 570, 21, 16));
        label_23->setFont(font);
        label_24 = new QLabel(centralWidget);
        label_24->setObjectName(QStringLiteral("label_24"));
        label_24->setGeometry(QRect(60, 570, 21, 16));
        label_24->setFont(font);
        lineEdit_X_kam_kmplx = new QLineEdit(centralWidget);
        lineEdit_X_kam_kmplx->setObjectName(QStringLiteral("lineEdit_X_kam_kmplx"));
        lineEdit_X_kam_kmplx->setGeometry(QRect(590, 600, 113, 22));
        label_25 = new QLabel(centralWidget);
        label_25->setObjectName(QStringLiteral("label_25"));
        label_25->setGeometry(QRect(640, 570, 21, 16));
        label_25->setFont(font);
        lineEdit_Y_kam_kmplx = new QLineEdit(centralWidget);
        lineEdit_Y_kam_kmplx->setObjectName(QStringLiteral("lineEdit_Y_kam_kmplx"));
        lineEdit_Y_kam_kmplx->setGeometry(QRect(720, 600, 113, 22));
        lineEdit_Z_kam_kmplx = new QLineEdit(centralWidget);
        lineEdit_Z_kam_kmplx->setObjectName(QStringLiteral("lineEdit_Z_kam_kmplx"));
        lineEdit_Z_kam_kmplx->setGeometry(QRect(840, 600, 113, 22));
        label_26 = new QLabel(centralWidget);
        label_26->setObjectName(QStringLiteral("label_26"));
        label_26->setGeometry(QRect(770, 570, 21, 16));
        label_26->setFont(font);
        label_27 = new QLabel(centralWidget);
        label_27->setObjectName(QStringLiteral("label_27"));
        label_27->setGeometry(QRect(630, 530, 271, 31));
        label_27->setFont(font);
        label_27->setWordWrap(true);
        label_28 = new QLabel(centralWidget);
        label_28->setObjectName(QStringLiteral("label_28"));
        label_28->setGeometry(QRect(890, 570, 21, 20));
        label_28->setFont(font);
        CalcKamGK = new QPushButton(centralWidget);
        CalcKamGK->setObjectName(QStringLiteral("CalcKamGK"));
        CalcKamGK->setGeometry(QRect(300, 650, 371, 28));
        CalcKamGK->setFont(font);
        lineEdit_B_kmplx = new QLineEdit(centralWidget);
        lineEdit_B_kmplx->setObjectName(QStringLiteral("lineEdit_B_kmplx"));
        lineEdit_B_kmplx->setGeometry(QRect(410, 600, 113, 22));
        label_29 = new QLabel(centralWidget);
        label_29->setObjectName(QStringLiteral("label_29"));
        label_29->setGeometry(QRect(390, 550, 161, 20));
        label_29->setFont(font);
        CalcCOIR = new QPushButton(centralWidget);
        CalcCOIR->setObjectName(QStringLiteral("CalcCOIR"));
        CalcCOIR->setGeometry(QRect(380, 480, 281, 28));
        CalcCOIR->setFont(font);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 972, 18));
        MainWindow->setMenuBar(menuBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "\320\237\320\265\321\200\320\265\321\201\321\207\320\265\321\202\321\213 \320\272\320\276\320\276\321\200\320\264\320\270\320\275\320\260\321\202 \320\223\320\225\320\236, \320\223\320\232, \320\241\321\204\320\265\321\200, \320\234\320\237\320\242\320\241\320\232\320\270", Q_NULLPTR));
        action_3->setText(QApplication::translate("MainWindow", "\320\227\320\260\320\277\320\270\321\201\320\260\321\202\321\214", Q_NULLPTR));
        action_4->setText(QApplication::translate("MainWindow", "\320\236\321\202\320\272\321\200\321\213\321\202\321\214 ", Q_NULLPTR));
        action_5->setText(QApplication::translate("MainWindow", "\320\222\321\213\321\205\320\276\320\264", Q_NULLPTR));
        label_7->setText(QApplication::translate("MainWindow", "X", Q_NULLPTR));
        lineEdit_H->setText(QApplication::translate("MainWindow", "594.1", Q_NULLPTR));
        label_6->setText(QApplication::translate("MainWindow", "Z", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "\320\224\320\276\320\273\320\263\320\276\321\202\320\260", Q_NULLPTR));
        lineEdit_Z_GK->setText(QApplication::translate("MainWindow", "0000.0", Q_NULLPTR));
        label_4->setText(QApplication::translate("MainWindow", "\320\223\320\265\320\276\320\264\320\265\320\267\320\270\321\207\320\265\321\201\320\272\320\270\320\265 \320\272\320\276\320\276\321\200\320\264\320\270\320\275\320\260\321\202\321\213:", Q_NULLPTR));
        label_5->setText(QApplication::translate("MainWindow", "\320\232\320\276\320\276\321\200\320\264\320\270\320\275\320\260\321\202\321\213 \320\262 \320\277\321\200\320\276\320\265\320\272\321\206\320\270\320\270 \320\223\320\232:", Q_NULLPTR));
        lineEdit_B->setText(QApplication::translate("MainWindow", "52.52612778 ", Q_NULLPTR));
        lineEdit_X_GK->setText(QApplication::translate("MainWindow", "000000.0", Q_NULLPTR));
        lineEdit_Y_GK->setText(QApplication::translate("MainWindow", "0000000.0", Q_NULLPTR));
        label_3->setText(QApplication::translate("MainWindow", "H", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "\320\250\320\270\321\200\320\276\321\202\320\260", Q_NULLPTR));
        CalcGeoToGK->setText(QApplication::translate("MainWindow", "\320\240\320\260\321\201\321\207\320\265\321\202 \320\270\320\267 \320\223\320\225\320\236 \320\262 \320\277\321\200\320\276\320\265\320\272\321\206\320\270\321\216 \320\223\320\232", Q_NULLPTR));
        CalcGKtoGeo->setText(QApplication::translate("MainWindow", "\320\240\320\260\321\201\321\207\320\265\321\202 \320\270\320\267 \320\277\321\200\320\276\320\265\320\272\321\206\320\270\320\270 \320\223\320\232  \320\262 \320\223\320\225\320\236 ", Q_NULLPTR));
        lineEdit_L->setText(QApplication::translate("MainWindow", "39.50625278 ", Q_NULLPTR));
        label_8->setText(QApplication::translate("MainWindow", "Y", Q_NULLPTR));
        lineEdit_L_KAM->setText(QApplication::translate("MainWindow", "39.43553333 ", Q_NULLPTR));
        lineEdit_B_KAM->setText(QApplication::translate("MainWindow", "52.64999167 ", Q_NULLPTR));
        lineEdit_H_KAM->setText(QApplication::translate("MainWindow", "4.1", Q_NULLPTR));
        label_9->setText(QApplication::translate("MainWindow", "\320\232\320\260\320\274\320\265\321\200\321\213_____", Q_NULLPTR));
        label_10->setText(QApplication::translate("MainWindow", "\320\236\321\200\320\270\320\265\320\275\321\202\320\270\321\200\320\260__", Q_NULLPTR));
        label_11->setText(QApplication::translate("MainWindow", "\320\236\321\200\320\270\320\265\320\275\321\202\320\270\321\200\320\260__", Q_NULLPTR));
        label_12->setText(QApplication::translate("MainWindow", "\320\232\320\260\320\274\320\265\321\200\321\213____", Q_NULLPTR));
        lineEdit_Z_GK_KAM->setText(QApplication::translate("MainWindow", "0000.0", Q_NULLPTR));
        lineEdit_X_GK_KAM->setText(QApplication::translate("MainWindow", "000000.0", Q_NULLPTR));
        lineEdit_Y_GK_KAM->setText(QApplication::translate("MainWindow", "0000000.0", Q_NULLPTR));
        label_13->setText(QApplication::translate("MainWindow", "\320\232\320\276\320\276\321\200\320\264\320\270\320\275\320\260\321\202\321\213 \321\201\321\204\320\265\321\200\320\270\321\207\320\265\321\201\320\272\320\270\320\265 (\320\235\320\232 - \320\232\320\260\320\274\320\265\321\200\320\260):", Q_NULLPTR));
        lineEdit_e_or->setText(QApplication::translate("MainWindow", "000.000", Q_NULLPTR));
        lineEdit_r_or->setText(QApplication::translate("MainWindow", "000000.0", Q_NULLPTR));
        lineEdit_b_or->setText(QApplication::translate("MainWindow", "000.000", Q_NULLPTR));
        label_14->setText(QApplication::translate("MainWindow", "b", Q_NULLPTR));
        label_15->setText(QApplication::translate("MainWindow", "r", Q_NULLPTR));
        label_16->setText(QApplication::translate("MainWindow", "e", Q_NULLPTR));
        CalcSfer->setText(QApplication::translate("MainWindow", "\320\240\320\260\321\201\321\207\320\265\321\202 \321\201\321\204\320\265\321\200\320\270\321\207\320\265\321\201\320\272\320\270\321\205 \320\272\320\276\320\276\321\200\320\264\320\270\320\275\320\260\321\202 ", Q_NULLPTR));
        label_Attention->setText(QApplication::translate("MainWindow", "!?", Q_NULLPTR));
        CalcMPTSKi->setText(QApplication::translate("MainWindow", "\320\240\320\260\321\201\321\207\320\265\321\202 \320\272\320\276\320\276\321\200\320\264\320\270\320\275\320\260\321\202 \320\262 \320\234\320\237\320\242\320\241\320\232\320\270 ", Q_NULLPTR));
        label_17->setText(QApplication::translate("MainWindow", "\320\232\320\276\320\276\321\200\320\264\320\270\320\275\320\260\321\202\321\213 \320\234\320\237\320\242\320\241\320\232\320\270 (\320\235\320\232 - \320\232\320\260\320\274\320\265\321\200\320\260):", Q_NULLPTR));
        label_18->setText(QApplication::translate("MainWindow", "x", Q_NULLPTR));
        label_19->setText(QApplication::translate("MainWindow", "y", Q_NULLPTR));
        lineEdit_y_or->setText(QApplication::translate("MainWindow", "000000.000", Q_NULLPTR));
        label_20->setText(QApplication::translate("MainWindow", "z", Q_NULLPTR));
        lineEdit_z_or->setText(QApplication::translate("MainWindow", "000000.000", Q_NULLPTR));
        lineEdit_x_or->setText(QApplication::translate("MainWindow", "000000.0", Q_NULLPTR));
        label_21->setText(QApplication::translate("MainWindow", "\320\232\320\276\320\276\321\200\320\264\320\270\320\275\320\260\321\202\321\213 \320\272\320\276\320\274\320\277\320\273\320\265\320\272\321\201\320\260", Q_NULLPTR));
        lineEdit_Lat_kmplx->setText(QApplication::translate("MainWindow", "0000000.0", Q_NULLPTR));
        lineEdit_longt_kmplx->setText(QApplication::translate("MainWindow", "0000000.0", Q_NULLPTR));
        lineEdit_Z_kmplx->setText(QApplication::translate("MainWindow", "0000.0", Q_NULLPTR));
        label_22->setText(QApplication::translate("MainWindow", "Z", Q_NULLPTR));
        label_23->setText(QApplication::translate("MainWindow", "Y", Q_NULLPTR));
        label_24->setText(QApplication::translate("MainWindow", "X", Q_NULLPTR));
        lineEdit_X_kam_kmplx->setText(QApplication::translate("MainWindow", "000000.0", Q_NULLPTR));
        label_25->setText(QApplication::translate("MainWindow", "X", Q_NULLPTR));
        lineEdit_Y_kam_kmplx->setText(QApplication::translate("MainWindow", "0000000.0", Q_NULLPTR));
        lineEdit_Z_kam_kmplx->setText(QApplication::translate("MainWindow", "0000.0", Q_NULLPTR));
        label_26->setText(QApplication::translate("MainWindow", "Y", Q_NULLPTR));
        label_27->setText(QApplication::translate("MainWindow", "\320\232\320\276\320\276\321\200\320\264\320\270\320\275\320\260\321\202\321\213 \320\236\320\237\320\243 \320\275\320\260 \320\272\320\276\320\274\320\277\320\273\320\265\320\272\321\201\320\265", Q_NULLPTR));
        label_28->setText(QApplication::translate("MainWindow", "Z", Q_NULLPTR));
        CalcKamGK->setText(QApplication::translate("MainWindow", "\320\240\320\260\321\201\321\207\320\265\321\202 \320\272\320\276\320\276\321\200\320\264\320\270\320\275\320\260\321\202 \320\223\320\265\320\276 \320\272\320\276\321\200\320\264\320\270\320\275\320\260\321\202  \320\221\320\236\320\255\320\241", Q_NULLPTR));
        lineEdit_B_kmplx->setText(QApplication::translate("MainWindow", "000.000", Q_NULLPTR));
        label_29->setText(QApplication::translate("MainWindow", "\320\220\320\267\320\270\320\274\321\203\321\202_\320\232\320\276\320\274\320\277\320\273\320\265\320\272\321\201\320\260 ", Q_NULLPTR));
        CalcCOIR->setText(QApplication::translate("MainWindow", "CalcKOIR", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
