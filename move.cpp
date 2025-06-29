#include "move.h"

Move::Move()
    : from(0), to(0), score(0.0), capture(0)
{
}

Move::Move(int from, int to, double score, int capture)
    : from(from), to(to), score(score), capture(capture)
{
}

Move::Move(const move_t& moveStruct)
    : from(moveStruct.from), to(moveStruct.to), score(moveStruct.score), capture(moveStruct.capture)
{
}

int Move::getFrom() const
{
    return from;
}

int Move::getTo() const
{
    return to;
}

double Move::getScore() const
{
    return score;
}

int Move::getCapture() const
{
    return capture;
}

void Move::setFrom(int from)
{
    this->from = from;
}

void Move::setTo(int to)
{
    this->to = to;
}

void Move::setScore(double score)
{
    this->score = score;
}

void Move::setCapture(int capture)
{
    this->capture = capture;
}

move_t Move::toMoveStruct() const
{
    move_t moveStruct;
    moveStruct.from = from;
    moveStruct.to = to;
    moveStruct.score = score;
    moveStruct.capture = capture;
    return moveStruct;
}

int Move::getColumn(int position)
{
    return position / 8;
}

int Move::getRow(int position)
{
    return position % 8;
}

int Move::getPosition(int column, int row)
{
    return column * 8 + row;
}