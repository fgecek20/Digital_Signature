#include "txtmsgdecryption.h"
#include "ui_txtmsgdecryption.h"

#include "textdecryption.h"

TxtMsgDecryption::TxtMsgDecryption(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TxtMsgDecryption)
{
    ui->setupUi(this);
    this->setFixedSize(488, 635);
}

TxtMsgDecryption::~TxtMsgDecryption()
{
    delete ui;
}

void TxtMsgDecryption::on_pbDecrypt_clicked()
{
    TextDecryption* textDecryption = new TextDecryption;

    if(textDecryption->DecryptionPossible()) {
        textDecryption->DecryptText();

        ui->pteDecryptedMessage->clear();
        ui->pteDecryptedMessage->insertPlainText(QString::fromStdString(textDecryption->ReturnPlainTextMessage()));

        if(!textDecryption->IntegrityCheck()) this->ui->lblWarning->setText(QString::fromStdString("Integrity check FAILED\n\n" + textDecryption->ReturnErrorMessage()));
        else this->ui->lblWarning->setText("Integrity check PASSED");
    }
    else this->ui->lblWarning->setText(QString::fromStdString(textDecryption->ReturnErrorMessage()));

    delete textDecryption;
}
