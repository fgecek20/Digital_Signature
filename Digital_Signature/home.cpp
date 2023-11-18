#include "home.h"
#include "./ui_home.h"

#include "txtmsgencryption.h"

Home::Home(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Home)
{
    ui->setupUi(this);
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

}

