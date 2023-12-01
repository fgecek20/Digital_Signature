#include "txtmsgencryption.h"
#include "ui_txtmsgencryption.h"

#include "textencryption.h"

TxtMsgEncryption::TxtMsgEncryption(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TxtMsgEncryption)
{
    ui->setupUi(this);
}

TxtMsgEncryption::~TxtMsgEncryption()
{
    delete ui;
}

void TxtMsgEncryption::on_pbEncrypt_clicked()
{
    QString* msgText = new QString;
    *(msgText) = ui->ptePlainTextMessage->toPlainText();

    TextEncryption* textEncryption = new TextEncryption(msgText->toStdString());

    textEncryption->CreateMessageHash();
    textEncryption->SaveMessageHash();
    textEncryption->EncryptMessage();
    textEncryption->SaveEncryptedMessage();
    ui->pteEncryptedMessage->clear();
    ui->pteEncryptedMessage->insertPlainText(QString::fromStdString((textEncryption->ReturnEncodedMessage())));

    textEncryption->SaveKey();
    textEncryption->SaveInitialisationVector();
    ui->pteKey->clear();
    ui->pteKey->insertPlainText(QString::fromStdString(textEncryption->ReturnEncodedKey()));

    delete msgText;
    delete textEncryption;
}
