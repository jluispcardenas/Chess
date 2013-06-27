#include "comunication.h"

Comunication::Comunication(Board *b) : connected(false), server(0), client(0)
{
    board = b;
}

void Comunication::createConnection(bool isServer, QString ip)
{
    if (connected)
    {
        int answer = QMessageBox::question(board, tr("Chess Connection"), tr("start a new connection?"),
                    QMessageBox::Yes | QMessageBox::No);
        if (answer == QMessageBox::No)
            return;

        close();
    }

    if (isServer)
    {
        server = new QTcpServer(this);
        if (!server->listen(QHostAddress::Any, 5170)) {
            QMessageBox::information(board, tr("Chess Server"),
                                  tr("Unable to start the server: %1.")
                                  .arg(server->errorString()));
            close();
            return;
        }

        connect(server, SIGNAL(newConnection()), this, SLOT(handleConnection()));
    }
    else
    {
        client = new QTcpSocket(this);
        client->connectToHost(ip, 5170);
        setClient(client);
    }

    connected = true;
}

void Comunication::sendMessage(const QString msg)
{
    QByteArray barr;
    barr.append(msg);
    client->write(barr);
    client->flush();
}

void Comunication::handleConnection()
{
    if (!client) {
        setClient(server->nextPendingConnection());
        board->mode(HUMAN_ONLINE);
        board->restart();
    } else {
        server->nextPendingConnection()->close();
    }
}

void Comunication::readClient()
{
    if (client && client->canReadLine())
    {
        QString data = client->readLine();
        emit receiveMessage(data);
    }
}

void Comunication::setClient(QTcpSocket *c)
{
    client = c;
    connect(client, SIGNAL(readyRead()), this, SLOT(readClient()));
    connect(client, SIGNAL(disconnected()), this, SLOT(clientDisconnect()));
    connect(client, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(displayError(QAbstractSocket::SocketError)));
}

void Comunication::close()
{
    if (server && server->isListening())
        server->close();
    if (client && client->isOpen())
        client->abort();

    server = 0;
    client = 0;

    connected = false;

    board->mode(UNSTARTED);
}

void Comunication::clientDisconnect()
{
    QMessageBox::information(board, tr("Chess connection"),
                             tr("Connection lose."));
    close();
}

void Comunication::displayError(QAbstractSocket::SocketError error)
{
    switch (error) {
    default:
        QMessageBox::information(board, tr("Chess connection"),
                                 tr("The following error occurred: %1.")
                                 .arg(client->errorString()));
    }

    close();
}
