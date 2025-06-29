#ifndef MOVE_H
#define MOVE_H

#include "enums.h"

class Move
{
public:
    Move();
    Move(int from, int to, double score = 0.0, int capture = 0);
    Move(const move_t& moveStruct);
    
    int getFrom() const;
    int getTo() const;
    double getScore() const;
    int getCapture() const;
    
    void setFrom(int from);
    void setTo(int to);
    void setScore(double score);
    void setCapture(int capture);
    
    move_t toMoveStruct() const;
    
    static int getColumn(int position);
    static int getRow(int position);
    static int getPosition(int column, int row);
    
private:
    int from;
    int to;
    double score;
    int capture;
};

#endif // MOVE_H