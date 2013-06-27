#include "piece.h"
#include "board.h"

QPixmap *Piece::spriteWhite = 0;
QPixmap *Piece::spriteBlack = 0;

Piece::Piece(pieceType t, pieceColor cl, int c, int r, QWidget *parent) :
    QLabel(parent)
{
    if (!spriteWhite)
        Piece::spriteWhite = new QPixmap(":/images/whitepieces.png");
    if (!spriteBlack)
        Piece::spriteBlack = new QPixmap(":/images/blackpieces.png");

    int w = spriteWhite->height();
    row(r);
    col(c);
    x(c * w);
    y(r * w);
    type(t);
    color(cl);
    capture(false);

    changeType(type());
    move(x(), y());
}

void Piece::changeType(pieceType t)
{
    QPixmap *p = color() == WHITE ? spriteWhite : spriteBlack;
    int w = p->height();
    pieceImage = p->copy(((int)type())*w, 0, w, w);

    setPixmap(pieceImage);
    show();
}

pieceType Piece::type(pieceType t)
{
    if (t != UNKNOWN)
        this->_type = t;
    return this->_type;
}

pieceColor Piece::color(pieceColor color)
{
    if (color != NONE)
        this->_color = color;
    return this->_color;
}

int Piece::row(int r)
{
    if (r != -1)
        this->_row = r;
    return this->_row;
}

int Piece::col(int c)
{
    if (c != -1)
        this->_col = c;
    return this->_col;
}

int Piece::x(int x)
{
    if (x != -1)
        this->_x = x;
    return this->_x;
}

int Piece::y(int y)
{
    if (y != -1)
        this->_y = y;
    return this->_y;
}

bool Piece::capture(int c)
{
    if (c != -1)
        this->_capture = (bool)c;
    return this->_capture;
}

void Piece::_move(int c, int r, QPixmap *pixmap)
{
    Board *board = (Board*)this->parent();
    int capture = -1;
    if (board->validMove(type(), col(), row(), c, r, &capture, false)) {
        // save move
        if (capture != -1)
            board->capture(board->getPiece((capture/8), (capture%8)));
        board->makeMove(col(), row(), c, r);

        col(c);
        row(r);
    }

    show();
    if (pixmap)
        setPixmap(*pixmap);
    move(x(col() * 75), y(row() * 75));
}
