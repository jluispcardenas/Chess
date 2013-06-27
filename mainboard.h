#ifndef MAINBOARD_H
#define MAINBOARD_H

#include <QMainWindow>
#include <QLabel>
#include "board.h"
#include "comunication.h"

namespace Ui {
    class MainBoard;
}

class MainBoard : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainBoard(QWidget *parent = 0);
    ~MainBoard();
    void ipConnect(QString ip);
    void startServer();
    void sendMessage(QString);

private slots:
    void newGameDialog();

private:
    Ui::MainBoard *ui;
    Board *board;
    Comunication *com;
};

#endif // MAINBOARD_H
