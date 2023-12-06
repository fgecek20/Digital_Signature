/********************************************************************************
** Form generated from reading UI file 'txtmsgdecryption.ui'
**
** Created by: Qt User Interface Compiler version 6.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TXTMSGDECRYPTION_H
#define UI_TXTMSGDECRYPTION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TxtMsgDecryption
{
public:
    QWidget *centralwidget;
    QPlainTextEdit *pteDecryptedMessage;
    QPushButton *pbDecrypt;
    QLabel *lblWarning;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *TxtMsgDecryption)
    {
        if (TxtMsgDecryption->objectName().isEmpty())
            TxtMsgDecryption->setObjectName("TxtMsgDecryption");
        TxtMsgDecryption->resize(483, 600);
        centralwidget = new QWidget(TxtMsgDecryption);
        centralwidget->setObjectName("centralwidget");
        pteDecryptedMessage = new QPlainTextEdit(centralwidget);
        pteDecryptedMessage->setObjectName("pteDecryptedMessage");
        pteDecryptedMessage->setGeometry(QRect(30, 20, 421, 181));
        pteDecryptedMessage->setReadOnly(true);
        pbDecrypt = new QPushButton(centralwidget);
        pbDecrypt->setObjectName("pbDecrypt");
        pbDecrypt->setGeometry(QRect(30, 210, 131, 31));
        lblWarning = new QLabel(centralwidget);
        lblWarning->setObjectName("lblWarning");
        lblWarning->setGeometry(QRect(30, 270, 421, 571));
        lblWarning->setTextFormat(Qt::PlainText);
        lblWarning->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        lblWarning->setWordWrap(true);
        TxtMsgDecryption->setCentralWidget(centralwidget);
        menubar = new QMenuBar(TxtMsgDecryption);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 483, 23));
        TxtMsgDecryption->setMenuBar(menubar);
        statusbar = new QStatusBar(TxtMsgDecryption);
        statusbar->setObjectName("statusbar");
        TxtMsgDecryption->setStatusBar(statusbar);

        retranslateUi(TxtMsgDecryption);

        QMetaObject::connectSlotsByName(TxtMsgDecryption);
    } // setupUi

    void retranslateUi(QMainWindow *TxtMsgDecryption)
    {
        TxtMsgDecryption->setWindowTitle(QCoreApplication::translate("TxtMsgDecryption", "Decrypt Text Message", nullptr));
        pteDecryptedMessage->setPlaceholderText(QCoreApplication::translate("TxtMsgDecryption", "Your message will appear here when you press the Decrypt button...", nullptr));
        pbDecrypt->setText(QCoreApplication::translate("TxtMsgDecryption", "Decrypt", nullptr));
        lblWarning->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class TxtMsgDecryption: public Ui_TxtMsgDecryption {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TXTMSGDECRYPTION_H
