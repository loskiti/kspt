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
    connect(sok, SIGNAL(readyRead()), this, SLOT(onSokReadyRead()));
    connect(sok, SIGNAL(connected()), this, SLOT(onSokConnected()));
    connect(sok, SIGNAL(disconnected()), this, SLOT(onSokDisconnected()));
    connect(sok, SIGNAL(error(QAbstractSocket::SocketError)),this, SLOT(onSokDisplayError(QAbstractSocket::SocketError)));
}

Dialog::~Dialog()
{
    delete ui;
}
//ошибки
void Dialog::onSokDisplayError(QAbstractSocket::SocketError socketError)
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
void Dialog::onSokReadyRead()
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
//        case MyClient::comAutchSuccess:
//        {
//            ui->pbSend->setEnabled(true);
//            AddToLog("Enter as "+name);
//        }
//        break;
        // когда пользователь входит в чат
        case MyClient::comUsersOnline:
        {
            AddToLog(name+" is online");
            ui->pbSend->setEnabled(true);
            QString users;
            data >> users;
            if (users == "")
                return;
            QStringList flag =  users.split(",");
            ui->lwUsers->addItems(flag);
            break;
        }

        //смс от сервера для всех
        case MyClient::comPublicServerMessage:
        {
            QString message;
            data >> message;
            AddToLog("[Server]: "+message);
            break;
        }

        //смс для всех
        case MyClient::comMessageToAll:
        {
            QString user;
            data >> user;
            QString message;
            data >> message;
            AddToLog("["+user+"]: "+message);
            break;
        }

        // приватное смс от пользователя
        case MyClient::comMessageToUsers:
        {
            QString user;
            data >> user;
            QString message;
            data >> message;
            AddToLog("["+user+"](private): "+message);
             break;
        }

        // приватное смс от сервера
        case MyClient::comPrivateServerMessage:
        {
            QString message;
            data >> message;
            AddToLog("[Server(private)]: "+message);
            break;
        }

        // когда вошел другой пользователь
        case MyClient::comUserJoin:
        {
            QString name;
            data >> name;
            ui->lwUsers->addItem(name);
            AddToLog(name+" is online");
            break;
        }

//когда другой пользователь ушел
        case MyClient::comUserLeft:
        {
            QString name;
            data >> name;
            for (int i = 0; i < ui->lwUsers->count(); i++)
                if (ui->lwUsers->item(i)->text() == name)
                {
                    ui->lwUsers->takeItem(i);
                    AddToLog(name+" is offline");
                    break;
                }
           break;
        }
        // неправильный ник
        case MyClient::comErrNameInvalid:
        {
            QMessageBox::information(this, "Ошибка", "неправильный ник");
            sok->disconnectFromHost();
            break;
        }

        //если ник уже используется
        case MyClient::comErrNameUsed:
        {
            QMessageBox::information(this, "Ошибка", "ник уже используется");
            sok->disconnectFromHost();
            break;
        }

    }
}
// подключение
void Dialog::onSokConnected()
{
    ui->pbConnect->setEnabled(false);
    ui->pbDisconnect->setEnabled(true);
    blockSize = 0;
    AddToLog("Connected to server"+sok->peerAddress().toString());

    //try autch
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out << (quint16)0;
    out << (quint8)MyClient::comAutchReq;
    out << ui->leName->text();
    name = ui->leName->text();
    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));
    sok->write(block);
}
// отключение
void Dialog::onSokDisconnected()
{
    ui->pbConnect->setEnabled(true);
    ui->pbDisconnect->setEnabled(false);
    ui->pbSend->setEnabled(false);
    ui->lwUsers->clear();
    AddToLog("Disconnected from server"+sok->peerAddress().toString());
}
//сигнал на подключение к серверу
void Dialog::on_pbConnect_clicked()
{
    sok->connectToHost(ui->leHost->text(), ui->sbPort->value());
}
//сигнал на отключение
void Dialog::on_pbDisconnect_clicked()
{
    sok->disconnectFromHost();
}

//void Dialog::on_cbToAll_clicked()
//{
//    if (ui->cbToAll->isChecked())
//        ui->pbSend->setText("For all");
//    else
//        ui->pbSend->setText("Send To Selected");
//}
// отправка смс
void Dialog::on_pbSend_clicked()
{
//    QByteArray data;
//    QDataStream out(&data, QIODevice::WriteOnly);
//  out << (quint16)0;
//    if (ui->cbToAll->isChecked())
//        out << (quint8)MyClient::comMessageToAll;
//    else
//    {
//        out << (quint8)MyClient::comMessageToUsers;
//        QString s;
//        foreach (QListWidgetItem *i, ui->lwUsers->selectedItems())
//            s += i->text()+",";
//        s.remove(s.length()-1, 1);
//        out << s;
//    }

//    out << ui->pteMessage->document()->toPlainText();
//    out.device()->seek(0);
//    out << (quint16)(data.size() - sizeof(quint16));
//    sok->write(data);
//    ui->pteMessage->clear();
}

void Dialog::AddToLog(QString text)
{
    ui->lwLog->insertItem(0, QTime::currentTime().toString()+" "+text);

}
