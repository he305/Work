/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.4.2
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
    QWidget *gridLayoutWidget_2;
    QGridLayout *abLayout;
    QLabel *bXAnswer;
    QLabel *bXLabel;
    QLabel *aXLabel;
    QLabel *aXAnswer;
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

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(477, 461);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayoutWidget = new QWidget(centralWidget);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(7, 10, 231, 24));
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
        mnk_button->setGeometry(QRect(380, 10, 81, 31));
        gridLayoutWidget_2 = new QWidget(centralWidget);
        gridLayoutWidget_2->setObjectName(QStringLiteral("gridLayoutWidget_2"));
        gridLayoutWidget_2->setGeometry(QRect(380, 50, 81, 80));
        abLayout = new QGridLayout(gridLayoutWidget_2);
        abLayout->setSpacing(6);
        abLayout->setContentsMargins(11, 11, 11, 11);
        abLayout->setObjectName(QStringLiteral("abLayout"));
        abLayout->setContentsMargins(0, 0, 0, 0);
        bXAnswer = new QLabel(gridLayoutWidget_2);
        bXAnswer->setObjectName(QStringLiteral("bXAnswer"));
        bXAnswer->setAlignment(Qt::AlignCenter);

        abLayout->addWidget(bXAnswer, 1, 2, 1, 1);

        bXLabel = new QLabel(gridLayoutWidget_2);
        bXLabel->setObjectName(QStringLiteral("bXLabel"));
        bXLabel->setAlignment(Qt::AlignCenter);

        abLayout->addWidget(bXLabel, 1, 0, 1, 1);

        aXLabel = new QLabel(gridLayoutWidget_2);
        aXLabel->setObjectName(QStringLiteral("aXLabel"));
        aXLabel->setAlignment(Qt::AlignCenter);

        abLayout->addWidget(aXLabel, 0, 0, 1, 1);

        aXAnswer = new QLabel(gridLayoutWidget_2);
        aXAnswer->setObjectName(QStringLiteral("aXAnswer"));
        aXAnswer->setAlignment(Qt::AlignCenter);

        abLayout->addWidget(aXAnswer, 0, 2, 1, 1);

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
        sLabel->setGeometry(QRect(180, 40, 20, 20));
        verticalLayoutWidget_3 = new QWidget(centralWidget);
        verticalLayoutWidget_3->setObjectName(QStringLiteral("verticalLayoutWidget_3"));
        verticalLayoutWidget_3->setGeometry(QRect(150, 60, 61, 391));
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
        mnk_button->setText(QApplication::translate("MainWindow", "\320\235\320\260\320\271\321\202\320\270 \320\260 \320\270 b", 0));
        bXAnswer->setText(QApplication::translate("MainWindow", "0", 0));
        bXLabel->setText(QApplication::translate("MainWindow", "b", 0));
        aXLabel->setText(QApplication::translate("MainWindow", "a", 0));
        aXAnswer->setText(QApplication::translate("MainWindow", "0", 0));
        sLabel->setText(QApplication::translate("MainWindow", "S", 0));
        outbaseButton->setText(QApplication::translate("MainWindow", "\320\237\320\276\320\273\321\203\321\207\320\270\321\202\321\214 \320\270\320\267 \321\202\320\260\320\261\320\273\320\270\321\206\321\213", 0));
        inbaseButton->setText(QApplication::translate("MainWindow", "\320\227\320\260\320\275\320\265\321\201\321\202\320\270 \320\262 \321\202\320\260\320\261\320\273\320\270\321\206\321\203", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
