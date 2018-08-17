/********************************************************************************
** Form generated from reading UI file 'resdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RESDIALOG_H
#define UI_RESDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_ResDialog
{
public:
    QVBoxLayout *verticalLayout;
    QTextEdit *textEdit_Res;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *ResDialog)
    {
        if (ResDialog->objectName().isEmpty())
            ResDialog->setObjectName(QStringLiteral("ResDialog"));
        ResDialog->resize(350, 324);
        verticalLayout = new QVBoxLayout(ResDialog);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        textEdit_Res = new QTextEdit(ResDialog);
        textEdit_Res->setObjectName(QStringLiteral("textEdit_Res"));

        verticalLayout->addWidget(textEdit_Res);

        buttonBox = new QDialogButtonBox(ResDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(ResDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), ResDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), ResDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(ResDialog);
    } // setupUi

    void retranslateUi(QDialog *ResDialog)
    {
        ResDialog->setWindowTitle(QApplication::translate("ResDialog", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ResDialog: public Ui_ResDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RESDIALOG_H
