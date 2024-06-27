#include "tcpserver.h"

DataServer::DataServer(QObject *parent)
    : QObject{parent}
{
    server = new QWebSocketServer(QStringLiteral("WebServer"), QWebSocketServer::NonSecureMode, this);

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

void DataServer::sendPosition(const int16_t x, const int16_t y)
{
    uint8_t msg[DEST_MSG_SIZE];
    msg[0] = 'D';

    msg[2] = (uint8_t)(x & 0xFF);
    msg[1] = (uint8_t)((x >> 8) & 0xFF);
    msg[4] = (uint8_t)(y & 0xFF);
    msg[3] = (uint8_t)((y >> 8) & 0xFF);

    QByteArray byteMsg;
    byteMsg.resize(DEST_MSG_SIZE);

    memcpy(byteMsg.data(), msg, DEST_MSG_SIZE);

    for(int i = 0; i < DEST_MSG_SIZE; ++i)
    {
        qDebug() << (uint8_t)byteMsg[i];
    }

    for(auto x : clients)
    {
        x->sendBinaryMessage(byteMsg);
    }

    qDebug() << "message sent";
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
    this->data.obstacleProximity = uStr[8];

    this->data.rpmL = uStr[9];
    this->data.rpmR = uStr[10];

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

int16_t DataServer::putBackInt16(uint8_t uStr[2])
{
    int16_t data = (static_cast<int16_t>(uStr[0]) << 8) | uStr[1];
    return data;
}

void DataServer::closed()
{
    // placeholder
}

void DataServer::sendMessage(const QString &str)
{
    for(auto x : clients)
    {
        x->sendTextMessage(str);
    }
    qDebug() << "message sent";
}


