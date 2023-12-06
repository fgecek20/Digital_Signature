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

        if(!textDecryption->IntegrityCheck()) this->ui->lblWarning->setText("WARNING: Integrity check FAILED! Message has been compromised");
        ui->pteDecryptedMessage->clear();
        ui->pteDecryptedMessage->insertPlainText(QString::fromStdString(textDecryption->ReturnPlainTextMessage()));
    }
    else std::cout << "Decryption not possible due to missing directory or files" << std::endl;

    delete textDecryption;
}
