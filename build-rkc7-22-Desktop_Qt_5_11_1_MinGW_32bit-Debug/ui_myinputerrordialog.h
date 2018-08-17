/********************************************************************************
** Form generated from reading UI file 'myinputerrordialog.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYINPUTERRORDIALOG_H
#define UI_MYINPUTERRORDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_myInputErrorDialog
{
public:
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QTextEdit *textEdit_Error;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_NotDoubleError;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QDialog *myInputErrorDialog)
    {
        if (myInputErrorDialog->objectName().isEmpty())
            myInputErrorDialog->setObjectName(QStringLiteral("myInputErrorDialog"));
        myInputErrorDialog->resize(280, 240);
        layoutWidget = new QWidget(myInputErrorDialog);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 10, 258, 225));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        textEdit_Error = new QTextEdit(layoutWidget);
        textEdit_Error->setObjectName(QStringLiteral("textEdit_Error"));

        verticalLayout->addWidget(textEdit_Error);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton_NotDoubleError = new QPushButton(layoutWidget);
        pushButton_NotDoubleError->setObjectName(QStringLiteral("pushButton_NotDoubleError"));

        horizontalLayout->addWidget(pushButton_NotDoubleError);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout);

        QWidget::setTabOrder(pushButton_NotDoubleError, textEdit_Error);

        retranslateUi(myInputErrorDialog);

        QMetaObject::connectSlotsByName(myInputErrorDialog);
    } // setupUi

    void retranslateUi(QDialog *myInputErrorDialog)
    {
        myInputErrorDialog->setWindowTitle(QApplication::translate("myInputErrorDialog", "Dialog", nullptr));
        pushButton_NotDoubleError->setText(QApplication::translate("myInputErrorDialog", "\320\230\321\201\320\277\321\200\320\260\320\262\320\270\321\202\321\214 \320\270 \320\277\321\200\320\276\320\264\320\276\320\273\320\266\320\270\321\202\321\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class myInputErrorDialog: public Ui_myInputErrorDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYINPUTERRORDIALOG_H
