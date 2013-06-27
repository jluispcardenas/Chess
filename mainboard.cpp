#include "mainboard.h"
#include "ui_mainboard.h"
#include "online.h"

MainBoard::MainBoard(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainBoard)
{
    ui->setupUi(this);

    board = new Board(ui->centralWidget);
    com = new Comunication(board);

    connect(ui->actionNuevo, SIGNAL(triggered()), this, SLOT(newGameDialog()));
    connect(com, SIGNAL(receiveMessage(QString)), board, SLOT(receiveCommand(QString)));
}

void MainBoard::newGameDialog()
{
    QMessageBox msg(ui->centralWidget);
    msg.setText("Chess.");
    msg.setInformativeText("Start a new game?");
    QPushButton *btnVsHuman = msg.addButton(tr("vs Human"), QMessageBox::ActionRole);
    QPushButton *btnVsComputer = msg.addButton(tr("vs Computador"), QMessageBox::ActionRole);
    QPushButton *btnOnline = msg.addButton(tr("En internet"), QMessageBox::ActionRole);
    QPushButton *btnCancel = msg.addButton(tr("Cancelar"), QMessageBox::ActionRole);

    msg.exec();

    if (msg.clickedButton() == btnVsHuman) {
        board->mode(HUMAN_HUMAN);
        board->restart();
    } else if (msg.clickedButton() == btnVsComputer) {
        board->mode(HUMAN_COMPUTER);
        board->restart();
    }
    else if (msg.clickedButton() == btnOnline) {
        Online o(this);
        o.exec();
    }
    else if (msg.clickedButton() == btnCancel)
    {
        msg.close();
    }
}

void MainBoard::startServer()
{
    com->createConnection(true);
}

void MainBoard::ipConnect(QString ip)
{
    com->createConnection(false, ip);
    board->mainColor(BLACK);
    board->mode(HUMAN_ONLINE);
    board->restart();
}

void MainBoard::sendMessage(QString msg)
{
    com->sendMessage(msg);
}

MainBoard::~MainBoard()
{
    delete ui;
    delete board;
}
