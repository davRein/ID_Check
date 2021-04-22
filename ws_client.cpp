#include "ws_client.h"
#include "json_objects.h"

QT_USE_NAMESPACE

//! [constructor]
WS_Client::WS_Client(const QUrl &url, bool debug, QObject *parent) :
    QObject(parent),
    m_url(url),
    m_debug(debug)
{
    if (m_debug)
        qDebug() << "WebSocket server:" << url;
    connect(&m_webSocket_dummyGate, &QWebSocket::connected, this, &WS_Client::onConnected_dummyGate);
    connect(&m_webSocket_dummyGate, &QWebSocket::disconnected, this, &WS_Client::closed_dummyGate);

    connect(&m_webSocket_dummyIO_Control, &QWebSocket::connected, this, &WS_Client::onConnected_dummyIO_Control);
    connect(&m_webSocket_dummyIO_Control, &QWebSocket::disconnected, this, &WS_Client::closed_dummyIO_Control);

    isConnected = true;
    m_webSocket_dummyGate.open(QUrl(url));
    m_webSocket_dummyIO_Control.open(QUrl(url));

}
//! [constructor]

//! [onConnected]
void WS_Client::onConnected_dummyGate()
{
    JSON_Objects obj;
    if (m_debug){
        qDebug() << "WebSocket dummyGate connected";
    }
    connect(&m_webSocket_dummyGate, &QWebSocket::textMessageReceived, this, &WS_Client::onTextMessageReceived_dummyGate);
    if(isConnected){
        m_webSocket_dummyGate.sendTextMessage(obj.readJsonFile(obj.getFn_dir() + obj.getFn_ID_0_Send_gate()));
    }

}
//! [onConnected]

//! [onConnected]
void WS_Client::onConnected_dummyIO_Control()
{
    JSON_Objects obj;
    if (m_debug){
        qDebug() << "WebSocket dummyIO Control connected";
    }
    connect(&m_webSocket_dummyIO_Control, &QWebSocket::textMessageReceived, this, &WS_Client::onTextMessageReceived_dummyIO_Control);
    if(isConnected){

        //m_webSocket_dummyIO_Control.sendTextMessage(obj.sendSetOutput(chck.getValue(), chck.getName()));
    }

}
//! [onConnected]

//! [onTextMessageReceived]
void WS_Client::onTextMessageReceived_dummyGate(QString message)
{
    if(message.contains("gateEvent")){
        //chck.setName(chck.checkTransponderID(obj.readGateEvent(message).toInt()));
        //qDebug() << obj.readGateEvent(message);
        //qDebug() << chck.checkTransponderID(obj.readGateEvent(message).toInt());
        //qDebug() << "-------------------";
        out.setOutput(obj, m_webSocket_dummyIO_Control, chck.checkTransponderID(obj.readGateEvent(message).toInt()));
    }
    //m_webSocket.close();
}
//! [onTextMessageReceived]


//! [onTextMessageReceived]
void WS_Client::onTextMessageReceived_dummyIO_Control(QString message)
{

    //m_webSocket.close();
}
//! [onTextMessageReceived]
