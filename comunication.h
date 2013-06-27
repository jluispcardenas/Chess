#ifndef COMUNICATION_H
#define COMUNICATION_H

#include <QObject>
#include <QString>
#include <QtGui>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include "board.h"
#include "enums.h"

class Comunication : public QObject

{
    Q_OBJECT
public:
    Comunication(Board*);
    void createConnection(bool, QString ip = "");
    void sendMessage(const QString);

signals:
    void receiveMessage(QString);

private slots:
    void handleConnection();
    void readClient();
    void clientDisconnect();
    void displayError(QAbstractSocket::SocketError);

private:
    void setClient(QTcpSocket*);
    void close();

    QTcpServer *server;
    QTcpSocket *client;
    Board *board;
    bool connected;
};

#endif // COMUNICATION_H
