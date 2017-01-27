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
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
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
    QWidget *gridLayoutWidget;
    QGridLayout *gridMenu;
    QComboBox *method_box;
    QLabel *method_label;
    QLabel *size_label;
    QLineEdit *size_line;
    QWidget *gridLayoutWidget_2;
    QGridLayout *gridMatrix;
    QPushButton *button_invert;
    QLabel *label_det;
    QPushButton *button_freezeMatrix;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(765, 484);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        QFont font;
        font.setFamily(QStringLiteral("Consolas"));
        font.setPointSize(12);
        font.setBold(true);
        font.setUnderline(false);
        font.setWeight(75);
        MainWindow->setFont(font);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayoutWidget = new QWidget(centralWidget);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(10, 10, 171, 95));
        gridMenu = new QGridLayout(gridLayoutWidget);
        gridMenu->setSpacing(6);
        gridMenu->setContentsMargins(11, 11, 11, 11);
        gridMenu->setObjectName(QStringLiteral("gridMenu"));
        gridMenu->setContentsMargins(0, 0, 0, 0);
        method_box = new QComboBox(gridLayoutWidget);
        method_box->setObjectName(QStringLiteral("method_box"));

        gridMenu->addWidget(method_box, 1, 1, 1, 1);

        method_label = new QLabel(gridLayoutWidget);
        method_label->setObjectName(QStringLiteral("method_label"));

        gridMenu->addWidget(method_label, 1, 0, 1, 1);

        size_label = new QLabel(gridLayoutWidget);
        size_label->setObjectName(QStringLiteral("size_label"));

        gridMenu->addWidget(size_label, 0, 0, 1, 1);

        size_line = new QLineEdit(gridLayoutWidget);
        size_line->setObjectName(QStringLiteral("size_line"));
        size_line->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridMenu->addWidget(size_line, 0, 1, 1, 1);

        gridLayoutWidget_2 = new QWidget(centralWidget);
        gridLayoutWidget_2->setObjectName(QStringLiteral("gridLayoutWidget_2"));
        gridLayoutWidget_2->setGeometry(QRect(190, 10, 561, 461));
        gridMatrix = new QGridLayout(gridLayoutWidget_2);
        gridMatrix->setSpacing(6);
        gridMatrix->setContentsMargins(11, 11, 11, 11);
        gridMatrix->setObjectName(QStringLiteral("gridMatrix"));
        gridMatrix->setContentsMargins(0, 0, 0, 0);
        button_invert = new QPushButton(centralWidget);
        button_invert->setObjectName(QStringLiteral("button_invert"));
        button_invert->setEnabled(false);
        button_invert->setGeometry(QRect(10, 440, 161, 31));
        label_det = new QLabel(centralWidget);
        label_det->setObjectName(QStringLiteral("label_det"));
        label_det->setGeometry(QRect(10, 140, 169, 15));
        QFont font1;
        font1.setPointSize(10);
        font1.setKerning(false);
        label_det->setFont(font1);
        label_det->setAcceptDrops(false);
        button_freezeMatrix = new QPushButton(centralWidget);
        button_freezeMatrix->setObjectName(QStringLiteral("button_freezeMatrix"));
        button_freezeMatrix->setGeometry(QRect(10, 110, 169, 27));
        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "\320\236\320\261\321\200\320\260\321\211\320\265\320\275\320\270\320\265 \320\274\320\260\321\202\321\200\320\270\321\206", Q_NULLPTR));
        method_label->setText(QApplication::translate("MainWindow", "\320\234\320\265\321\202\320\276\320\264:", Q_NULLPTR));
        size_label->setText(QApplication::translate("MainWindow", "\320\240\320\260\320\267\320\274\320\265\321\200:", Q_NULLPTR));
        size_line->setText(QApplication::translate("MainWindow", "6", Q_NULLPTR));
        button_invert->setText(QApplication::translate("MainWindow", "\320\236\320\261\321\200\320\260\321\202\320\270\321\202\321\214 \320\274\320\260\321\202\321\200\320\270\321\206\321\203", Q_NULLPTR));
        label_det->setText(QApplication::translate("MainWindow", "\320\236\320\277\321\200\320\265\320\264\320\265\320\273\320\270\321\202\320\265\320\273\321\214 \320\274\320\260\321\202\321\200\320\270\321\206\321\213 = 0", Q_NULLPTR));
        button_freezeMatrix->setText(QApplication::translate("MainWindow", "\320\227\320\260\320\272\321\200\320\265\320\277\320\270\321\202\321\214 \320\274\320\260\321\202\321\200\320\270\321\206\321\203", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
