#ifndef HOME_H
#define HOME_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Home; }
QT_END_NAMESPACE

class Home : public QMainWindow
{
    Q_OBJECT

public:
    Home(QWidget *parent = nullptr);
    ~Home();

private slots:
    void on_pbEncrypt_clicked();

    void on_pbDecrypt_clicked();

private:
    Ui::Home *ui;
};
#endif // HOME_H
