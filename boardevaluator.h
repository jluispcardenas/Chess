#ifndef BOARDEVALUATOR_H
#define BOARDEVALUATOR_H

#include "enums.h"
#include "board.h"

class BoardEvaluator {
Q_OBJECT

public:
    BoardEvaluator();
    static int getBoardScore(pieceColor color);
    static int pieceValue(char c);


    static const short pknight[64];
    static const short pbishop[64];
    static const short ppawn[64];
};

#endif
