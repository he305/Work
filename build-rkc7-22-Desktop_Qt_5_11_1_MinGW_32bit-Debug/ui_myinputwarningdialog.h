/********************************************************************************
** Form generated from reading UI file 'myinputwarningdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYINPUTWARNINGDIALOG_H
#define UI_MYINPUTWARNINGDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_myInputWarningDialog
{
public:
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QTextEdit *textEdit_Warning;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QDialogButtonBox *buttonBox;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QDialog *myInputWarningDialog)
    {
        if (myInputWarningDialog->objectName().isEmpty())
            myInputWarningDialog->setObjectName(QStringLiteral("myInputWarningDialog"));
        myInputWarningDialog->resize(281, 241);
        layoutWidget = new QWidget(myInputWarningDialog);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 10, 261, 221));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        textEdit_Warning = new QTextEdit(layoutWidget);
        textEdit_Warning->setObjectName(QStringLiteral("textEdit_Warning"));
        textEdit_Warning->setFocusPolicy(Qt::NoFocus);

        verticalLayout->addWidget(textEdit_Warning);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        buttonBox = new QDialogButtonBox(layoutWidget);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setFocusPolicy(Qt::StrongFocus);
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        horizontalLayout->addWidget(buttonBox);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(myInputWarningDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), myInputWarningDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), myInputWarningDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(myInputWarningDialog);
    } // setupUi

    void retranslateUi(QDialog *myInputWarningDialog)
    {
        myInputWarningDialog->setWindowTitle(QApplication::translate("myInputWarningDialog", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class myInputWarningDialog: public Ui_myInputWarningDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYINPUTWARNINGDIALOG_H
