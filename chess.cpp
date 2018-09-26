//Benjamin Skotny
//I completed steps 0 - 8.
#include "chess.h"

Piece* board[8][8];


Chess::Chess(QWidget *parent)
    : QMainWindow(parent)
{
    resize(44*8,44*8);

    for(int y = 0; y < 8;y++)
    {
        for(int x = 0; x < 8;x++)
        {
            board[x][y] = NULL;
        }
    }

    board[0][0] = new Rook(false);              //makes the different rooks as objects
    board[7][0] = new Rook(false);
    board[0][7] = new Rook(true);
    board[7][7] = new Rook(true);

    board[0][1] = new Pawn(false);              //creates an object in each spot as a black pawn
    board[1][1] = new Pawn(false);
    board[2][1] = new Pawn(false);
    board[3][1] = new Pawn(false);
    board[4][1] = new Pawn(false);
    board[5][1] = new Pawn(false);
    board[6][1] = new Pawn(false);
    board[7][1] = new Pawn(false);


    board[0][6] = new Pawn(true);              //creates an object in each spot as a white pawn
    board[1][6] = new Pawn(true);
    board[2][6] = new Pawn(true);
    board[3][6] = new Pawn(true);
    board[4][6] = new Pawn(true);
    board[5][6] = new Pawn(true);
    board[6][6] = new Pawn(true);
    board[7][6] = new Pawn(true);


    board[2][0] = new Bishop(false);           //creates an object in each spot as a black bishop
    board[5][0] = new Bishop(false);

    board[2][7] = new Bishop(true);           //creates an object in each spot as a white bishop
    board[5][7] = new Bishop(true);

    board[3][0] = new Queen(false);             //creates an object in each spot as a black queen
    board[3][7] = new Queen(true);             //creates an object in each spot as a white queen

    board[4][0] = new King(false);              //creates an object in each spot as a black king
    board[4][7] = new King(true);              //creates an object in each spot as a white king

    board[1][0] = new Knight(false);              //creates an object in each spot as a black knight
    board[6][0] = new Knight(false);

    board[1][7] = new Knight(true);              //creates an object in each spot as a white knight
    board[6][7] = new Knight(true);
}

Chess::~Chess()
{

}

void Chess::paintEvent(QPaintEvent *)
{
    QColor pretty(200,230,254);
    QPainter paint(this);

    for(int y = 0; y < 10; y++)         //creates the chess board
    {
        for(int x = 0; x < 10; x++)
        {
        paint.drawRect(0+44*x,0+44*y,44,44);
        if(((x%2 == 0) && (y%2 == 0)) || ((x%2 == 1) && (y%2 == 1)))
            paint.fillRect(x*44,y*44,44,44,QColor(177,113,24));
        else
            paint.fillRect(x*44,y*44,44,44,QColor(233,174,95));
        }
    }
    for(int y = 0; y < 8; y++)
    {
        for(int x = 0; x < 8; x++)
        {
           if(board[x][y]!= NULL)
               board[x][y]->draw(x,y,&paint);           //calls the method draw to draw the pieces
        }
    }
}

Piece::Piece(bool c)
{
    color = c;
}

//this set of code dtermines the color of the pieces
Rook::Rook(bool c):Piece(c)
{
    if(color == true)
        image=QPixmap("wrook.gif").toImage();
    else
    {
        image=QPixmap("brook.gif").toImage();
    }
}

Pawn::Pawn(bool c):Piece(c)
{
    if(color == true)
        image=QPixmap("wpawn.gif").toImage();
    else
    {
        image=QPixmap("bpawn.gif").toImage();
    }
}

Bishop::Bishop(bool c):Piece(c)
{
    if(color == true)
        image=QPixmap("wbishop.gif").toImage();
    else
    {
        image=QPixmap("bbishop.gif").toImage();
    }
}

Queen::Queen(bool c):Piece(c)
{
    if(color == true)
        image=QPixmap("wqueen.gif").toImage();
    else
    {
        image=QPixmap("bqueen.gif").toImage();
    }
}

King::King(bool c):Piece(c)
{
    if(color == true)
        image=QPixmap("wking.gif").toImage();
    else
    {
        image=QPixmap("bking.gif").toImage();
    }
}

