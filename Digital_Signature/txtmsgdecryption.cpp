#include "txtmsgdecryption.h"
#include "ui_txtmsgdecryption.h"

#include "textdecryption.h"

TxtMsgDecryption::TxtMsgDecryption(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TxtMsgDecryption)
{
    ui->setupUi(this);
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

        if(textDecryption->IntegrityCheck()) std::cout << "Integrity check PASSED" << std::endl;
        else std::cout << "Integrity check FAILED" << std::endl;
    }
    else std::cout << "Decryption not possible due to missing directory or files" << std::endl;

    delete textDecryption;
}
