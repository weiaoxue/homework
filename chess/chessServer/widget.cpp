#include "widget.h"
#include "ui_widget.h"
#include "time.h"
#include <QTime>
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    myType = NO;

    //waiting for connection
    tcpserver = new QTcpServer(this);
    tcpsocket = new QTcpSocket(this);
    socket_list = new QList<QTcpSocket*>;
    tcpserver->listen(QHostAddress::Any, 6666);
    connect(tcpserver, SIGNAL(newConnection()), this, SLOT(newConnect()));

    //using for random number
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
}

Widget::~Widget()
{
    delete ui;
}

QString stoq(std::string s) {  //change std::string to QString
    return QString::fromStdString(s);
}

std::string qtos(QString str) {  //change QString to std::string
    return str.toStdString();
}

void Widget::newConnect() {
    tcpsocket = tcpserver->nextPendingConnection();
    socket_list->append(tcpsocket);
    connect(tcpsocket, SIGNAL(readyRead()), this, SLOT(readMessage()));
    if(socket_list->length() == 2) {  //when the number of connection is 2
        qsrand(time(NULL));
        int r = qrand() % 2;  //random number from 0 to 1

        Object obj;
        obj["type"] = (std::string)"greeting";
        obj["toplayer"] = r;
        QString str = stoq(obj.to_json());
        sendMessage(0, str);

        obj["toplayer"] = 1 - r;
        str = stoq(obj.to_json());
        sendMessage(1, str);

        five.init();
        go.init();
    }
}

void Widget::readMessage() {
    QString msg;
    int i;
    for(i = 0; i < socket_list->length(); ++i) {
        QDataStream in(socket_list->at(i));
        in.setVersion(QDataStream::Qt_5_8);
        in >> msg;
        if(!msg.isEmpty()) break;
    }
    ui->textBrowser->append(tr("received client message: '%1'").arg(msg));
    Object obj(qtos(msg));
    if(obj["type"].to_string() == "greeting") {  //if type is greeting
        if(obj["option"].to_string() == "five") {  //if it is Five
            myType = FIVE;
        } else {  //if it is Go
            myType = GO;
        }
    } else if(obj["type"].to_string() == "finished") {  // if type is finished, then disconnect
        connect(socket_list->at(i), SIGNAL(disconnected()), socket_list->at(i), SLOT(deleteLater()));
        socket_list->at(i)->disconnectFromHost();
        socket_list->removeAt(i);
    } else {  //if type is process
        if(myType == FIVE) {  //Five
            int x = obj["posx"].to_int(), y = obj["posy"].to_int();
            StoneType t = obj["color"].to_int() == 0 ? BLACK : WHITE;
            if(five.putStone(x, y, t)) {  //whether the stone can be put on this position or not in Five
                Object obj2;
                obj2["posx"] = x, obj2["posy"] = y, obj2["color"] = t == BLACK ? 0 : 1;
                obj2["success"] = 1;
                if(five.checkStone(x, y) == t) {  //whether it wins or not
                    obj2["type"] = (std::string)"finished";
                    //send to two clients that the stone is put on the chessboard successfully and someone win
                    for(int j = 0; j < socket_list->length(); ++j)
                        sendMessage(j, stoq(obj2.to_json()));
                } else {  //send to two clients that the stone is put on the chessboard successfully
                    obj2["type"] = (std::string)"process";
                    sendMessage(i, stoq(obj2.to_json()));
                    obj2["success"] = -1;
                    sendMessage(1 - i, stoq(obj2.to_json()));
                }
            } else {  //send to the client received message from that the stone isn't put on the chessboard
                Object obj2;
                obj2["type"] = (std::string)"process";
                obj2["posx"] = x, obj2["posy"] = y, obj2["color"] = t == BLACK ? 0 : 1;
                obj2["success"] = 0;
                sendMessage(i, stoq(obj2.to_json()));
            }
        } else {  //Go
            int x = obj["posx"].to_int(), y = obj["posy"].to_int();
            StoneType t = obj["color"].to_int() == 0 ? BLACK : WHITE;
            if(go.putStone(x, y, t)) {  //whether the stone can be put on this position or not in Go
                Object obj2;
                obj2["posx"] = x, obj2["posy"] = y, obj2["color"] = t == BLACK ? 0 : 1;
                obj2["success"] = 1;
                if(go.removeStone(x, y)) {  //whether it can kill the stones of opponent or not
                    obj2["type"] = (std::string)"remove";
                    obj2["removex"] = Array();
                    obj2["removex"] = go.aryX;
                    obj2["removey"] = Array();
                    obj2["removey"] = go.aryY;
                    obj2["size"] = go.size;
                    sendMessage(i, stoq(obj2.to_json()));
                    obj2["success"] = -1;
                    sendMessage(1 - i, stoq(obj2.to_json()));
                } else {
                    obj2["type"] = (std::string)"process";
                    sendMessage(i, stoq(obj2.to_json()));
                    obj2["success"] = -1;
                    sendMessage(1 - i, stoq(obj2.to_json()));
                }
            } else {
                Object obj2;
                obj2["type"] = (std::string)"process";
                obj2["posx"] = x, obj2["posy"] = y, obj2["color"] = t == BLACK ? 0 : 1;
                obj2["success"] = 0;
                sendMessage(i, stoq(obj2.to_json()));
            }
        }
    }
}

void Widget::sendMessage(int id, QString info) {
    qDebug() << "send to " << id << " : " << info;
    QByteArray msg;
    QDataStream out(&msg, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_8);
    out << info;
    socket_list->at(id)->write(msg);
}
