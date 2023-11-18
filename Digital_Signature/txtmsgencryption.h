#ifndef TXTMSGENCRYPTION_H
#define TXTMSGENCRYPTION_H

#include <QMainWindow>

namespace Ui {
class TxtMsgEncryption;
}

class TxtMsgEncryption : public QMainWindow
{
    Q_OBJECT

public:
    explicit TxtMsgEncryption(QWidget *parent = nullptr);
    ~TxtMsgEncryption();

private slots:
    void on_pbEncrypt_clicked();

private:
    Ui::TxtMsgEncryption *ui;
};

#endif // TXTMSGENCRYPTION_H
