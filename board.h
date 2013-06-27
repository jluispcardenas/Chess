#ifndef BOARD_H
#define BOARD_H

#include <QWidget>
#include <QPainter>
#include <QtGui>
#include <QHash>
#include <math.h>
#include "computer.h"
#include "enums.h"
#include "piece.h"

QT_BEGIN_NAMESPACE
class QDragEnterEvent;
class QDropEvent;
QT_END_NAMESPACE

#define max(a, b) (a>b ? a : b)

class Board : public QWidget
{
    Q_OBJECT

public slots:
    void receiveCommand(QString);
    void onMoveReady(move_t);

public:
    Board(QWidget* parent);
    ~Board();
    void drawBoard(QPainter *p);
    void restart();
    static pieceColor mainColor(pieceColor c = NONE);
    gameMode mode(gameMode m);
    gameMode mode();
    bool gameOver(int g = -1);
    bool myTurn(pieceColor c);
    bool myTurn();
    static pieceColor getColor(char c);
    static pieceType getType(char c);
    static bool validMove(pieceType type, int c, int r, int dc, int dr, int *capture, bool first = false);
    static int blocked(int ac, int ar, int bc, int br);
    void makeMove(int ac, int ar, int bc, int br, bool intern = false);
    void capture(Piece *cpiece);
    static QList<move_t> generateValidMoves(pieceColor color, bool calc = false);
    Piece* getPiece(int c, int r);
    int fix(int n);
    static void arrayCopy(char arr[][8], char arr2[][8], int s);

    static char _board[8][8];

private:
    void save(int c, int r, Piece *pc);
    bool checkCheck(pieceColor color);
    void checkAlert();
    int getPos(char p, int distinct = -1);

    Computer *computer;
    bool whites;
    static const char ids[6];
    static pieceColor _mainColor;
    gameMode _gameMode;
    bool _gameOver;
    bool _attach;
    Piece *curDrag;
    QHash<int, Piece*> _pieces;
    QPixmap *lightTile, *darkTile;

protected:
    void paintEvent(QPaintEvent *e);
    void dragEnterEvent(QDragEnterEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void dropEvent(QDropEvent *event);
    void mousePressEvent(QMouseEvent *event);
};

#endif // BOARD_H
