#define DIALOG_H

#include <QDialog>
#include <QTcpSocket>
#include <QHostAddress>
#include "C:\QT\server/client.h"
class Client;

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
    void SokConnected();
    //отключение
    void SokDisconnected();
    //получение информации и ее обработка
    void SokReadyRead();
    //смс об ошибках
    void SokDisplayError(QAbstractSocket::SocketError socketError);
//сигнал на соединение
    void on_pbConnect_clicked();
//сигнал на отлючение
    void on_pbDisconnect_clicked();
//сигнал на отправку смс
    void on_pbSend_clicked();

private:
    Ui::Dialog *ui;
    QTcpSocket *sok;
    //длина блока передаваемых данных
    quint16 blockSize;
    QString name;
    //вывод на экран
    void Read(QString text);

};

