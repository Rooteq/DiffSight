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

// test message: P1oGüè
void DataServer::processTextMessage(const QString &message)
{
    // switch message[0]? - read different things

    if(message.size() != POS_MSG_SIZE)
    {
        qDebug() << message.size();
        qDebug() << "Wrong message size!";
        return;
    }
    QByteArray ba = message.toLatin1();
    uint8_t *uStr = new uint8_t[message.size()];
    memcpy(uStr, ba.data(), message.size());
    this->data.flag = uStr[1];
    this->data.x = putBackInt16(&uStr[2]);
    this->data.y = putBackInt16(&uStr[4]);
    this->data.ang = putBackInt16(&uStr[6]);

    emit positionReady();
    delete[] uStr;
}

void DataServer::processBinaryMessage(const QByteArray &message)
{
    // switch message[0]? - read different things

    if(message.size() != POS_MSG_SIZE)
    {
        qDebug() << message.size();
        qDebug() << "Wrong message size!";
        return;
    }
    QByteArray ba = message;
    uint8_t *uStr = new uint8_t[message.size()];
    memcpy(uStr, ba.data(), message.size());
    this->data.flag = uStr[1];
    this->data.x = putBackInt16(&uStr[2]);
    this->data.y = putBackInt16(&uStr[4]);
    this->data.ang = putBackInt16(&uStr[6]);

    emit positionReady();
    delete[] uStr;
}

void DataServer::onNewConnection()
{
    qDebug() << "onNewConnection invoked!";
    QWebSocket *socket = server->nextPendingConnection();
    connect(socket, &QWebSocket::binaryMessageReceived, this, &DataServer::processBinaryMessage);
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


