#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QDebug>
#include <queue>
#include "value.h"

enum StoneType {
    BLACK, WHITE, NONE
};

template <int N>
class GameBoard
{
    StoneType board[N][N];
public:
    Array aryX, aryY;  //removed stone in Go
    int size;  //the size of aryX and aryY

    GameBoard() {
        for(int i = 0; i < N; ++i)
            for(int j = 0; j < N; ++j)
                board[i][j] = NONE;
        aryX = Array();
        aryY = Array();
    }

    void init() {  //initialization
        for(int i = 0; i < N; ++i)
            for(int j = 0; j < N; ++j)
                board[i][j] = NONE;
        aryX = Array();
        aryY = Array();
    }

    bool putStone(int x, int y, StoneType stone) {  //return whether the stone can be put on this position or not
        if(x < 0 || x >= N || y < 0 || y >= N) return false;
        if(N == 15) {  //Five
            if(board[x][y] == NONE) {
                board[x][y] = stone;
                return true;
            } else return false;
        } else {  //Go
            if(board[x][y] == BLACK || board[x][y] == WHITE) {
                return false;
            } else {
                StoneType _t = board[x][y];
                board[x][y] = stone;
                if(isLive(x, y, stone) || (!isLive(x, y, stone) && canKill(x, y, stone))) {
                    //if the stone is alive after it is put on this position
                    //or the stone is dead after it is put on this position, but it can kill the stones of opponent
                    //then the stone can be put on this position
                    return true;
                } else {
                    board[x][y] = _t;
                    return false;
                }
            }
        }
    }

    bool isLive(int x, int y, StoneType stone) {  //return whether the stone is alive after it is put on this position or not in Go
        int dir[4][2] = {-1, 0, 0, -1, 1, 0, 0, 1};
        bool flag[N][N];
        memset(flag, false, sizeof(flag));
        std::queue<std::pair<int, int> > Q;
        while(!Q.empty()) Q.pop();
        int qi = 0;
        Q.push(std::make_pair(x, y));
        flag[x][y] = true;
        while(!Q.empty()) {
            int tmpx = Q.front().first, tmpy = Q.front().second;
            Q.pop();
            for(int j = 0; j < 4; ++j) {
                int ttmpx = tmpx + dir[j][0], ttmpy = tmpy + dir[j][1];
                if(ttmpx < 0 || ttmpx >= N || ttmpy < 0 || ttmpy >= N || flag[ttmpx][ttmpy]) continue;
                if(board[ttmpx][ttmpy] == NONE) qi++;
                else if(board[ttmpx][ttmpy] == stone) {
                    Q.push(std::make_pair(ttmpx, ttmpy));
                    flag[ttmpx][ttmpy] = true;
                }
            }
        }
        if(qi == 0) return false;
        else return true;
    }

    bool canKill(int x, int y, StoneType stone) {  //return whether the stone can kill the stones of opponent after it is put on this position or not in Go
        int dir[4][2] = {-1, 0, 0, -1, 1, 0, 0, 1};
        for(int i = 0; i < 4; ++i) {
            int tmpx = x + dir[i][0], tmpy = y + dir[i][1];
            if(tmpx < 0 || tmpx >= N || tmpy < 0  || tmpy >= N || stone == board[tmpx][tmpy] || board[tmpx][tmpy] == NONE) continue;
            if(!isLive(tmpx, tmpy, board[tmpx][tmpy])) return true;
        }
        return false;
    }

