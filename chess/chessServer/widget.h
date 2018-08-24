#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include <QList>
#include "gameboard.h"

namespace Ui {
class Widget;
}

enum Type {
    FIVE, GO, NO
};

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:
    Type myType;  //Five or Go
    Ui::Widget *ui;
    QTcpSocket *tcpsocket;
    QTcpServer *tcpserver;
    QList<QTcpSocket*> *socket_list;
    GameBoard<15> five;
    GameBoard<19> go;

private slots:
    void newConnect();
    void sendMessage(int id, QString info);
    void readMessage();
};

#endif // WIDGET_H
