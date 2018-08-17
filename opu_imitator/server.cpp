#include "server.h"

Server::Server()
{
}

Server::~Server()
{
    delete socket;
}

void Server::read()
{
    QByteArray datagram;
    datagram.resize(socket->pendingDatagramSize());
    QHostAddress* address = new QHostAddress();
    socket->readDatagram(datagram.data(), datagram.size(), address);

    QDataStream in(&datagram, QIODevice::ReadOnly);

    qint64 size = -1;
    if(in.device()->size() > sizeof(qint64))
    {
        in >> size;
    }
    else return;

    if (in.device()->size() - sizeof(qint64) < size) return;

    delete address;
}
