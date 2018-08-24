#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <map>

enum Type {
    BLACK, WHITE, NONE
};

struct Point {  //the information of stone
    int px, py;  //position
    Type type;  //BLACK or WHITE or NONE
    Point() {}
    Point(int _px, int _py, Type _t) {
        px = _px, py = _py, type = _t;
    }

    Point& operator =(const Point& _p) {
        px = _p.px;
        py = _p.py;
        type = _p.type;
    }

    bool operator ==(const Point& _p) {
        if(px == _p.px && py == _p.py && type == _p.type) return true;
        else return false;
    }

    bool operator <(const Point& _p) const{
        if(px < _p.px) return true;
        else if(px > _p.px) return false;
        else {
            if(py < _p.py) return true;
            else if(py > _p.py) return false;
            else return false;
        }
    }
};

class ChessBoard : public QWidget
{
    Q_OBJECT
private:
    int N;
    Type myType;  //BLACK or WHITE or NONE
    bool myTurn;  //true means my turn, false means opponent's turn
    std::vector<Point> mp;  //record the position of all stones on the chessboard now and ever

public:
    std::map<Point, int> removed;  //record the position of stones removed in Go
    explicit ChessBoard(QWidget *parent = 0);
    void setLine(int N);
    int getLine();
    void setType(Type t);
    Type getType();
    void setTurn(bool t);
    void push_back(Point p);
    void initBoard();

signals:
    void clicked(int x, int y);

public slots:

protected:
    void paintEvent(QPaintEvent *);
    void mouseReleaseEvent(QMouseEvent *e);
};

#endif // CHESSBOARD_H
