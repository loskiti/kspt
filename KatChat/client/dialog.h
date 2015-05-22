#define DIALOG_H

#include <QDialog>
#include <QTcpSocket>
#include <QHostAddress>
#include "C:\QT\2\3\Lab2_server\myclient.h"
class  MyClient;

namespace Ui {
    class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private slots:
    // подключение
    void Connected();
    //отключение
    void Disconnected();
    //получение информации и ее обработка
    void Operation();
    //смс об ошибках
    void Error(QAbstractSocket::SocketError socketError);
//сигнал на соединение
    void on_pbConnect_clicked();
    //сигнал на отлючение
    void on_pbDisconnect_clicked();
    //сигнал на отправку смс
    void on_pbSend_clicked();

private:
    Ui::Dialog *ui;
    QTcpSocket *sok;
    quint16 blockSize;
    //имя пользователя
    QString name;
    // функция вывода текста
    void Write(QString text);

};
