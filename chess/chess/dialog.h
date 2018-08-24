#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "chessboard.h"
#include <QtNetwork>
#include <QTcpSocket>
#include <QPainter>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    Dialog(int N, QWidget *parent = 0);
    void initDialog();
    ~Dialog();

private slots:
    void on_play_clicked();
    void on_quit_clicked();
    void sendMessage(int x, int y);
    void readMessage();
    void tcpServerConnect();

private:
    Ui::Dialog *ui;
    QTcpSocket *tcpsocket;
    int N;  //15 or 19
    bool flag;  //whether click on the Play button ever or not

protected:
    void paintEvent(QPaintEvent *);
};

#endif // DIALOG_H
