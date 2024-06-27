/**
 * @file tcpserver.h
 * @brief Main WebSocket server for robot communication.
 *
 * This file contains the declaration of the DataServer class, which sets up a WebSocket server
 * to handle communication with the robot.
 *
 * @version 0.1
 *
 * @author Szymon
 */

#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QObject>
#include <QWebSocket>
#include <QWebSocketServer>
#include <QList>
#include <cstdint>

#define POS_MSG_SIZE 11
#define DEST_MSG_SIZE 5

/**
 * @struct RxData
 * @brief Holds data related to the robot's position and status.
 *
 * The RxData struct contains fields for the robot's status flag, position (x, y), angle, and obstacle proximity.
 */
struct RxData {
    uint8_t flag;              /**< Status flag. */
    int16_t x;                 /**< X-coordinate. */
    int16_t y;                 /**< Y-coordinate. */
    int16_t ang;               /**< Angle. */
    uint8_t obstacleProximity; /**< Proximity to the obstacle. */
    int8_t rpmL;
    int8_t rpmR;
};

/**
 * @class DataServer
 * @brief The DataServer class sets up a WebSocket server for robot communication.
 *
 * This class handles incoming connections, processes messages, and sends data to clients.
 */
class DataServer : public QObject {
    Q_OBJECT
public:
    /**
     * @brief Construct a new DataServer object.
     *
     * Initializes the WebSocket server and starts listening on port 9999.
     *
     * @param[in] parent - The parent object, if any.
     */
    explicit DataServer(QObject *parent = nullptr);

    /**
     * @brief Sends the robot's position to all connected clients.
     *
     * This function sends the x and y coordinates of the robot's position to all connected clients.
     *
     * @param[out] x - The x-coordinate of the robot.
     * @param[out] y - The y-coordinate of the robot.
     */
    void sendPosition(const int16_t x, const int16_t y);

public slots:
    /**
     * @brief Processes incoming text messages.
     *
     * This function processes text messages received from clients.
     *
     * @param[in] message - The received text message.
     */
    void processTextMessage(const QString &message);

    /**
     * @brief Processes incoming binary messages.
     *
     * This function processes binary messages received from clients.
     *
     * @param[in] message - The received binary message.
     */
    void processBinaryMessage(const QByteArray &message);

    /**
     * @brief Handles new client connections.
     *
     * This function is called when a new client connects to the server.
     */
    void onNewConnection();

    /**
     * @brief Placeholder function for server closure.
     */
    void closed();

    /**
     * @brief Sends a text message to all connected clients.
     *
     * @param[in] str - The message to be sent.
     */
    void sendMessage(const QString &str);

signals:
    /**
     * @brief Signal emitted when a new position is ready.
     */
    void positionReady();

private:
    /**
     * @brief Converts two bytes back to an int16.
     *
     * @param[in] uStr - The array of bytes to be converted.
     * @return The converted int16 value.
     */
    int16_t putBackInt16(uint8_t uStr[2]);

    QWebSocketServer* server;           /**< The WebSocket server. */
    QList<QWebSocket*> clients;         /**< List of connected clients. */

public:
    RxData data; /**< The robot's data. */
};

#endif // TCPSERVER_H
