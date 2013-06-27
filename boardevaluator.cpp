#include "boardevaluator.h"

const short BoardEvaluator::pknight[64] =
        {0, 4, 8, 10, 10, 8, 4, 0,
         4, 8, 16, 20, 20, 16, 8, 4,
         8, 16, 24, 28, 28, 24, 16, 8,
         10, 20, 28, 32, 32, 28, 20, 10,
         10, 20, 28, 32, 32, 28, 20, 10,
         8, 16, 24, 28, 28, 24, 16, 8,
         4, 8, 16, 20, 20, 16, 8, 4,
         0, 4, 8, 10, 10, 8, 4, 0};

const short BoardEvaluator::pbishop[64] =
        {14, 14, 14, 14, 14, 14, 14, 14,
        14, 22, 18, 18, 18, 18, 22, 14,
        14, 18, 22, 22, 22, 22, 18, 14,
        14, 18, 22, 22, 22, 22, 18, 14,
        14, 18, 22, 22, 22, 22, 18, 14,
        14, 18, 22, 22, 22, 22, 18, 14,
        14, 22, 18, 18, 18, 18, 22, 14,
        14, 14, 14, 14, 14, 14, 14, 14};

const short BoardEvaluator::ppawn[64] =
        {0, 0, 0, 0, 0, 0, 0, 0,
        4, 4, 4, 0, 0, 4, 4, 4,
        6, 8, 2, 10, 10, 2, 8, 6,
        6, 8, 12, 16, 16, 12, 8, 6,
        8, 12, 16, 24, 24, 16, 12, 8,
        12, 16, 24, 32, 32, 24, 16, 12,
        12, 16, 24, 32, 32, 24, 16, 12,
        0, 0, 0, 0, 0, 0, 0, 0};



BoardEvaluator::BoardEvaluator()
{
}


int BoardEvaluator::getBoardScore(pieceColor color)
{
    int total = 0;
    for (int i = 0; i < 64; i++)
    {
        int c = i / 8, r = i % 8;
        char p = Board::_board[c][r];
        if (p != '\0')
        {
            pieceType type = Board::getType(p);
            pieceColor pcolor = Board::getColor(p);
            int result = 0;
            switch (type)
            {
                case KING:
                    result += 9000;
                    break;
                case QUEEN:
                    result += 1100;
                    result += pknight[i];
                    break;
                case BISHOP:
                    result += 315;
                    result += pbishop[i];
                    break;
                case KNIGHT:
                    result += 330;
                    result += pknight[i];
                    break;
                case ROOK:
                    result += 500;
                    break;
                case PAWN:
                    result += 100;
                    result += ppawn[i];
                    break;
                case UNKNOWN:
                    break;
            }

            total += (color == pcolor) ? result : -result;
        }
    }

    return total;
}


int BoardEvaluator::pieceValue(char c)
{
    int value = 0;
    switch (tolower(c))
    {
    case 'k':
        value = 9000;
        break;
    case 'q':
        value = 1100;
        break;
    case 'b':
        value = 315;
        break;
    case 'n':
        value = 330;
        break;
    case 'r':
        value = 500;
        break;
    case 'p':
        value = 100;
        break;
    }

    return value;
}
