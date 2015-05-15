#define DIALOG_H

#include <QDialog>
#include <QTcpSocket>
#include <QHostAddress>
#include "C:\QT\Lab2_server/myclient.h"
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
    void onSokConnected();
    //отключение
    void onSokDisconnected();
    //получение информации и ее обработка
    void onSokReadyRead();
    //смс об ошибках
    void onSokDisplayError(QAbstractSocket::SocketError socketError);
//сигналы
    void on_pbConnect_clicked();
    void on_pbDisconnect_clicked();
//    void on_cbToAll_clicked();
    void on_pbSend_clicked();

private:
    Ui::Dialog *ui;
    QTcpSocket *sok;
    quint16 blockSize;
    QString name;
    void AddToLog(QString text);

};

