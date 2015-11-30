/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QWidget *formLayoutWidget;
    QFormLayout *formLayout;
    QLabel *velLable;
    QLineEdit *velEdit;
    QLabel *timeLable;
    QLabel *RLabel;
    QLineEdit *timeEdit;
    QLineEdit *REdit;
    QPushButton *refreshButton;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(679, 493);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        formLayoutWidget = new QWidget(centralWidget);
        formLayoutWidget->setObjectName(QStringLiteral("formLayoutWidget"));
        formLayoutWidget->setGeometry(QRect(160, 100, 160, 74));
        formLayout = new QFormLayout(formLayoutWidget);
        formLayout->setSpacing(6);
        formLayout->setContentsMargins(11, 11, 11, 11);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setContentsMargins(0, 0, 0, 0);
        velLable = new QLabel(formLayoutWidget);
        velLable->setObjectName(QStringLiteral("velLable"));

        formLayout->setWidget(0, QFormLayout::LabelRole, velLable);

        velEdit = new QLineEdit(formLayoutWidget);
        velEdit->setObjectName(QStringLiteral("velEdit"));

        formLayout->setWidget(0, QFormLayout::FieldRole, velEdit);

        timeLable = new QLabel(formLayoutWidget);
        timeLable->setObjectName(QStringLiteral("timeLable"));

        formLayout->setWidget(1, QFormLayout::LabelRole, timeLable);

        RLabel = new QLabel(formLayoutWidget);
        RLabel->setObjectName(QStringLiteral("RLabel"));

        formLayout->setWidget(2, QFormLayout::LabelRole, RLabel);

        timeEdit = new QLineEdit(formLayoutWidget);
        timeEdit->setObjectName(QStringLiteral("timeEdit"));

        formLayout->setWidget(1, QFormLayout::FieldRole, timeEdit);

        REdit = new QLineEdit(formLayoutWidget);
        REdit->setObjectName(QStringLiteral("REdit"));

        formLayout->setWidget(2, QFormLayout::FieldRole, REdit);

        refreshButton = new QPushButton(centralWidget);
        refreshButton->setObjectName(QStringLiteral("refreshButton"));
        refreshButton->setGeometry(QRect(580, 440, 75, 23));
        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        velLable->setText(QApplication::translate("MainWindow", "Velocity", 0));
        velEdit->setText(QApplication::translate("MainWindow", "100", 0));
        timeLable->setText(QApplication::translate("MainWindow", "Time", 0));
        RLabel->setText(QApplication::translate("MainWindow", "R", 0));
        timeEdit->setText(QApplication::translate("MainWindow", "-10", 0));
        REdit->setText(QApplication::translate("MainWindow", "20", 0));
        refreshButton->setText(QApplication::translate("MainWindow", "\320\236\320\261\320\275\320\276\320\262\320\270\321\202\321\214", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
