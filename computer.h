#ifndef COMPUTER_H
#define COMPUTER_H

#include <QThread>

class Computer : QThread
{
public:
    Computer(QObject *parent);
    void nextMove() {
    }
};

#endif // COMPUTER_H
