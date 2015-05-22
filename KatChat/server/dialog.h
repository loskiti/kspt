#ifndef DIALOG_H
#define DIALOG_H

#include <QDebug>
#include <QtGui>
#include <QtCore>
#include "myserver.h"

namespace Ui {
    class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private:
    Ui::Dialog *ui;
    MyServer *serv;
    // вывод в чат
    void Write(QString text);

signals:
    // набор сообщения
    void messageText(QString message, const QStringList &users);

public slots:
    // добавить пользователя на экран
    void AddUser(QString name);
    // удалить пользователя с экрана
    void DelitUser(QString name);
    // сообщения пользователей
    void MessagesUser(QString message, QString from, const QStringList &users);
    // вывод на экран
    void WriteChat(QString string);

private slots:
    // сообщения сервера
    void on_pbSend_clicked();
    //включение/выключение сервера
    void on_pbStartStop_clicked(bool checked);
};

#endif
