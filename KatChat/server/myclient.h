#ifndef MYCLIENT_H
#define MYCLIENT_H
#include <QObject>
#include <QDebug>
#include <QTcpSocket>
#include <QThreadPool>
#include <QtGui>
#include <QRegExp>
#include "myserver.h"
class MyServer;

class MyClient : public QObject
{
    friend class MyServer;
    Q_OBJECT

public:
   // static const QString constNameUnknown;
    //авторизация
    static const quint8 Registration = 1;
    // когда пользователь входит в чат
    static const quint8 UserIsOnline = 2;
    // когда вошел другой пользователь
    static const quint8 UsersOnline = 3;
    //когда другой пользователь ушел
    static const quint8 UserOffline = 4;
     //смс для всех
    static const quint8 MessageToAll = 5;
    // приватное смс от пользователя
    static const quint8 MessageToUser = 6;
    //смс от сервера для всех
    static const quint8 ServerMessage = 7;
    // приватное смс от сервера
    static const quint8 PrivateServerMessage = 8;
  //  static const quint8 AutchSuccess = 9;
    // неправильный ник
    static const quint8 ErrNameInvalid = 9;
    //если ник уже используется
    static const quint8 ErrNameUsed = 10;

    explicit MyClient(int desc, MyServer *serv1, QObject *parent = 0);
    ~MyClient();
    //void setName(QString name) {name = name;}
    // имя пользователя с виджета
    QString getName(){return name;}
    //авторизирован пользователь или нет
    bool getAuthorization()  {return Authorization;}
    // отправить команду
    void SendCommand(quint8 com) ;
    // уведомление, что пользователь зашел в чат
    void SendUserIsOnline() ;

signals:
    // добавить пользователя на экран
    void ConnectUser(QString name);
    // удалить пользователя с экрана
    void DisconnectUser(QString name);
    // удаление пользователя из списка
    void DisconUser(MyClient *client);
// сообщения пользователей
    void messageUser(QString message, QString from, const QStringList &users);

private slots:
    void Connect();
    void Disconnect();
    void Options();
    void Error(QAbstractSocket::SocketError socketError) ;

private:
    QTcpSocket *sok;
    MyServer *serv;
    quint16 blockSize;
    QString name;
    bool Authorization;

};

#endif
