#include "dialog.h"
#include "ui_dialog.h"

#include <QtGui>
#include <QDebug>
//подкласс

Dialog::Dialog(QWidget *parent) :QDialog(parent),ui(new Ui::Dialog)
{
    ui->setupUi(this);
// новый сокет
    sok = new QTcpSocket(this);
    //подключаем сигналы
    connect(sok, SIGNAL(readyRead()), this, SLOT(SokRead()));
    connect(sok, SIGNAL(connected()), this, SLOT(SokConnected()));
    connect(sok, SIGNAL(disconnected()), this, SLOT(SokDisconnected()));
    connect(sok, SIGNAL(error(QAbstractSocket::SocketError)),this, SLOT(SokDisplayError(QAbstractSocket::SocketError)));
}

Dialog::~Dialog()
{
    delete ui;
}
//ошибки
void Dialog::SokDisplayError(QAbstractSocket::SocketError socketError)
{
    switch (socketError) {
    //удалённый узел закрывает соединение
    case QAbstractSocket::RemoteHostClosedError:
        break;
        //Адрес узла не найден
    case QAbstractSocket::HostNotFoundError:
        QMessageBox::information(this, "Ошибка", "Адрес узла не найден.");
        break;
        //Соединение было разорвано другим узлом (или по тайм-ауту)
    case QAbstractSocket::ConnectionRefusedError:
        QMessageBox::information(this, "Ошибка", "Соединение было разорвано другим узлом (или по тайм-ауту)");
        break;
    default:
        QMessageBox::information(this, "Ошибка", "Произошла ошибка: "+sok->errorString());
    }
}
//получение данных
void Dialog::SokReadyRead()
{// в каждом блоке первые 2 байта - размер, 3 байт - команда, дальше информация
    QDataStream data(sok);

    if (blockSize == 0) {

        if (sok->bytesAvailable() < (int)sizeof(quint16))
            return;
        data >> blockSize;
          }

    if (sok->bytesAvailable() < blockSize)
        return;
    else
        blockSize = 0;

        quint8 command;
    data >> command;


    switch (command)
    {
       
        // когда пользователь входит в чат
        case Client::UsersOnline:
        {
            Read(name+" is online");
            ui->pbSend->setEnabled(true);
            QString users;
            data >> users;
            if (users == "")
                return;
            QStringList flag =  users.split(";");
            ui->lwUsers->addItems(flag);
            break;
        }

        //смс от сервера для всех
        case Client::PublicServerMessage:
        {
            QString message;
            data >> message;
            Read("[Server]: "+message);
            break;
        }

        //смс для всех
        case Client::MessageToAll:
        {
            QString user;
            data >> user;
            QString message;
            data >> message;
            Read("["+user+"]: "+message);
            break;
        }

        // приватное смс от пользователя
        case Client::MessageToUsers:
        {
            QString user;
            data >> user;
            QString message;
            data >> message;
            Read("["+user+"](private): "+message);
             break;
        }

        // приватное смс от сервера
        case Client::PrivateServerMessage:
        {
            QString message;
            data >> message;
            Read("[Server(private)]: "+message);
            break;
        }

        // когда вошел другой пользователь
        case Client::UserOnline:
        {
            QString name;
            data >> name;
            ui->lwUsers->addItem(name);
            Read(name+" is online");
            break;
        }

//когда другой пользователь ушел
        case Client::UserOffline:
        {
            QString name;
            data >> name;
            for (int i = 0; i < ui->lwUsers->count(); i++)
                if (ui->lwUsers->item(i)->text() == name)
                {
                    ui->lwUsers->takeItem(i);
                    Read(name+" is offline");
                    break;
                }
           break;
        }
        // неправильный ник
        case Client::ErrNameInvalid:
        {
            QMessageBox::information(this, "Ошибка", "неправильный ник");
            sok->disconnectFromHost();
            break;
        }

        //если ник уже используется
        case Client::ErrNameUsed:
        {
            QMessageBox::information(this, "Ошибка", "ник уже используется");
            sok->disconnectFromHost();
            break;
        }

    }
}
// подключение
void Dialog::SokConnected()
{
    ui->pbConnect->setEnabled(false);
    ui->pbDisconnect->setEnabled(true);
    blockSize = 0;
    Read("Connected to server"+sok->peerAddress().toString());

 
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out << (quint16)0;
    out << (quint8)Client::AutchReq;
    out << ui->leName->text();
    name = ui->leName->text();
    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));
    sok->write(block);
}
// отключение
void Dialog::SokDisconnected()
{
    ui->pbConnect->setEnabled(true);
    ui->pbDisconnect->setEnabled(false);
    ui->pbSend->setEnabled(false);
    ui->lwUsers->clear();
    Read("Disconnected from server"+sok->peerAddress().toString());
}
//сигнал на подключение к серверу
void Dialog::on_pbConnect_clicked()
{
    sok->connectToHost(ui->leHost->text(), ui->sbPort->value());
	// дописать
}
//сигнал на отключение
void Dialog::on_pbDisconnect_clicked()
{
    sok->disconnectFromHost();
}


// отправка смс
void Dialog::on_pbSend_clicked()
{
    QByteArray data;
    QDataStream out(&data, QIODevice::WriteOnly);
  out << (quint16)0;
    if (ui->cbToAll->isChecked())
       out << (quint8)Client::MessageToAll;
    else
    {
        out << (quint8)Client::MessageToUsers;
        QString s;
        foreach (QListWidgetItem *i, ui->lwUsers->selectedItems())
           s += i->text()+";";
       
        out << s;
    }

    out << ui->pteMessage->document()->toPlainText();
//   дописать
   ui->pteMessage->clear();
}
// вывод на экран
void Dialog::Read(QString text)
{
    ui->lwLog->insertItem(0, QTime::currentTime().toString()+" "+text);

}
