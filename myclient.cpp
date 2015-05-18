#include "myclient.h"

const QString MyClient::constNameUnknown = QString(".Unknown");
// подкласс
MyClient::MyClient(int desc, MyServer *serv1, QObject *parent) :QObject(parent)
{

    serv = serv1;
    Authorization = false;
    _name = constNameUnknown;
    _blockSize = 0;
    sok = new QTcpSocket(this);
    //соединяем сокет и клиент
    sok->setSocketDescriptor(desc);
    //подключаем сигналы
    connect(sok, SIGNAL(connected()), this, SLOT(Connect()));
    connect(sok, SIGNAL(disconnected()), this, SLOT(Disconnect()));
    connect(sok, SIGNAL(readyRead()), this, SLOT(Options()));
    connect(sok, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(Error(QAbstractSocket::SocketError)));

   
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
   
    if (Authorization)
    {

        emit DisconUserFromGui(_name);
        serv->doSendToAllUserLeft(_name);
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
        QMessageBox::information(&window, "Ошибка", "Адрес узла не найден");
        break;
        //Соединение было разорвано другим узлом (или по тайм-ауту)
    case QAbstractSocket::ConnectionRefusedError:
        QMessageBox::information(&window, "Ошибка", "Соединение было разорвано другим узлом (или по тайм-ауту).");
        break;
    default:
        QMessageBox::information(&window, "Ошибка", "Произошла ошибка: "+sok->errorString());
    }

}
// действия
void MyClient::Options()
{
    QDataStream data(sok);

    if (_blockSize == 0) {

        if (sok->bytesAvailable() < (int)sizeof(quint16))
            return;

        data >> _blockSize;
       
    }

    if (sok->bytesAvailable() < _blockSize)
        return;
    else

        _blockSize = 0;

    quint8 command;
    data >> command;
  
    //все команды кроме запроса авторизации от неавторизованного пользователя игнорируются
    if (!Authorization && command != AutchReq)
        return;

    switch(command)
    {
        //авторизация
        case AutchReq:
        {

            QString name;
            data >> name;
 // неправильный ник
            if (!serv->isNameValid(name))
            {
                SendCommand(ErrNameInvalid);
                return;
            }
            //если ник уже используется
            if (serv->isNameUsed(name))
            {

                SendCommand(ErrNameUsed);
                return;
            }
            // если все нормально
            _name = name;
            Authorization = true;
            SendUserIsOnline();
            emit ConcectUserToGui(name);
            serv->doSendToAllUserJoin(_name);
            break;
        }

        //смс для всех
        case MessageToAll:
        {
            QString message;
            data >> message;
            serv->doSendToAllMessage(message, _name);
            emit messageToGui(message, _name, QStringList());
            break;
        }

        // приватное смс для пользователя
        case MessageToUsers:
        {
            QString users_on;
            data >> users_on;
            QString message;
            data >> message;
            QStringList flag = users_on.split(";");
            serv->doSendMessageToUsers(message, flag, _name);
            emit messageToGui(message, _name, flag);
            break;
        }

    }


}
// отправить команду
void MyClient::SendCommand(quint8 comm)
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out << (quint16)0;
    out << comm;
    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));
    sok->write(block);
   
}
// отправить положительный ответ на авторизацию и список клиентов, которые онлайн
void MyClient::SendUserIsOnline() const
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out << (quint16)0;
    out << UserIsOnline;
    QStringList flag = serv->getUsersOnline();
    QString s;
    for (int i = 0; i < flag.length(); i++)
        if (flag.at(i) != _name)
            s += flag.at(i)+(QString)";";
    s.remove(s.length()-1, 1);
    out << s;
    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));
    sok->write(block);
  
}