Knight::Knight(bool c):Piece(c)
{
    if(color == true)
        image=QPixmap("wknight.gif").toImage();
    else
    {
        image=QPixmap("bknight.gif").toImage();
    }
}

void Piece::draw(int x, int y, QPainter* paint)     //draws the pieces
{
    paint->drawImage(x*44,y*44,image);
}

void Chess::mousePressEvent(QMouseEvent* event)         //gets the coordinates of where the mouse starts
{
    event->x() / 44;
    event->y() / 44;

    startx = event->x() / 44;
    starty = event->y() / 44;

}

bool canMove(int startx, int starty, int endx, int endy)
{
    bool isValid = false;
    bool isEmpty = false;
    bool canCapture = false;
    bool whitePawn = false;
    bool blackPawn = false;

    if(board[endx][endy] !=NULL && board[endx][endy]->color!=board[startx][starty]->color)
        isValid = true;

    if(board[endx][endy] !=NULL && board[endx][endy]->color==board[startx][starty]->color)
        return false;

    if(board[startx][starty]->image == QPixmap("wknight.gif").toImage() ||          //special case for the knight
            board[startx][starty]->image == QPixmap("bknight.gif").toImage())
    {
        isValid =true;
        canCapture = true;
        isEmpty = true;
    }

    if(board[startx][starty]->image == QPixmap("bpawn.gif").toImage())      //if it is a BlackPawn, these bolleans are set
    {
            canCapture = false;
            isValid = true;
            isEmpty = true;
            blackPawn = true;
    }

    if(board[startx][starty]->image == QPixmap("wpawn.gif").toImage())      //if it is a whitePawn, these booleans are set
    {
            canCapture = false;
            isValid = true;
            isEmpty = true;
            whitePawn = true;
    }

    if(board[startx][starty] != NULL)                   //checks to make sure there is a piece at startx and starty
    {
        int moveBetweenX = abs(startx - endx);
        int moveBetweenY = abs(starty - endy);
        if(startx == endx)                  //veritcal up movement
        {
            if(starty > endy)
            {
            if (blackPawn)      //black pawn can not move up
            {
                canCapture=false;
                isValid = false;
                isEmpty = false;
            }
            if (whitePawn)      //white pawn cannot capture moving forward
            {
                canCapture=false;
                isValid = false;
                isEmpty = false;
            }
            for(int k = 1; k <= moveBetweenY;k++)
            {
                if(((board[startx][starty - k]) == NULL) && (!blackPawn))        //tests to make sure there are no pieces in the way
                {
                    isEmpty = true;
                    canCapture = true;
                }
                else if((board[startx][starty - k]) != NULL && isValid)     //moving into next box, and checks to make sure the next box is a different color
                {
                    if ((starty-k) > endy)                                  //tries to capture another piece, however there is a piece in the way
                    {
                        isEmpty = false;
                        isValid = false;
                        canCapture= true;
                        break;
                    }
                    else                                 //A piece is captured, and there is no pieces in the way
                    {
                      canCapture = true;
                      isEmpty = true;
                      break;
                    }
                }
                else                        //when going up, a piece is in the way
                {
                    isEmpty = false;
                    canCapture = false;
                    break;
                }
            }
            }
            else    //in vertical down
            { 
            if (whitePawn)      //white pawn cannot move down
            {
                canCapture=false;
                isValid = false;
                isEmpty = false;
            }
            if (blackPawn)      //black pawn cannot capture moving down
            {
                canCapture=false;
                isValid = false;
                isEmpty = false;
            }
            for(int k = 1; k <= moveBetweenY;k++)
            {
                if(((board[startx][starty + k]) == NULL) && (!whitePawn))
                {
                    isEmpty = true;
                    canCapture = true;
                }
                else if((board[startx][starty + k]) != NULL && isValid) //piece exists veritcal down
                {
                    if ((starty+k) < endy)
                    {
                        isEmpty = false;
                        canCapture= true;
                        break;
                    }
                    else
                    {
                      //vertical down else piece
                      canCapture = true;
                      isEmpty = true;
                      break;
                    }
                }
                else
                {
                    //veritcal down in way
                    isEmpty = false;
                    canCapture = false;
                    break;
                }
            }
            }
        }
        else if(starty == endy)
        {
            if(startx > endx)       //in horizontal left
            {
            for(int c = 1; c <= moveBetweenX;c++)
            {
                if((board[startx - c][starty]) == NULL)
                {
                    isEmpty = true;
                    canCapture = true;
                }
                else if((board[startx - c][starty]) != NULL && isValid)
                {   //piece exists horizontal left
                    if ((startx-c) > endx)
                    {
                        isEmpty = false;
                        canCapture= true;
                        break;
                    }
                    else
                    {
                      canCapture = true;
                      isEmpty = true;
                      break;
                    }
                }
                else
                {
                    //horizontal left blocked
                    isEmpty = false;
                    canCapture = false;
                    break;
                }
            }
            }
            else
            {
            //in horizontal right
            for(int c = 1; c <= moveBetweenX;c++)
            {
                if((board[startx + c][starty]) == NULL)
                {
                    isEmpty = true;
                    canCapture = true;
                }
                else if((board[startx + c][starty]) != NULL && isValid)
                {
                    if ((startx+c) < endx)
                    {
                        isEmpty = false;
                        canCapture= true;
                        break;
                    }
                    else
                    {
                      canCapture = true;
                      isEmpty = true;
                      break;
                    }
                }
                else
                {
                    //horiontal right blocked
                    isEmpty = false;
                    canCapture = false;
                    break;
                }
            }
            }
        }
        else if(abs(moveBetweenX) == abs(moveBetweenY))
        {
            if((endx > startx) && (starty > endy))
            {
            //in diagonal top right
            if (blackPawn)
            {
                //black pawn cannot move dia top right
                canCapture=false;
                isValid = false;
                isEmpty = false;
            }
            if((board[startx + 1][starty - 1] == NULL) && (whitePawn == true))
            {
                //white pawn cannot move dia top right when the spot is null
                canCapture = false;
                isValid = false;
                isEmpty = false;
                whitePawn = true;
            }
            for(int i = 1; i <= moveBetweenX;i++)
            {
             if(((board[startx + i][starty - i]) == NULL) && (!blackPawn) && (!whitePawn))
             {
                isEmpty = true;
                canCapture = true;
             }
             else if((board[startx + i][starty - i]) != NULL && isValid)
             {
                 if ((startx+i) < endx && (starty-i) > endy)
                 {
                     isEmpty = false;
                     canCapture= true;
                     break;
                 }
                 else
                 {
                   canCapture = true;
                   isEmpty = true;
                   break;
                 }
             }
             else
                {
                //diagonal top right blocked
                isEmpty = false;
                canCapture = false;
                break;
                }
            }
            }
            else if((startx > endx) && (starty > endy))
            {
            //in diagonal top left
            if (blackPawn)
            {
                //black pawn cannot move dia top left
                canCapture=false;
                isValid = false;
                isEmpty = false;
            }
            if((board[startx - 1][starty - 1] == NULL) && (whitePawn))
            {
                //white pawn cannot move dia top left when the spot is null
                canCapture = false;
                isValid = false;
                isEmpty = false;
            }
            for(int i = 1; i <= moveBetweenX;i++)
            {
             if(((board[startx - i][starty - i]) == NULL) && (!blackPawn) && (!whitePawn))
             {
                isEmpty = true;
                canCapture = true;
             }
             else if((board[startx - i][starty - i]) != NULL && isValid)
             {
                 if ((startx-i) > endx && (starty-i) > endy)
                 {
                     isEmpty = false;
                     canCapture= true;
                     break;
                 }
                 else
                 {
                   canCapture = true;
                   isEmpty = true;
                   break;
                 }
             }
             else
                {
                //diagonal top left blocked
                isEmpty = false;
                canCapture = false;
                break;
                }
            }
            }
            else if((startx > endx) && (endy > starty))
            {
            //in diagonal bottom left
            if (whitePawn)
            {
                //white pawn cannot move dia bot left
                canCapture=false;
                isValid = false;
                isEmpty = false;
            }
            if((board[startx - 1][starty + 1] == NULL) && (blackPawn))
            {
                //black pawn cannot move dia bot left when the spot is null
                canCapture = false;
                isValid = false;
                isEmpty = false;
            }
            for(int i = 1; i <= moveBetweenX;i++)
            {
             if(((board[startx - i][starty + i]) == NULL) && (!whitePawn) && (!blackPawn))
             {
                isEmpty = true;
                canCapture = true;
             }
             else if((board[startx - i][starty + i]) != NULL && isValid)
             {
                 if ((startx-i) > endx && (starty+i) < endy)
                 {
                     isEmpty = false;
                     canCapture= true;
                     break;
                 }
                 else
                 {
                   canCapture = true;
                   isEmpty = true;
                   break;
                 }
             }
             else
                {
                //diagonal bottom left blocked
                isEmpty = false;
                canCapture = false;
                break;
                }
            }
            }
            else
            {
            //in diagonal bottom right
            if (whitePawn)
            {
                //white pawn cannot move dia bottom right
                canCapture=false;
                isValid = false;
                isEmpty = false;
            }
            if((board[startx + 1][starty + 1] == NULL) && (blackPawn))
            {
                //black pawn cannot move dia bot right when the spot is null
                canCapture = false;
                isValid = false;
                isEmpty = false;
            }
            for(int i = 1; i <= moveBetweenX;i++)
            {
             if(((board[startx + i][starty + i]) == NULL) && (!whitePawn) && (!blackPawn))
             {
                isEmpty = true;
                canCapture = true;
             }
             else if((board[startx + i][starty + i]) != NULL && isValid)
             {
                 if ((startx+i) < endx && (starty+i) < endy)
                 {
                     isEmpty = false;
                     canCapture= true;
                     break;
                 }
                 else
                 {
                   canCapture = true;
                   isEmpty = true;
                   break;
                 }
             }
             else
                {
                //diagonal bottom right blocked
                isEmpty = false;
                canCapture = false;
                break;
                }
            }
            }
        }
        if((isEmpty == true) && (canCapture == true))
        {
            if(board[startx][starty]->canMove(startx, starty, endx, endy))
            {
                //VALID MOVE
                return true;
                board[endx][endy]=board[startx][starty];
                board[startx][starty]=NULL;
                //repaint();
             }
             else
                cout << "invalid move" << endl;
        }
     }
        else
            if((board[endx][endy] == NULL) && board[startx][starty]->canMove(startx, starty, endx, endy))
            {
                return true;
                //Moving to blank
            }
    return false;
}

