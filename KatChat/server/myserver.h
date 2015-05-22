#ifndef MYSERVER_H
#define MYSERVER_H

#include <QTcpServer>
#include <QDebug>
#include "myclient.h"
class MyClient;

class MyServer : public QTcpServer
{
    Q_OBJECT

public:
    explicit MyServer(QWidget *widget1 = 0, QObject *parent = 0);
    // прослушка
    bool StartServer(QHostAddress addr, qint16 port);
    //уведомление о новом пользователе
    void SendToAllUserOnline(QString name);
    // уведомление, что пользователь вышел
    void SendToAllUserOffline(QString name);
    // разослать сообщение от какого-то пользователя для всех
    void SendToAllMessage(QString message, QString fromUsername);
    // смс от сервера для всех
    void SendToAllServerMessage(QString message);
    // приватное смс от сервера
    void SendServerMessageToUsers(QString message, const QStringList &users);
    // переслать приватное смс от пользователя
    void SendMessageToUsers(QString message, const QStringList &users, QString fromUser);
    // список пользователей
    QStringList getUsersOnline() ;
    // проверка имени на допустимые символы
    bool isNameValid(QString name) ;
    // проверка, используется ли этот ник
    bool isNameUsed(QString name) ;

signals:
    //вывод на экран
    void Writechat(QString string);

public slots:
    // // набор сообщения
    void MessageText(QString message, const QStringList &users);
    // удаление пользователя из списка
    void RemoveUser(MyClient *client);

protected:
    // подключение клиента
    void incomingConnection(int handle);

private:
    QList<MyClient *> clients;
    QWidget *widget;

};

#endif
