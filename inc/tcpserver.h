#ifndef TCPSERVER_H
#define TCPSERVER_H
#include <QObject>
#include <QWebSocket>
#include <QWebSocketServer>
#include <QList>
#include <cstdint>
// #include <QTcpSocket>
// #include <QTcpServer>

#define POS_MSG_SIZE 8

struct RxData
{
    uint8_t flag;
    int16_t x;
    int16_t y;
    int16_t ang;
};

class DataServer : public QObject
{
    Q_OBJECT
public:
    explicit DataServer(QObject *parent = nullptr);

public slots:
    void processTextMessage(const QString &message);
    void processBinaryMessage(const QByteArray &message);
    void onNewConnection();
    void closed();
    void sendMessage(const QString &str);

signals:
    void positionReady();

private:
    int16_t putBackInt16(uint8_t uStr[2])
    {
        int16_t data = (static_cast<int16_t>(uStr[0]) << 8) | uStr[1];
        return data;
    }

    QWebSocketServer* server;
    QList<QWebSocket*> clients;
public:
    RxData data;
};

#endif // TCPSERVER_H
