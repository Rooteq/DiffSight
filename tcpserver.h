#ifndef TCPSERVER_H
#define TCPSERVER_H
#include <QObject>
#include <QWebSocket>
#include <QWebSocketServer>
#include <QList>
// #include <QTcpSocket>
// #include <QTcpServer>

class DataServer : public QObject
{
    Q_OBJECT
public:
    explicit DataServer(QObject *parent = nullptr);

public slots:
    void processTextMessage(const QString &message);
    void onNewConnection();
    void closed();
    void sendMessage(const QString &str);

private:
    QWebSocketServer* server;
    QList<QWebSocket*> clients;
};

#endif // TCPSERVER_H
