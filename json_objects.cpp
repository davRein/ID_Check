#include "json_objects.h"

//! [constructor]
//! Creates an JSON_Objects object
JSON_Objects::JSON_Objects()
{

}
//! [constructor]


//! [readGateEvent]
//! Parses the JSON gateEvent and returns the UII
//! @param gateEvent: QString gateEvent
//! @returns result: UII ID
int JSON_Objects::readGateEvent(QString &gateEvent){

    QJsonDocument d = QJsonDocument::fromJson(gateEvent.toUtf8());
    QJsonObject rootObj = d.object();
    QJsonValue params = rootObj.value(QString("params"));
    QJsonObject paramsObj = params.toObject();
    QJsonValue tags = paramsObj.value(QString("tags"));
    paramsObj = tags[0].toObject();
    QJsonValue qval = paramsObj.value(QString("UII"));
    QString result = qval.toString();

    return result.toInt();
}
//! [readGateEvent]


//! [checkJsonMessage]
//! Checks the incoming JSON message
//! @param message: JSON message as QString
//! @param socket: Socket to communicate with the server
void JSON_Objects::checkJsonMessage(QString &message, QWebSocket &socket)
{
    QTime time;
    QJsonDocument doc = QJsonDocument::fromJson(message.toUtf8());
    QJsonObject rootObj = doc.object();
    if(rootObj.find("result").value().operator==("OK")){
        if(m_debug){
            qDebug() << "Result OK from iocontrol at " << time.currentTime();
        }
    } else if(rootObj.find("method").value() == "gateEvent"){
        if(m_debug){
            qDebug() << "\nGenerated UII from gateEvent: " << readGateEvent(message);
        }
        sendOutput(message, socket);
    } else {
        if(m_debug){
            qDebug() << "Unknown JSON protocol";
        }
    }
}
//! [checkJsonMessage]

//! [sendOutput]
//! Sends the setOutput JSON file depending on the evaluated UII
//! @param message: JSON message as QString
//! @param socket: Socket to communicate with the server
void JSON_Objects::sendOutput(QString &message, QWebSocket &socket)
{
    if(chck.checkTransponderID(readGateEvent(message)).compare(SIGNAL_GREEN) == 0){
        valueGreen = VAL_TRUE;
        socket.sendTextMessage(protocols.createJson_method_SetOutput(nId, valueGreen, SIGNAL_GREEN));
        valueYellow = VAL_FALSE;
        socket.sendTextMessage(protocols.createJson_method_SetOutput(nId, valueYellow, SIGNAL_YELLOW));
        valueRed = VAL_FALSE;
        socket.sendTextMessage(protocols.createJson_method_SetOutput(nId, valueRed, SIGNAL_RED));
    } else if(chck.checkTransponderID(readGateEvent(message)).compare(SIGNAL_YELLOW) == 0){
        valueGreen = VAL_FALSE;
        socket.sendTextMessage(protocols.createJson_method_SetOutput(nId, valueGreen, SIGNAL_GREEN));
        valueYellow = VAL_TRUE;
        socket.sendTextMessage(protocols.createJson_method_SetOutput(nId, valueYellow, SIGNAL_YELLOW));
        valueRed = VAL_FALSE;
        socket.sendTextMessage(protocols.createJson_method_SetOutput(nId, valueRed, SIGNAL_RED));
    } else if(chck.checkTransponderID(readGateEvent(message)).compare(SIGNAL_RED) == 0){
        valueGreen = VAL_FALSE;
        socket.sendTextMessage(protocols.createJson_method_SetOutput(nId, valueGreen, SIGNAL_GREEN));
        valueYellow = VAL_FALSE;
        socket.sendTextMessage(protocols.createJson_method_SetOutput(nId, valueYellow, SIGNAL_YELLOW));
        valueRed = VAL_TRUE;
        socket.sendTextMessage(protocols.createJson_method_SetOutput(nId, valueRed, SIGNAL_RED));
    } else {
        if(m_debug){
            qDebug() << "Unknows message input";
        }
    }
}
//! [sendOutput]
