#include "computer.h"
#include "ia.h"

Computer::Computer(QObject *parent)
    : QThread(parent), moveRequested(false)
{
}

void Computer::requestMove()
{
    moveRequested = true;
    if (!isRunning()) {
        start();
    }
}

void Computer::run()
{
    while (moveRequested) {
        moveRequested = false;
        
        ia aiEngine;
        move_t bestMove = aiEngine.computeBestMove();
        
        emit moveReady(bestMove);
    }
}
