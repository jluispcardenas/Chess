#ifndef IA_H
#define IA_H

#include "enums.h"
#include "boardevaluator.h"
#include "board.h"

class ia {
Q_OBJECT

public:
    move_t computeBestMove();
    int alphaBeta(int depth, int alpha, int beta, pieceColor color);
    const int depth = 3;
};

#endif