void Chess::mouseReleaseEvent(QMouseEvent* event)       //gets the coordinates of where the mouse ends
{
    event->x() / 44;
    event->y() / 44;
    qDebug() << "END " << event->x() / 44 << ", " << event->y() / 44;

    endx = event->x() / 44;
    endy = event->y() / 44;

    bool isValid = false;
    bool isEmpty = false;
    bool canCapture = false;
    bool blackPawn = false;

    if((startx < 0) || ((starty >7)))                   //checks to make sure the startx and starty are on the board
        return;

    if((endx < 0) || ((endy >7)))                       //checks to make sure the endx and endy are on the board
        return;

    if(board[startx][starty] == NULL)
        return;

    if(board[startx][starty] == board[endx][endy])          //checks to see if the mouse press and release are at the same spot
    {
        //Same spot
        return;
    }

    if(board[endx][endy] != NULL && board[endx][endy]->color==board[startx][starty]->color)     //checks to see if the piece is moving to a piece of the same color
    {
        isValid = false;
        //invalid move to same color
        return;
    }

    if(canMove(startx,starty,endx, endy) == false)
        cout <<"can't move" << endl;
    else
    {
        board[endx][endy]=board[startx][starty];
        board[startx][starty]=NULL;

        while(true)
        {
            startx = rand()% 8;
            starty = rand()% 8;
            endx = rand()% 8;
            endy = rand()% 8;
            if(board[startx][starty] == NULL)
                continue;
            else if(canMove(startx,starty,endx,endy) == false)
                continue;
            else if(board[startx][starty]->color == true)
                continue;
            else
            {
                board[endx][endy]=board[startx][starty];
                board[startx][starty]=NULL;
                repaint();
                break;
            }
        }
    }

    //repaint();

}
