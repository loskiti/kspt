#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :QDialog(parent), ui(new Ui::Dialog)
{
    ui->setupUi(this);
    serv = new MyServer(this, this);
    connect(this, SIGNAL(messageText(QString,QStringList)), serv, SLOT(MessageText(QString,QStringList)));
    connect(serv, SIGNAL(Writechat(QString)), this, SLOT(WriteChat(QString)));

    //по умолчанию  127.0.0.1:1234
    if (serv->StartServer(QHostAddress::LocalHost, 1234)==true)
    {
        ui->lwChat->insertItem(0, QTime::currentTime().toString()+" server strated at "+serv->serverAddress().toString()+":"+QString::number(serv->serverPort()));

    }
//    else
//    {
//        ui->lwChat->insertItem(0, QTime::currentTime().toString()+" server not strated at "+serv->serverAddress().toString()+":"+QString::number(serv->serverPort()));
//        ui->pbStartStop->setChecked(true);
//    }
}

Dialog::~Dialog()
{
    delete ui;
}
// добавить пользователя на экран
void Dialog::AddUser(QString name)
{
    ui->lwUsers->addItem(name);
    ui->lwChat->insertItem(0, QTime::currentTime().toString()+" "+name+" is online");

}
// удалить пользователя с экрана
void Dialog::DelitUser(QString name)
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
void Dialog::MessagesUser(QString message, QString from, const QStringList &users)
{
    if (users.isEmpty()==true)
        ui->lwChat->insertItem(0, QTime::currentTime().toString()+"["+from+"]: "+message);
    else
    {
        ui->lwChat->insertItem(0, QTime::currentTime().toString()+"["+from+"]("+users.join(";")+"): "+message);

    }
}

void Dialog::WriteChat(QString string)
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
    if (ui->cbToAll->isChecked()==false)
        foreach (QListWidgetItem *i, ui->lwUsers->selectedItems())
            flag << i->text();
    emit messageText(ui->pteMessage->document()->toPlainText(), flag);

    if (flag.isEmpty())
        Write("[Server]: "+ui->pteMessage->document()->toPlainText());
    else
        Write("[Server]("+flag.join(";")+"): "+ui->pteMessage->document()->toPlainText());
    ui->pteMessage->clear();
}

//void Dialog::on_cbToAll_clicked()
//{
//    if (ui->cbToAll->isChecked())
//        ui->pbSend->setText("Send To All");
//    else
//        ui->pbSend->setText("Send To Selected");
//}

//включение/выключение сервера
void Dialog::on_pbStartStop_clicked(bool checked)
{
    if (checked==true)
    {
        Write(" server stopped at "+serv->serverAddress().toString()+":"+QString::number(serv->serverPort()));
        serv->close();
        ui->pbStartStop->setText("Start server");
    }
    else
    {
        QHostAddress addr;
        if (addr.setAddress(ui->leHost->text())==false)
        {
            Write(" invalid address "+ui->leHost->text());
            return;
        }
        if (serv->StartServer(addr, ui->lePort->text().toInt())==true)
        {
            Write(" server strated at "+ui->leHost->text()+":"+ui->lePort->text());
            ui->pbStartStop->setText("Stop server");
        }
//        else
//        {
//            Write(" server not strated at "+ui->leHost->text()+":"+ui->lePort->text());
//            ui->pbStartStop->setChecked(true);
//        }
    }
}
// вывод в чат
void Dialog::Write(QString text)
{
    ui->lwChat->insertItem(0, QTime::currentTime().toString()+text);

}
