#include "txtmsgencryption.h"
#include "ui_txtmsgencryption.h"

#include "textencryption.h"

TextEncryption* textEncryption;

TxtMsgEncryption::TxtMsgEncryption(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TxtMsgEncryption)
{
    ui->setupUi(this);
    this->setFixedSize(488, 635);
}

TxtMsgEncryption::~TxtMsgEncryption()
{
    delete ui;
}

void TxtMsgEncryption::on_pbEncrypt_clicked()
{
    delete textEncryption;

    QString* msgText = new QString;
    *(msgText) = ui->ptePlainTextMessage->toPlainText();

    textEncryption = new TextEncryption(msgText->toStdString());

    textEncryption->EncryptMessage();
    ui->pteEncryptedMessage->clear();
    ui->pteEncryptedMessage->insertPlainText(QString::fromStdString((textEncryption->ReturnEncodedEncryptedMessage())));
    ui->pteKey->clear();
    ui->pteKey->insertPlainText(QString::fromStdString(textEncryption->ReturnEncodedKey()));

    delete msgText;
}

void TxtMsgEncryption::on_pbSend_clicked()
{
    textEncryption->Sign();
    textEncryption->Send();
}
