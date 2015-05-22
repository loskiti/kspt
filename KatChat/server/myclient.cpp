#include "myclient.h"

//const QString MyClient::constNameUnknown = QString(".Unknown");
// ????????
MyClient::MyClient(int desc, MyServer *serv1, QObject *parent) :QObject(parent)
{

    serv = serv1;
    Authorization = false;
   // name = /*constNameUnknown*/QString(".Unknown");
    blockSize = 0;
    sok = new QTcpSocket(this);
    //????????? ????? ? ??????
    sok->setSocketDescriptor(desc);
    //?????????? ???????
    connect(sok, SIGNAL(connected()), this, SLOT(Connect()));
    connect(sok, SIGNAL(disconnected()), this, SLOT(Disconnect()));
    connect(sok, SIGNAL(readyRead()), this, SLOT(Options()));
    connect(sok, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(Error(QAbstractSocket::SocketError)));

   // qDebug() << "Client connected" << desc;
}

MyClient::~MyClient()
{

}

void MyClient::Connect()
{
    //автоматически
}
// выход из клиента
void MyClient::Disconnect()
{
   // qDebug() << "Client disconnected";
    if (Authorization==true)
    {

        emit DisconnectUser(name);
        serv->SendToAllUserOffline(name);
        emit DisconUser(this);
    }
    deleteLater();
}
//ошибки
void MyClient::Error(QAbstractSocket::SocketError socketError)
{
    QWidget window;
    switch (socketError) {
    //удалённый узел закрывает соединение
    case QAbstractSocket::RemoteHostClosedError:
        break;
       // Адрес узла не найден
    case QAbstractSocket::HostNotFoundError:
        QMessageBox::information(&window, "??????", "// Адрес узла не найден");
        break;
        //Соединение было разорвано другим узлом (или по тайм-ауту)
    case QAbstractSocket::ConnectionRefusedError:
        QMessageBox::information(&window, "??????", "?????????? ???? ????????? ?????? ????? (??? ?? ????-????).");
        break;
    default:
        QMessageBox::information(&window, "??????", "????????? ??????: "+sok->errorString());
    }

}
// действия
void MyClient::Options()
{
    QDataStream data(sok);

    if (blockSize == 0) {

        if (sok->bytesAvailable() < (int)sizeof(quint16))
            return;

        data >> blockSize;
       // qDebug() << "_blockSize now " << _blockSize;
    }

    if (sok->bytesAvailable() < blockSize)
        return;
    else

        blockSize = 0;

    quint8 command;
    data >> command;
   // qDebug() << "Received command " << command;
    //все команды кроме запроса авторизации от неавторизованного пользователя игнорируются
    if (Authorization==false && command != Registration)
        return;

    switch(command)
    {
        //авторизация
        case Registration:
        {

            QString  user;
            data >> user;
 // неправильный ник
            if (serv->isNameValid(user)==false)
            {
                SendCommand(ErrNameInvalid);
                return;
            }
            //если ник уже используется
            if (serv->isNameUsed(user)==true)
            {

                SendCommand(ErrNameUsed);
                return;
            }
            // если все нормально
            name = user;
            Authorization = true;
            SendUserIsOnline();
            emit ConnectUser(user);
            serv->SendToAllUserOnline(name);
            break;
        }

        //смс для всех
        case MessageToAll:
        {
            QString message;
            data >> message;
            serv->SendToAllMessage(message, name);
            emit messageUser(message, name, QStringList());
            break;
        }

        // приватное смс для пользователя
        case MessageToUser:
        {
            QString users;
            data >> users;
            QString message;
            data >> message;
            QStringList flag = users.split(";");
            serv->SendMessageToUsers(message, flag, name);
            emit messageUser(message, name, flag);
            break;
        }

    }


}
// отправить команду
void MyClient::SendCommand(quint8 com)
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out << (quint16)0;
    out << com;
    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));
    sok->write(block);
   // qDebug() << "Send to" << name << "command:" << comm;
}
// отправить положительный ответ на авторизацию и список клиентов, которые онлайн
void MyClient::SendUserIsOnline()
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out << (quint16)0;
    out << UserIsOnline;
    QStringList flag = serv->getUsersOnline();
    QString stroka;
    for (int i = 0; i < flag.length(); i++)
        if (flag.at(i) != name)
            stroka += flag.at(i)+(QString)";";
    stroka.remove(stroka.length()-1, 1);
    out << stroka;
    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));
    sok->write(block);
   // qDebug() << "Send user list to" << name << ":" << s;
}


