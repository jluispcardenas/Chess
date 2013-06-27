#include "ia.h"
/*
ia::ia()
{
}
*/
//const int ia::depth = 3;

move_t ia::computeBestMove()
{
    int alpha = -99999;
    int beta = 99999;

    QList<move_t> moves = Board::generateValidMoves(BLACK, true);
    //moves.Sort(new SortByScore());
    move_t bestMove;

    for(int i = 0; i < moves.size(); i++)
    {
        move_t move = moves.at(i);
        char backBoard[8][8];
        Board::arrayCopy(Board::_board, backBoard, 8);
        int c = move.from / 8, r = move.from % 8, c2 = move.to / 8, r2 = move.to % 8;
        Board::_board[c2][r2] = Board::_board[c][r];
        Board::_board[c][r] = '\0';

        // PVS enhancement
        int value = -alphaBeta(depth - 1, -alpha - 1, -alpha, WHITE);
        if (value > alpha && value < beta)
        {
            value = -alphaBeta(depth - 1, -beta, -alpha, WHITE);
        }

        if (value > alpha) {
            alpha = value;
            bestMove = move;
        }
        Board::arrayCopy(backBoard, Board::_board, 8);
    }

    return bestMove;
}

int ia::alphaBeta(int depth, int alpha, int beta, pieceColor color)
{
    if (depth == 0)
        return BoardEvaluator::getBoardScore(color);

    int value = -99999;
    bool pv = false;
    pieceColor enemyColor = color == WHITE ? BLACK : WHITE;

    if (depth >= 3)
    {
        value = -alphaBeta(depth - (depth > 6 ? 3 : 2) - 1, -beta, -beta + 1, enemyColor);
        if (value >= beta)
            return beta;
    }

    QList<move_t> moves = Board::generateValidMoves(color, true);
    //moves.Sort(new SortByScore());
    for(int i = 0; i < moves.size(); i++)
    {
        move_t move = moves.at(i);
        char backBoard[8][8];
        Board::arrayCopy(Board::_board, backBoard, 8);
        int c = move.from / 8, r = move.from % 8, c2 = move.to / 8, r2 = move.to % 8;
        Board::_board[c2][r2] = Board::_board[c][r];
        Board::_board[c][r] = '\0';
        if (pv)
        {
            value = -alphaBeta(depth - 1, -alpha - 1, -alpha, enemyColor);
            if (value > alpha && value < beta)
            {
                value = -alphaBeta(depth - 1, -beta, -alpha, enemyColor);
            }
        }
        else
        {
            value = -alphaBeta(depth - 1, -beta, -alpha, enemyColor);
        }
        Board::arrayCopy(backBoard, Board::_board, 8);

        if( value >= beta )
            return beta;

        if (value > alpha)
        {
            alpha = value;
            pv = true;
        }
    }

    return alpha;
}
/*
class SortByScore : System.Collections.IComparer
{
    int System.Collections.IComparer.Compare(object a, object b)
    {
        Move ma = (Move)a;
        Move mb = (Move)b;
        if (ma.Score < mb.Score)
            return 1;
        if (ma.Score > mb.Score)
            return -1;
        else
            return 0;
    }
}*/


