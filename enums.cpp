#include "enums.h"

const char* pieceTypeToString(pieceType type)
{
    switch (type) {
        case KING: return "King";
        case QUEEN: return "Queen";
        case ROOK: return "Rook";
        case BISHOP: return "Bishop";
        case KNIGHT: return "Knight";
        case PAWN: return "Pawn";
        case NORMAL: return "Normal";
        default: return "Unknown";
    }
}

const char* pieceColorToString(pieceColor color)
{
    switch (color) {
        case WHITE: return "White";
        case BLACK: return "Black";
        default: return "None";
    }
}

const char* gameModeToString(gameMode mode)
{
    switch (mode) {
        case HUMAN_HUMAN: return "Human vs Human";
        case HUMAN_COMPUTER: return "Human vs Computer";
        case HUMAN_ONLINE: return "Human vs Online";
        case REPLAY: return "Replay";
        default: return "Unstarted";
    }
}
