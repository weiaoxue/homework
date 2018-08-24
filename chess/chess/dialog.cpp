#include "dialog.h"
#include "ui_dialog.h"
#include <QDebug>
#include "value.h"
#include <QMessageBox>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::Dialog(int N, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    this->N = N;
    flag = false;
    initDialog();
    connect(ui->cb, SIGNAL(clicked(int,int)), this, SLOT(sendMessage(int,int)));
}

void Dialog::initDialog() {  //initialization
    ui->cb->setLine(N);
    ui->cb->initBoard();
    ui->cb->update();
}

Dialog::~Dialog()
{
    delete ui;
}

QString stoq(std::string s) {  //change std::string to QString
    return QString::fromStdString(s);
}

std::string qtos(QString str) {  // change QString to std::string
    return str.toStdString();
}

void Dialog::on_play_clicked()
{
    flag = true;
    ui->play->setEnabled(false);
    tcpServerConnect();  //when the Play button is clicked, connect to server
    sendMessage(-1, ui->cb->getLine());  //send message whose type is greeting
}

void Dialog::on_quit_clicked()
{
    if(flag) sendMessage(-2, -2);  //if the Play button has been clicked ever, send message to disconnect to server
    this->close();
}

void Dialog::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    int width = this->width();
    int height = this->height();
    //display the color of stone
    if(ui->cb->getType() == BLACK) {
        painter.setBrush(Qt::black);
        painter.drawEllipse(QPointF(width * 0.9, height / 6.0), width / 20.0, width / 20.0);
    } else if(ui->cb->getType() == WHITE) {
        painter.setPen(Qt::white);
        painter.setBrush(Qt::white);
        painter.drawEllipse(QPointF(width * 0.9, height / 6.0), width / 20.0, width / 20.0);
    }
}

void Dialog::tcpServerConnect() {  //connect to server
    tcpsocket = new QTcpSocket(this);
    tcpsocket->abort();
    QHostAddress address;
    address.setAddress(ui->ipLineEdit->text());
    tcpsocket->connectToHost(address, 6666);
    connect(tcpsocket, SIGNAL(readyRead()), this, SLOT(readMessage()));
}

void Dialog::readMessage() {
    QDataStream in(tcpsocket);
    in.setVersion(QDataStream::Qt_5_8);
    QString str;
    in >> str;
    qDebug() << "received message: " << str;
    Object obj(qtos(str));
    if(obj["type"].to_string() == "greeting") {
        ui->cb->setType(obj["toplayer"].to_int() == 0 ? BLACK : WHITE);
        update();
    } else if(obj["type"].to_string() == "process") {
        if(obj["success"].to_int() == 1 || obj["success"].to_int() == -1) {  //put stone on the chessboard successfully
            int x = obj["posx"].to_int(), y = obj["posy"].to_int();
            Type t = obj["color"].to_int() == 0 ? BLACK : WHITE;
            Point p(x, y, t);
            ui->cb->push_back(p);
            if(ui->cb->removed[p] == 1) ui->cb->removed[p] = 0;
            ui->cb->update();
            if(obj["success"].to_int() == 1) ui->cb->setTurn(false);  //if the stone is put by me, then it isn't my turn
            else ui->cb->setTurn(true);
        } else {  //put stone on the chessboard unsuccessfully, then it's my turn
            ui->cb->setTurn(true);
        }
    } else if(obj["type"].to_string() == "finished") {  //Five
        int x = obj["posx"].to_int(), y = obj["posy"].to_int();
        Type t = obj["color"].to_int() == 0 ? BLACK : WHITE;
        Point p(x, y, t);
        ui->cb->push_back(p);
        ui->cb->update();
        QString msg;
        if(t == ui->cb->getType()) msg = "Congratulations!\n";
        else msg = "Sorry!\n";
        if(t == BLACK) msg += "Black win!";
        else msg += "White win!";
        QMessageBox::StandardButton box = QMessageBox::information(this, "", msg);
        if(box == QMessageBox::Ok) {
            sendMessage(-2, -2);  //send message to disconnect to server
            ui->play->setEnabled(true);
            initDialog();
        }
    } else {  //Go
        int x = obj["posx"].to_int(), y = obj["posy"].to_int();
        Type t = obj["color"].to_int() == 0 ? BLACK : WHITE;
        Point p(x, y, t);
        ui->cb->push_back(p);
        if(obj["success"].to_int() == 1) ui->cb->setTurn(false);
        else ui->cb->setTurn(true);
        if(ui->cb->removed[p] == 1) ui->cb->removed[p] = 0;
        for(int i = 0; i < obj["size"].to_int(); ++i) {
            int tmpx = obj["removex"][i].to_int(), tmpy = obj["removey"][i].to_int();
            Point p(tmpx, tmpy, NONE);
            ui->cb->removed[p] = 1;
        }
        ui->cb->update();
    }
}

void Dialog::sendMessage(int x, int y) {
    Object obj;
    if(x == -1) {  //greeting
        obj["type"] = (std::string)"greeting";
        obj["option"] = ui->cb->getLine() == 15 ? (std::string)"five" : (std::string)"go";
    } else if(x == -2) {  //finished
        obj["type"] = (std::string)"finished";
    } else {  //process
        obj["type"] = (std::string)"process";
        obj["option"] = ui->cb->getLine() == 15 ? (std::string)"five" : (std::string)"go";
        obj["posx"] = x;
        obj["posy"] = y;
        obj["color"] = ui->cb->getType() == BLACK ? 0 : 1;
    }
    QString str = stoq(obj.to_json());
    QByteArray msg;
    QDataStream out(&msg, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_8);
    out << str;
    tcpsocket->write(msg);
}
