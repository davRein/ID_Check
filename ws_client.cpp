#include "ws_client.h"
#include "json_objects.h"

QT_USE_NAMESPACE

//! [constructor]
//! Creates a ID_Check instance (client)
//! @param url: URL of the server
//! @param debug: enable/disable qDebug() functionality
WS_Client::WS_Client(const QUrl &url, bool debug, QObject *parent) :
    QObject(parent),
    m_url(url),
    m_debug(debug)
{
    // Connect MACROS for the gate application
    connect(&m_webSocket_dummyGate, &QWebSocket::connected, this, &WS_Client::onConnected_dummyGate);
    connect(&m_webSocket_dummyGate, &QWebSocket::disconnected, this, &WS_Client::closed_dummyGate);

    // Connect MACROS for the io_control application
    connect(&m_webSocket_dummyIO_Control, &QWebSocket::connected, this, &WS_Client::onConnected_dummyIO_Control);
    connect(&m_webSocket_dummyIO_Control, &QWebSocket::disconnected, this, &WS_Client::closed_dummyIO_Control);

    // Tell the sockets which url they has to use
    m_webSocket_dummyGate.open(QUrl(url));
    m_webSocket_dummyIO_Control.open(QUrl(url));
}
//! [constructor]

//! [onConnected]
//! SLOT to connect to the dummy gate app on the server
void WS_Client::onConnected_dummyGate()
{
    m_webSocket_dummyGate.sendTextMessage(obj.readJsonFile(obj.getFn_dir() + obj.getFn_ID_0_Send_gate()));
    if (m_debug){
        qDebug() << "WebSocket dummyGate connected";
    }
    connect(&m_webSocket_dummyGate, &QWebSocket::textMessageReceived, this, &WS_Client::onTextMessageReceived_dummyGate);
}
//! [onConnected]

//! [onConnected]
//! SLOT to connect to the dummy IO Control app on the server
void WS_Client::onConnected_dummyIO_Control()
{
    m_webSocket_dummyIO_Control.sendTextMessage(obj.readJsonFile(obj.getFn_dir() + obj.getFn_ID_0_Send_ioControl()));
    if (m_debug){
        qDebug() << "WebSocket dummyIO Control connected";
        qDebug() << "----------------------------------------\n";
    }
    connect(&m_webSocket_dummyIO_Control, &QWebSocket::textMessageReceived, this, &WS_Client::onTextMessageReceived_dummyIO_Control);
}
//! [onConnected]

//! [onTextMessageReceived]
//! SLOT to handle incoming text messages
//! @param message: message sent by the server
void WS_Client::onTextMessageReceived_dummyGate(QString message)
{
    obj.checkJsonMessage(message, m_webSocket_dummyIO_Control);
}
//! [onTextMessageReceived]


//! [onTextMessageReceived]
//! SLOT to handle incoming text messages
//! @param message: message sent by the server
void WS_Client::onTextMessageReceived_dummyIO_Control(QString message)
{
    if(m_debug){
        qDebug() << "IOControl message:" << message;
    }
}
//! [onTextMessageReceived]
