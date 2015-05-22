#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :QDialog(parent), ui(new Ui::Dialog)
{
    ui->setupUi(this);


    serv = new MyServer(this, this);

    //подключаем сигналы от виджета к серверу
    connect(this, SIGNAL(messageFromGui(QString,QStringList)), serv, SLOT(onMessageFromGui(QString,QStringList)));
    connect(serv, SIGNAL(WriteToGui(QString)), this, SLOT(onWriteToGui(QString)));

    //по умолчанию  127.0.0.1:1234
    if (serv->StartServer(QHostAddress::LocalHost, 1234))
    {
        ui->lwChat->insertItem(0, QTime::currentTime().toString()+" server strated at "+serv->serverAddress().toString()+":"+QString::number(serv->serverPort()));

    }
    else
    {
        ui->lwChat->insertItem(0, QTime::currentTime().toString()+" server not strated at "+serv->serverAddress().toString()+":"+QString::number(serv->serverPort()));
        ui->pbStartStop->setChecked(true);
    }
}

Dialog::~Dialog()
{
    delete ui;
}
// добавить пользователя
void Dialog::AddUserToGui(QString name)
{
    ui->lwUsers->addItem(name);
    ui->lwChat->insertItem(0, QTime::currentTime().toString()+" "+name+" is online");

}
// удалить пользователя
void Dialog::DelitUserFromGui(QString name)
{
    for (int i = 0; i < ui->lwUsers->count(); i++)
        if (ui->lwUsers->item(i)->text() == name)
        {
            ui->lwUsers->takeItem(i);
            ui->lwChat->insertItem(0, QTime::currentTime().toString()+" "+name+" if offline");
            break;
        }
}
// сообщения пользователей
void Dialog::MessagesToGui(QString message, QString from, const QStringList &users)
{
    if (users.isEmpty())
        ui->lwChat->insertItem(0, QTime::currentTime().toString()+"["+from+"]: "+message);
    else
    {
        ui->lwChat->insertItem(0, QTime::currentTime().toString()+"["+from+"]("+users.join(";")+"): "+message);

    }
}

void Dialog::onWriteToGui(QString string)
{
    Write(string);
}
// сообщения сервера
void Dialog::on_pbSend_clicked()
{
    if (ui->lwUsers->count() == 0)
    {
        QMessageBox::information(this, "", "No clients connected");
        return;
    }
    QStringList flag;
    if (!ui->cbToAll->isChecked())
        foreach (QListWidgetItem *i, ui->lwUsers->selectedItems())
            flag << i->text();
    emit messageFromGui(ui->pteMessage->document()->toPlainText(), flag);

    if (flag.isEmpty())
        Write("[Server]: "+ui->pteMessage->document()->toPlainText());
    else
        Write("[Server]("+flag.join(";")+"): "+ui->pteMessage->document()->toPlainText());
    ui->pteMessage->clear();
}



//включение/выключение сервера
void Dialog::on_pbStartStop_clicked(bool checked)
{
    if (checked)
    {
        Write(" server stopped at "+serv->serverAddress().toString()+":"+QString::number(serv->serverPort()));
        serv->close();
        ui->pbStartStop->setText("Start server");
    }
    else
    {
        QHostAddress addr;
        if (!addr.setAddress(ui->leHost->text()))
        {
            Write(" invalid address "+ui->leHost->text());
            return;
        }
        if (serv->StartServer(addr, ui->lePort->text().toInt()))
        {
            Write(" server strated at "+ui->leHost->text()+":"+ui->lePort->text());
            ui->pbStartStop->setText("Stop server");
        }
        else
        {
            Write(" server not strated at "+ui->leHost->text()+":"+ui->lePort->text());
            ui->pbStartStop->setChecked(true);
        }
    }
}
// вывод в чат
void Dialog::Write(QString text)
{
    ui->lwChat->insertItem(0, QTime::currentTime().toString()+text);

}
