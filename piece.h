#ifndef PIECE_H
#define PIECE_H

#include <QLabel>
#include "enums.h"

class Piece : public QLabel
{
    Q_OBJECT
public:
    explicit Piece(pieceType type, pieceColor color, int c, int r, QWidget *parent = 0);

    pieceType type(pieceType t = UNKNOWN);
    pieceColor color(pieceColor c = NONE);
    int row(int r = -1);
    int col(int c = -1);
    int x(int x = -1);
    int y(int y = -1);
    bool capture(int c = -1);
    void changeType(pieceType t);
    void _move(int c, int r, QPixmap *pixmap = 0);

    static QPixmap *spriteWhite, *spriteBlack;

private:
    int _row, _col, _x, _y;
    bool _capture;
    pieceType _type;
    pieceColor _color;
    QPixmap pieceImage;

signals:

public slots:

};

#endif // PIECE_H
