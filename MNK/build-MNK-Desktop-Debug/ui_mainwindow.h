/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QLabel *nLabel;
    QLineEdit *nEdit;
    QLabel *xLabel;
    QLabel *yLabel;
    QPushButton *mnk_button;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *xLayout;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *yLayout;
    QLabel *sLabel;
    QWidget *verticalLayoutWidget_3;
    QVBoxLayout *sLayout;
    QWidget *verticalLayoutWidget_4;
    QVBoxLayout *dbLayout;
    QPushButton *outbaseButton;
    QPushButton *inbaseButton;
    QLabel *zLabel;
    QWidget *verticalLayoutWidget_5;
    QVBoxLayout *zLayout;
    QWidget *verticalLayoutWidget_6;
    QVBoxLayout *resLayout;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(477, 461);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayoutWidget = new QWidget(centralWidget);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(7, 10, 231, 34));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        nLabel = new QLabel(gridLayoutWidget);
        nLabel->setObjectName(QStringLiteral("nLabel"));

        gridLayout->addWidget(nLabel, 0, 0, 1, 1);

        nEdit = new QLineEdit(gridLayoutWidget);
        nEdit->setObjectName(QStringLiteral("nEdit"));

        gridLayout->addWidget(nEdit, 0, 1, 1, 1);

        xLabel = new QLabel(centralWidget);
        xLabel->setObjectName(QStringLiteral("xLabel"));
        xLabel->setGeometry(QRect(30, 40, 16, 16));
        xLabel->setAlignment(Qt::AlignCenter);
        yLabel = new QLabel(centralWidget);
        yLabel->setObjectName(QStringLiteral("yLabel"));
        yLabel->setGeometry(QRect(100, 40, 20, 20));
        yLabel->setAlignment(Qt::AlignCenter);
        mnk_button = new QPushButton(centralWidget);
        mnk_button->setObjectName(QStringLiteral("mnk_button"));
        mnk_button->setGeometry(QRect(340, 10, 121, 31));
        verticalLayoutWidget = new QWidget(centralWidget);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(10, 60, 61, 391));
        xLayout = new QVBoxLayout(verticalLayoutWidget);
        xLayout->setSpacing(6);
        xLayout->setContentsMargins(11, 11, 11, 11);
        xLayout->setObjectName(QStringLiteral("xLayout"));
        xLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayoutWidget_2 = new QWidget(centralWidget);
        verticalLayoutWidget_2->setObjectName(QStringLiteral("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(80, 60, 61, 391));
        yLayout = new QVBoxLayout(verticalLayoutWidget_2);
        yLayout->setSpacing(6);
        yLayout->setContentsMargins(11, 11, 11, 11);
        yLayout->setObjectName(QStringLiteral("yLayout"));
        yLayout->setContentsMargins(0, 0, 0, 0);
        sLabel = new QLabel(centralWidget);
        sLabel->setObjectName(QStringLiteral("sLabel"));
        sLabel->setGeometry(QRect(240, 40, 20, 20));
        verticalLayoutWidget_3 = new QWidget(centralWidget);
        verticalLayoutWidget_3->setObjectName(QStringLiteral("verticalLayoutWidget_3"));
        verticalLayoutWidget_3->setGeometry(QRect(220, 60, 61, 391));
        sLayout = new QVBoxLayout(verticalLayoutWidget_3);
        sLayout->setSpacing(6);
        sLayout->setContentsMargins(11, 11, 11, 11);
        sLayout->setObjectName(QStringLiteral("sLayout"));
        sLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayoutWidget_4 = new QWidget(centralWidget);
        verticalLayoutWidget_4->setObjectName(QStringLiteral("verticalLayoutWidget_4"));
        verticalLayoutWidget_4->setGeometry(QRect(300, 360, 171, 91));
        dbLayout = new QVBoxLayout(verticalLayoutWidget_4);
        dbLayout->setSpacing(6);
        dbLayout->setContentsMargins(11, 11, 11, 11);
        dbLayout->setObjectName(QStringLiteral("dbLayout"));
        dbLayout->setContentsMargins(0, 0, 0, 0);
        outbaseButton = new QPushButton(verticalLayoutWidget_4);
        outbaseButton->setObjectName(QStringLiteral("outbaseButton"));
        outbaseButton->setEnabled(true);
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(outbaseButton->sizePolicy().hasHeightForWidth());
        outbaseButton->setSizePolicy(sizePolicy);

        dbLayout->addWidget(outbaseButton);

        inbaseButton = new QPushButton(verticalLayoutWidget_4);
        inbaseButton->setObjectName(QStringLiteral("inbaseButton"));
        sizePolicy.setHeightForWidth(inbaseButton->sizePolicy().hasHeightForWidth());
        inbaseButton->setSizePolicy(sizePolicy);

        dbLayout->addWidget(inbaseButton);

        zLabel = new QLabel(centralWidget);
        zLabel->setObjectName(QStringLiteral("zLabel"));
        zLabel->setGeometry(QRect(180, 40, 16, 18));
        verticalLayoutWidget_5 = new QWidget(centralWidget);
        verticalLayoutWidget_5->setObjectName(QStringLiteral("verticalLayoutWidget_5"));
        verticalLayoutWidget_5->setGeometry(QRect(150, 60, 61, 391));
        zLayout = new QVBoxLayout(verticalLayoutWidget_5);
        zLayout->setSpacing(6);
        zLayout->setContentsMargins(11, 11, 11, 11);
        zLayout->setObjectName(QStringLiteral("zLayout"));
        zLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayoutWidget_6 = new QWidget(centralWidget);
        verticalLayoutWidget_6->setObjectName(QStringLiteral("verticalLayoutWidget_6"));
        verticalLayoutWidget_6->setGeometry(QRect(400, 50, 61, 281));
        resLayout = new QVBoxLayout(verticalLayoutWidget_6);
        resLayout->setSpacing(6);
        resLayout->setContentsMargins(11, 11, 11, 11);
        resLayout->setObjectName(QStringLiteral("resLayout"));
        resLayout->setContentsMargins(0, 0, 0, 0);
        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "\320\234\320\235\320\232", 0));
        nLabel->setText(QApplication::translate("MainWindow", "\320\232\320\276\320\273-\320\262\320\276 \321\202\320\276\321\207\320\265\320\272: ", 0));
        xLabel->setText(QApplication::translate("MainWindow", "X", 0));
        yLabel->setText(QApplication::translate("MainWindow", "Y", 0));
        mnk_button->setText(QApplication::translate("MainWindow", "\320\235\320\260\320\271\321\202\320\270 \320\267\320\275\320\260\321\207\320\265\320\275\320\270\321\217", 0));
        sLabel->setText(QApplication::translate("MainWindow", "S", 0));
        outbaseButton->setText(QApplication::translate("MainWindow", "\320\237\320\276\320\273\321\203\321\207\320\270\321\202\321\214 \320\270\320\267 \321\202\320\260\320\261\320\273\320\270\321\206\321\213", 0));
        inbaseButton->setText(QApplication::translate("MainWindow", "\320\227\320\260\320\275\320\265\321\201\321\202\320\270 \320\262 \321\202\320\260\320\261\320\273\320\270\321\206\321\203", 0));
        zLabel->setText(QApplication::translate("MainWindow", "Z", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
