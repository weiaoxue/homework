#include "chessboard.h"
#include <QDebug>
#include <cmath>

ChessBoard::ChessBoard(QWidget *parent) : QWidget(parent)
{
    mp.clear();
    myType = NONE;
    myTurn = false;
    removed.clear();
}

void ChessBoard::initBoard() {  //initialization
    mp.clear();
    myType = NONE;
    myTurn = false;
    removed.clear();
}

void ChessBoard::setLine(int N) {  //set the size of chessboard
    this->N = N;
}

int ChessBoard::getLine() {  //get the size of chessboard
    return N;
}

void ChessBoard::setType(Type t) {  //set color
    this->myType = t;
    if(t == BLACK) myTurn = true;  //if color is BLACK, it can play first
}

Type ChessBoard::getType() {  //get color
    return myType;
}

void ChessBoard::setTurn(bool t) {  //set if it can play now
    this->myTurn = t;
}

void ChessBoard::push_back(Point p) {
    mp.push_back(p);
}

void ChessBoard::paintEvent(QPaintEvent *) {
    //set the background color of chessboard
    QPalette pal(this->palette());
    pal.setColor(QPalette::Background, QColor(211, 185, 153));
    this->setAutoFillBackground(true);
    this->setPalette(pal);

    //paint chessboard according to the size of window
    QPainter painter(this);
    const float width = this->width();
    const float height = this->height();
    const float interval = std::min(width, height) * 1.0 / N;
    const float toppadding = (height - interval * (N - 1)) / 2;
    const float leftpadding = (width - interval * (N - 1)) / 2;
    //qDebug() << N << " " << width << " " << height << " " << interval << " " << toppadding << " " << leftpadding;
    for(int i = 0; i < N; ++i) {
        painter.drawLine(QPointF(leftpadding, toppadding + interval * i), QPointF(leftpadding + interval * (N - 1), toppadding + interval * i));
        painter.drawLine(QPointF(leftpadding + interval * i, toppadding), QPointF(leftpadding + interval * i, toppadding + interval * (N - 1)));
    }

    //paint the black point on the chessboard
    if(N == 15) {
        int pos[5][2] = {3, 3, 3, 11, 7, 7, 11, 3, 11, 11};
        for(int i = 0; i < 5; ++i) {
            painter.setPen(Qt::black);
            painter.setBrush(Qt::black);
            painter.drawEllipse(QPointF(leftpadding + pos[i][0] * interval, toppadding + pos[i][1] * interval), interval * 0.125, interval * 0.125);
        }
    } else {
        int pos[9][2] = {3, 3, 3, 9, 3, 15, 9, 3, 9, 9, 9, 15, 15, 3, 15, 9, 15, 15};
        for(int i = 0; i < 9; ++i) {
            painter.setPen(Qt::black);
            painter.setBrush(Qt::black);
            painter.drawEllipse(QPointF(leftpadding + pos[i][0] * interval, toppadding + pos[i][1] * interval), interval * 0.125, interval * 0.125);
        }
    }

    /*qDebug() << "hhhhhh rrrrremove: ";
    for(std::map<Point, int>::iterator it = removed.begin(); it != removed.end(); ++it) {
        qDebug() << "map: " << it->first.px << " " << it->first.py;
    }*/

    //paint all stone on the chessboard
    for(int i = 0; i < (int)mp.size(); ++i) {
        int x = mp[i].px, y = mp[i].py;
        Point p(x, y, NONE);
        if(removed[p] == 1) continue;  //if the stone is removed, don't paint it
        if(mp[i].type == BLACK) {
            painter.setPen(Qt::black);
            painter.setBrush(Qt::black);
        } else if(mp[i].type == WHITE) {
            painter.setPen(Qt::white);
            painter.setBrush(Qt::white);
        }
        painter.drawEllipse(QPointF(leftpadding + mp[i].px * interval, toppadding + mp[i].py * interval), interval * 2 / 5, interval * 2 / 5);
    }
}

void ChessBoard::mouseReleaseEvent(QMouseEvent *e) {
    //if it isn't my turn, don't allow to click
    if(myTurn) {
        int x = e->pos().x();
        int y = e->pos().y();
        const float width = this->width();
        const float height = this->height();
        const float interval = std::min(width, height) * 1.0 / N;
        const float toppadding = (height - interval * (N - 1)) / 2;
        const float leftpadding = (width - interval * (N - 1)) / 2;
        if(x >= leftpadding && x <= width - leftpadding && y >= toppadding && y <= height - toppadding) {
            int nearx1 = (int)((x - leftpadding) / interval);
            int nearx2 = nearx1 + 1;
            int neary1 = (int)((y - toppadding) / interval);
            int neary2 = neary1 + 1;
            std::vector<std::pair<int, int> > V;  //record the nearest four points of the position clicked
            V.push_back(std::make_pair(nearx1, neary1));
            V.push_back(std::make_pair(nearx2, neary1));
            V.push_back(std::make_pair(nearx1, neary2));
            V.push_back(std::make_pair(nearx2, neary2));
            float dis = 1000.0, id = -1, tmp, tmpx, tmpy;
            for(int i = 0; i < (int)V.size(); ++i) {  //choose the nearest point among those four points
                tmpx = V[i].first * interval + leftpadding, tmpy = V[i].second * interval + toppadding;
                tmp = sqrt((x - tmpx) * (x - tmpx) + (y - tmpy) * (y - tmpy));
                if(dis - tmp > 1e-9) dis = tmp, id = i;
            }
            myTurn = false;
            emit clicked(V[id].first, V[id].second);
        }
    }
}
