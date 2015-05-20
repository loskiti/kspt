#include "myserver.h"

MyServer::MyServer(QWidget *widget1, QObject *parent) :QTcpServer(parent)
{
    widget = widget1;
}
// прослушка
bool MyServer::StartServer(QHostAddress addr, qint16 port)
{
    if (!listen(addr, port))
    {
            return false;
    }
     return true;
}
//уведомление о новом пользователе
void MyServer::SendToAllUserOnline(QString name)
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out << (quint16)0 << MyClient::UsersOnline << name;
    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));
    // отправка только авторизированным пользователям и не самому себе
    for (int i = 0; i < clients.length(); i++)
        if (clients.at(i)->getName() != name && clients.at(i)->getAuthorization())
            clients.at(i)->sok->write(block);
}
// уведомление, что пользователь вышел
void MyServer::SendToAllUserOffline(QString name)
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out << (quint16)0 << MyClient::UserOffline << name;
    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));
    // отправка только авторизированным пользователям и не самому себе
    for (int i = 0; i < clients.length(); ++i)
        if (clients.at(i)->getName() != name && clients.at(i)->getAuthorization())
            clients.at(i)->sok->write(block);
}
// разослать сообщение от какого-то пользователя для всех
void MyServer::SendToAllMessage(QString message, QString fromUser)
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out << (quint16)0 << MyClient::MessageToAll << fromUser << message;
    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));
    // только авторизованным пользователям и продублировать самому себе
    for (int i = 0; i < clients.length(); ++i)
        if (clients.at(i)->getAuthorization())
            clients.at(i)->sok->write(block);
}
// смс от сервера для всех
void MyServer::SendToAllServerMessage(QString message)
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out << (quint16)0 << MyClient::PublicServerMessage << message;
    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));
    for (int i = 0; i < clients.length(); ++i)
        if (clients.at(i)->getAuthorization())
            clients.at(i)->sok->write(block);
}
// приватное смс от сервера
void MyServer::SendServerMessageToUsers(QString message, const QStringList &users)
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out << (quint16)0 << MyClient::PrivateServerMessage << message;
    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));
    for (int j = 0; j < clients.length(); ++j)
        if (users.contains(clients.at(j)->getName()))
            clients.at(j)->sok->write(block);
}
// переслать приватное смс от пользователя
void MyServer::SendMessageToUsers(QString message, const QStringList &users, QString fromUsername)
{// получателям
    QByteArray block, blockToSender;
    QDataStream out(&block, QIODevice::WriteOnly);
    out << (quint16)0 << MyClient::MessageToUsers << fromUsername << message;
    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));
// отправителю
    QDataStream outToSender(&blockToSender, QIODevice::WriteOnly);
    outToSender << (quint16)0 << MyClient::MessageToUsers << users.join(";") << message;
    outToSender.device()->seek(0);
    outToSender << (quint16)(blockToSender.size() - sizeof(quint16));
    for (int j = 0; j < clients.length(); ++j)
        if (users.contains(clients.at(j)->getName()))
            clients.at(j)->sok->write(block);
        else if (clients.at(j)->getName() == fromUsername)
            clients.at(j)->sok->write(blockToSender);
}
// список пользователей
QStringList MyServer::getUsersOnline()
{
    QStringList flag;
    foreach (MyClient * c, clients)
        if (c->getAuthorization())
            flag << c->getName();
    return flag;
}
// проверка имени на допустимые символы
bool MyServer::isNameValid(QString name)
{
    if (name.length() > 20 || name.length() < 5)
        return false;
    QRegExp flag("[A-Za-z0-9_]+");
    return flag.exactMatch(name);
}
// проверка, используется ли этот ник
bool MyServer::isNameUsed(QString name)
{
    for (int i = 0; i < clients.length(); ++i)
        if (clients.at(i)->getName() == name)
            return true;
    return false;
}
// подключение клиента
void MyServer::incomingConnection(int handle)
{
    //передаем дескрпитор сокета, указатель на сервер (для вызова его методов),
    // и стандартный параметр - parent
    MyClient *client = new MyClient(handle, this, this);
    //подключаем сигналы напрямую к виджету, если его передали в конструктор сервера
    if (widget != 0)
    {
        connect(client, SIGNAL(ConcectUserToGui(QString)), widget, SLOT(AddUserToGui(QString)));
        connect(client, SIGNAL(DisconUserFromGui(QString)), widget, SLOT(RemoveUserFromGui(QString)));
        connect(client, SIGNAL(messageToGui(QString,QString,QStringList)), widget, SLOT(MessagesToGui(QString,QString,QStringList)));
    }
    connect(client, SIGNAL(DisconUser(MyClient*)), this, SLOT(onRemoveUser(MyClient*)));
    clients.append(client);
}
// удаление пользователя из списка
void MyServer::onRemoveUser(MyClient *client)
{
    clients.removeAt(clients.indexOf(client));
}

void MyServer::onMessageFromGui(QString message, const QStringList &users)
{
    if (users.isEmpty())
        SendToAllServerMessage(message);
    else
        SendServerMessageToUsers(message, users);
}
