#include "tcpserver.h"

DataServer::DataServer(QObject *parent)
    : QObject{parent}
{
    server = new QWebSocketServer(QStringLiteral("DupaServer"), QWebSocketServer::NonSecureMode, this);

    if(!server->listen(QHostAddress::Any, 9999))
    {
        qDebug() << "Server could not start";
    }
    else
    {
        connect(server, &QWebSocketServer::newConnection, this, &DataServer::onNewConnection);
        //connect(server, SIGNAL(QWebSocketServer::closed()), this, SLOT(closed()));
        qDebug() << "Server started!";
    }
}

void DataServer::processTextMessage(const QString &message)
{
    qDebug()  << message;
}


void DataServer::onNewConnection()
{
    qDebug() << "onNewConnection invoked!";
    QWebSocket *socket = server->nextPendingConnection();
    connect(socket, &QWebSocket::textMessageReceived, this, &DataServer::processTextMessage);
    clients << socket;
}

void DataServer::closed()
{
    // lolz
}

void DataServer::sendMessage(const QString &str)
{    
    for(auto x : clients)
    {
        x->sendTextMessage(str);
    }
    qDebug() << "message sent";
}


