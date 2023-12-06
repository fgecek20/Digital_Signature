/********************************************************************************
** Form generated from reading UI file 'txtmsgencryption.ui'
**
** Created by: Qt User Interface Compiler version 6.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TXTMSGENCRYPTION_H
#define UI_TXTMSGENCRYPTION_H

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

class Ui_TxtMsgEncryption
{
public:
    QWidget *centralwidget;
    QPlainTextEdit *ptePlainTextMessage;
    QPushButton *pbEncrypt;
    QLabel *lblEncryptedMessage;
    QPlainTextEdit *pteEncryptedMessage;
    QLabel *lblKey;
    QPlainTextEdit *pteKey;
    QPushButton *pbSend;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *TxtMsgEncryption)
    {
        if (TxtMsgEncryption->objectName().isEmpty())
            TxtMsgEncryption->setObjectName("TxtMsgEncryption");
        TxtMsgEncryption->resize(488, 635);
        centralwidget = new QWidget(TxtMsgEncryption);
        centralwidget->setObjectName("centralwidget");
        ptePlainTextMessage = new QPlainTextEdit(centralwidget);
        ptePlainTextMessage->setObjectName("ptePlainTextMessage");
        ptePlainTextMessage->setGeometry(QRect(30, 20, 421, 181));
        pbEncrypt = new QPushButton(centralwidget);
        pbEncrypt->setObjectName("pbEncrypt");
        pbEncrypt->setGeometry(QRect(30, 210, 131, 31));
        lblEncryptedMessage = new QLabel(centralwidget);
        lblEncryptedMessage->setObjectName("lblEncryptedMessage");
        lblEncryptedMessage->setGeometry(QRect(30, 300, 121, 20));
        pteEncryptedMessage = new QPlainTextEdit(centralwidget);
        pteEncryptedMessage->setObjectName("pteEncryptedMessage");
        pteEncryptedMessage->setGeometry(QRect(30, 320, 421, 141));
        pteEncryptedMessage->setReadOnly(true);
        lblKey = new QLabel(centralwidget);
        lblKey->setObjectName("lblKey");
        lblKey->setGeometry(QRect(30, 490, 54, 17));
        pteKey = new QPlainTextEdit(centralwidget);
        pteKey->setObjectName("pteKey");
        pteKey->setGeometry(QRect(30, 510, 421, 31));
        pteKey->setReadOnly(true);
        pbSend = new QPushButton(centralwidget);
        pbSend->setObjectName("pbSend");
        pbSend->setGeometry(QRect(30, 550, 131, 30));
        TxtMsgEncryption->setCentralWidget(centralwidget);
        menubar = new QMenuBar(TxtMsgEncryption);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 488, 22));
        TxtMsgEncryption->setMenuBar(menubar);
        statusbar = new QStatusBar(TxtMsgEncryption);
        statusbar->setObjectName("statusbar");
        TxtMsgEncryption->setStatusBar(statusbar);

        retranslateUi(TxtMsgEncryption);

        QMetaObject::connectSlotsByName(TxtMsgEncryption);
    } // setupUi

    void retranslateUi(QMainWindow *TxtMsgEncryption)
    {
        TxtMsgEncryption->setWindowTitle(QCoreApplication::translate("TxtMsgEncryption", "Encrypt Text Message", nullptr));
        ptePlainTextMessage->setPlaceholderText(QCoreApplication::translate("TxtMsgEncryption", "Type yout message here...", nullptr));
        pbEncrypt->setText(QCoreApplication::translate("TxtMsgEncryption", "Encrypt", nullptr));
        lblEncryptedMessage->setText(QCoreApplication::translate("TxtMsgEncryption", "Encrypted message:", nullptr));
        lblKey->setText(QCoreApplication::translate("TxtMsgEncryption", "Key:", nullptr));
        pbSend->setText(QCoreApplication::translate("TxtMsgEncryption", "Send", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TxtMsgEncryption: public Ui_TxtMsgEncryption {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TXTMSGENCRYPTION_H