    bool removeStone(int x, int y) {
        //return whether the stone can kill the stones of opponent after it is put on this position or not in Go
        //and if yes, record the positions of removed stones in aryX and aryY
        qDebug() << "removeStone";
        int dir[4][2] = {-1, 0, 0, -1, 1, 0, 0, 1};
        bool flag[N][N];
        bool f = false;
        memset(flag, false, sizeof(flag));
        std::queue<std::pair<int, int> > Q;
        aryX.clear();
        aryY.clear();
        Array tmpAryX = Array();  //record the positions of stones in the same group
        Array tmpAryY = Array();
        for(int i = 0; i < 4; ++i) {
            int tmpx = x + dir[i][0], tmpy = y + dir[i][1];
            if(tmpx < 0 || tmpx >= N || tmpy < 0  || tmpy >= N || flag[tmpx][tmpy] || board[x][y] == board[tmpx][tmpy] || board[tmpx][tmpy] == NONE) continue;
            while(!Q.empty()) Q.pop();
            int qi = 0;
            Q.push(std::make_pair(tmpx, tmpy));
            tmpAryX.clear();
            tmpAryY.clear();
            tmpAryX.push_back(tmpx);
            tmpAryY.push_back(tmpy);
            qDebug() << "first: " << tmpx << " " << tmpy << " " << board[tmpx][tmpy];
            flag[tmpx][tmpy] = true;
            while(!Q.empty()) {
                tmpx = Q.front().first, tmpy = Q.front().second;
                Q.pop();
                for(int j = 0; j < 4; ++j) {
                    int ttmpx = tmpx + dir[j][0], ttmpy = tmpy + dir[j][1];
                    if(ttmpx < 0 || ttmpx >= N || ttmpy < 0 || ttmpy >= N || flag[ttmpx][ttmpy]) continue;
                    qDebug() << "queue: " << ttmpx << " " << ttmpy << " " << board[ttmpx][ttmpy];
                    if(board[ttmpx][ttmpy] == NONE) qi++;
                    else if(board[ttmpx][ttmpy] == board[tmpx][tmpy]) {
                        Q.push(std::make_pair(ttmpx, ttmpy));
                        tmpAryX.push_back(ttmpx);
                        tmpAryY.push_back(ttmpy);
                        flag[ttmpx][ttmpy] = true;
                    }
                }
            }
            if(qi == 0) {
                //if the stones in the group are dead
                //then remove these stones and record the positions of removed stones in aryX and aryY
                for(int j = 0; j < tmpAryX.size(); ++j) aryX.push_back(tmpAryX[j]);
                for(int j = 0; j < tmpAryY.size(); ++j) aryY.push_back(tmpAryY[j]);
                f = true;
            }
        }
        size = aryX.size();
        //change the removed stones into NONE
        for(int i = 0; i < aryX.size(); ++i) {
            board[aryX[i].to_int()][aryY[i].to_int()] = NONE;
        }
        return f;
    }

    StoneType checkStone(int x, int y) {
        //whether it wins after the stone is put on this position or not in Five
        //direction from left to right
        int i, j, cnt = 0;
        for(i = x - 1; i >= 0 && i >= x - 4; i--) {
            if(board[i][y] != board[x][y]) break;
            cnt++;
        }
        if(cnt == 4) return board[x][y];
        for(i = x + 1; i < N && i <= x + 4; i++) {
            if(board[i][y] != board[x][y]) break;
            cnt++;
        }
        if(cnt >= 4) return board[x][y];
        //direction from top to bottom
        cnt = 0;
        for(i = y - 1; i >= 0 && i >= y - 4; i--) {
            if(board[x][i] != board[x][y]) break;
            cnt++;
        }
        if(cnt == 4) return board[x][y];
        for(i = y + 1; i < N && i <= y + 4; i++) {
            if(board[x][i] != board[x][y]) break;
            cnt++;
        }
        if(cnt >= 4) return board[x][y];
        //direction from left top to right bottom
        cnt = 0;
        for(i = x - 1, j = y - 1; i >= 0 && j >= 0 && i >= x - 4 && j >= y - 4; i--, j--) {
            if(board[i][j] != board[x][y]) break;
            cnt++;
        }
        if(cnt == 4) return board[x][y];
        for(i = x + 1, j = y + 1; i < N && j < N && i <= x + 4 && j <= y + 4; i++, j++) {
            if(board[i][j] != board[x][y]) break;
            cnt++;
        }
        if(cnt >= 4) return board[x][y];
        //direction from left bottom to right top
        cnt = 0;
        for(i = x - 1, j = y + 1; i >= 0 && j < N && i >= x - 4 && j <= y + 4; i--, j++) {
            if(board[i][j] != board[x][y]) break;
            cnt++;
        }
        if(cnt == 4) return board[x][y];
        for(i = x + 1, j = y - 1; i < N && j >= 0 && i <= x + 4 && j >= y - 4; i++, j--) {
            if(board[i][j] != board[x][y]) break;
            cnt++;
        }
        if(cnt >= 4) return board[x][y];
        //if it doesn't win, return NONE
        return NONE;
    }

    static const int boardSize() {
        return N;
    }
};

#endif // GAMEBOARD_H
