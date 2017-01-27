/********************************************************************************
** Form generated from reading UI file 'invertedmatrixwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INVERTEDMATRIXWINDOW_H
#define UI_INVERTEDMATRIXWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_InvertedMatrixWindow
{
public:
    QWidget *gridLayoutWidget;
    QGridLayout *grid_matrix;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label_matrix_type;

    void setupUi(QWidget *InvertedMatrixWindow)
    {
        if (InvertedMatrixWindow->objectName().isEmpty())
            InvertedMatrixWindow->setObjectName(QStringLiteral("InvertedMatrixWindow"));
        InvertedMatrixWindow->resize(641, 468);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(InvertedMatrixWindow->sizePolicy().hasHeightForWidth());
        InvertedMatrixWindow->setSizePolicy(sizePolicy);
        gridLayoutWidget = new QWidget(InvertedMatrixWindow);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(10, 40, 621, 421));
        grid_matrix = new QGridLayout(gridLayoutWidget);
        grid_matrix->setObjectName(QStringLiteral("grid_matrix"));
        grid_matrix->setContentsMargins(0, 0, 0, 0);
        horizontalLayoutWidget = new QWidget(InvertedMatrixWindow);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(10, 10, 621, 24));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label_matrix_type = new QLabel(horizontalLayoutWidget);
        label_matrix_type->setObjectName(QStringLiteral("label_matrix_type"));
        QFont font;
        font.setFamily(QStringLiteral("Consolas"));
        font.setPointSize(14);
        font.setBold(true);
        font.setWeight(75);
        label_matrix_type->setFont(font);

        horizontalLayout->addWidget(label_matrix_type);


        retranslateUi(InvertedMatrixWindow);

        QMetaObject::connectSlotsByName(InvertedMatrixWindow);
    } // setupUi

    void retranslateUi(QWidget *InvertedMatrixWindow)
    {
        InvertedMatrixWindow->setWindowTitle(QApplication::translate("InvertedMatrixWindow", "\320\236\320\261\321\200\320\260\321\202\320\275\320\260\321\217 \320\274\320\260\321\202\321\200\320\270\321\206\320\260", Q_NULLPTR));
        label_matrix_type->setText(QApplication::translate("InvertedMatrixWindow", "TextLabel", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class InvertedMatrixWindow: public Ui_InvertedMatrixWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INVERTEDMATRIXWINDOW_H
