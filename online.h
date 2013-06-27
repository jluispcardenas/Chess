#ifndef ONLINE_H
#define ONLINE_H

#include "mainboard.h"
#include <QDialog>

class Online : public QDialog
{
    Q_OBJECT

public:
    Online(MainBoard*);
    ~Online();
    void startServer();
    void ipConnect();
};

#endif
