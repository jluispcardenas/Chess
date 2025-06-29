#ifndef ENUMS_H
#define ENUMS_H

enum pieceType
{
    NORMAL,
    KING,
    QUEEN,
    KNIGHT,
    BISHOP,
    ROOK,
    PAWN,
    UNKNOWN = -1
};

enum pieceColor
{
    WHITE,
    BLACK,
    NONE = -1
};

enum gameMode
{
    HUMAN_HUMAN,
    HUMAN_COMPUTER,
    HUMAN_ONLINE,
    REPLAY,
    UNSTARTED
};

typedef struct move
{
    int from;
    int to;
    double score;
    int capture;
    inline
    friend bool operator<(const move &a, const move &b)
    {
        return a.score < b.score;
    }
} move_t;

// Utility functions
const char* pieceTypeToString(pieceType type);
const char* pieceColorToString(pieceColor color);
const char* gameModeToString(gameMode mode);

#endif // ENUMS_H
