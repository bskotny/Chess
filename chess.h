#ifndef CHESS_H
#define CHESS_H

#include <QMainWindow>
#include <QPainter>
#include <iostream>
#include <QImage>
#include <QMouseEvent>
#include <QDebug>
using namespace std;

void draw(int, int, QPainter*);                         //function prtotypes
bool canMove(int , int , int , int);


class Chess : public QMainWindow
{
    Q_OBJECT

public:
    Chess(QWidget *parent = 0);
    void paintEvent(QPaintEvent *);
    ~Chess();

    void mousePressEvent(QMouseEvent*);             //function prtotypes
    void mouseReleaseEvent(QMouseEvent*);

    int startx;
    int starty;

    int endx;
    int endy;
};

class Piece
{
public:

    bool color;
    QImage image;

    Piece();

    Piece(bool c);

    void draw(int x, int y, QPainter* paint);
    virtual bool canMove(int startx, int starty, int endx, int endy)=0;

};

//inside of bool canMove sets the rules for each piece
class Rook : public Piece
{
public:
    Rook(bool c);
    bool canMove(int startx, int starty, int endx, int endy)
    {
        if((startx == endx) || (starty == endy))
            return true;
        else
            return false;
    }
};

class Pawn : public Piece
{
public:
    Pawn(bool c);
    bool canMove(int startx, int starty, int endx, int endy)
    {
            if(starty == endy)
                return false;
            else if(starty == 6 && abs(starty - endy) <= 2)
                return true;
            else if(starty == 1 && abs(starty - endy) <= 2)
                return true;
            else if(starty > 1 && starty < 6 && abs(starty-endy) == 1)
                return true;
            else
                return false;
    }
};

class Bishop : public Piece
{
public:
    Bishop(bool c);
    bool canMove(int startx, int starty, int endx, int endy)
    {
        if(abs(startx - endx) == abs(starty - endy))
            return true;
        else
            return false;
    }
};

class Queen : public Piece
{
public:
    Queen(bool c);
    bool canMove(int startx, int starty, int endx, int endy)
    {
        if((startx == endx) || (starty == endy) || (abs(startx - endx) == abs(starty - endy)))
            return true;
        else
            return false;
    }
};

class King : public Piece
{
public:
    King(bool c);
    bool canMove(int startx, int starty, int endx, int endy)
    {
        if(abs(startx-endx)<=1 && abs(starty-endy)<=1)
            return true;
        else
            return false;
    }
};

class Knight : public Piece
{
public:
    Knight(bool c);
    bool canMove(int startx, int starty, int endx, int endy)
    {
        if(abs(startx-endx) == 2 && abs(starty-endy) == 1)
            return true;
        else if(abs(startx-endx) == 1 && abs(starty-endy) == 2)
            return true;
        else
            return false;
    }
};

#endif // CHESS_H
