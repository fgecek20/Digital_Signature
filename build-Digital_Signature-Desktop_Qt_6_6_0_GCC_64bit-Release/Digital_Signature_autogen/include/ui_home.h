/********************************************************************************
** Form generated from reading UI file 'home.ui'
**
** Created by: Qt User Interface Compiler version 6.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HOME_H
#define UI_HOME_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Home
{
public:
    QWidget *centralwidget;
    QPushButton *pbEncrypt;
    QPushButton *pbDecrypt;
    QPushButton *pbGenerateKeys;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Home)
    {
        if (Home->objectName().isEmpty())
            Home->setObjectName("Home");
        Home->resize(373, 368);
        centralwidget = new QWidget(Home);
        centralwidget->setObjectName("centralwidget");
        pbEncrypt = new QPushButton(centralwidget);
        pbEncrypt->setObjectName("pbEncrypt");
        pbEncrypt->setGeometry(QRect(120, 100, 131, 51));
        pbDecrypt = new QPushButton(centralwidget);
        pbDecrypt->setObjectName("pbDecrypt");
        pbDecrypt->setGeometry(QRect(120, 170, 131, 51));
        pbGenerateKeys = new QPushButton(centralwidget);
        pbGenerateKeys->setObjectName("pbGenerateKeys");
        pbGenerateKeys->setGeometry(QRect(230, 280, 131, 31));
        Home->setCentralWidget(centralwidget);
        menubar = new QMenuBar(Home);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 373, 23));
        Home->setMenuBar(menubar);
        statusbar = new QStatusBar(Home);
        statusbar->setObjectName("statusbar");
        Home->setStatusBar(statusbar);

        retranslateUi(Home);

        QMetaObject::connectSlotsByName(Home);
    } // setupUi

    void retranslateUi(QMainWindow *Home)
    {
        Home->setWindowTitle(QCoreApplication::translate("Home", "Hunter Cipher", nullptr));
        pbEncrypt->setText(QCoreApplication::translate("Home", "Encrypt", nullptr));
        pbDecrypt->setText(QCoreApplication::translate("Home", "Decrypt", nullptr));
        pbGenerateKeys->setText(QCoreApplication::translate("Home", "Generate Keys", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Home: public Ui_Home {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HOME_H
