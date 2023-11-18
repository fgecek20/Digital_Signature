#ifndef TXTMSGDECRYPTION_H
#define TXTMSGDECRYPTION_H

#include <QMainWindow>

namespace Ui {
class TxtMsgDecryption;
}

class TxtMsgDecryption : public QMainWindow
{
    Q_OBJECT

public:
    explicit TxtMsgDecryption(QWidget *parent = nullptr);
    ~TxtMsgDecryption();

private slots:
    void on_pbDecrypt_clicked();

private:
    Ui::TxtMsgDecryption *ui;
};

#endif // TXTMSGDECRYPTION_H
