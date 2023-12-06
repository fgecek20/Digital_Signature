#include "home.h"
#include "./ui_home.h"

#include "txtmsgencryption.h"
#include "txtmsgdecryption.h"
#include "rsakeymanagement.h"

Home::Home(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Home)
{
    ui->setupUi(this);
    this->setFixedSize(373, 368);
    if(KeysExist()) {
        this->ui->pbGenerateKeys->setEnabled(false);
        this->ui->pbEncrypt->setEnabled(true);
        this->ui->pbDecrypt->setEnabled(true);
    }
    else {
        this->ui->pbGenerateKeys->setEnabled(true);
        this->ui->pbEncrypt->setEnabled(false);
        this->ui->pbDecrypt->setEnabled(false);
    }
}

Home::~Home()
{
    delete ui;
}


void Home::on_pbEncrypt_clicked()
{
    TxtMsgEncryption* w = new TxtMsgEncryption;
    w->show();
}


void Home::on_pbDecrypt_clicked()
{
    TxtMsgDecryption* w = new TxtMsgDecryption;
    w->show();
}

void Home::on_pbGenerateKeys_clicked()
{
    RSAKeyManagement* rsa = new RSAKeyManagement;
    this->ui->pbEncrypt->setEnabled(true);
    this->ui->pbDecrypt->setEnabled(true);
    this->ui->pbGenerateKeys->setEnabled(false);
    delete rsa;
}
