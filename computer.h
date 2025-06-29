#ifndef COMPUTER_H
#define COMPUTER_H

#include <QThread>
#include <QObject>
#include "enums.h"

class Computer : public QThread
{
    Q_OBJECT

public:
    Computer(QObject *parent);
    void requestMove();

signals:
    void moveReady(move_t move);

protected:
    void run() override;

private:
    bool moveRequested;
};

#endif // COMPUTER_H
