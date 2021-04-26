#include "json_objects.h"

//! [constructor]
//! Creates an JSON_Objects object
JSON_Objects::JSON_Objects()
{

}
//! [constructor]

//! [readJsonFile]
//! Opens and reads a JSON file
//! @param filename: directory/filename
//! @returns val: JSON file as QString
QString JSON_Objects::readJsonFile(const QString &filename){
    QString val;
    QFile file;
    file.setFileName(filename);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    val = file.readAll();
    file.close();

    return val;
}
//! [readJsonFile]

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

//! [setOutput]
//! Sets the params value and name for the setOutput JSON method
//! @param value: true or false, depends on read UII
//! @param name: name of the result after reading the gateEvent -> green, yellow or red
//! @returns result: JSON setOutput as QString
QString JSON_Objects::setOutput(QString value, QString name){
    QJsonObject outputObj;
    outputObj.insert("id", "1");
    outputObj.insert("jsonrpc", "2.0");
    outputObj.insert("method", "setOutput");
    QJsonObject paramsObj;
    paramsObj.insert("name", name);
    paramsObj.insert("value", value);
    outputObj.insert("params", paramsObj);
    QJsonDocument doc(outputObj);

    QString result(doc.toJson(QJsonDocument::Compact));
    return result;
}
//! [setOutput]

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
        socket.sendTextMessage(setOutput(valueGreen, SIGNAL_GREEN));
        valueYellow = VAL_FALSE;
        socket.sendTextMessage(setOutput(valueYellow, SIGNAL_YELLOW));
        valueRed = VAL_FALSE;
        socket.sendTextMessage(setOutput(valueRed, SIGNAL_RED));
    } else if(chck.checkTransponderID(readGateEvent(message)).compare(SIGNAL_YELLOW) == 0){
        valueGreen = VAL_FALSE;
        socket.sendTextMessage(setOutput(valueGreen, SIGNAL_GREEN));
        valueYellow = VAL_TRUE;
        socket.sendTextMessage(setOutput(valueYellow, SIGNAL_YELLOW));
        valueRed = VAL_FALSE;
        socket.sendTextMessage(setOutput(valueRed, SIGNAL_RED));
    } else if(chck.checkTransponderID(readGateEvent(message)).compare(SIGNAL_RED) == 0){
        valueGreen = VAL_FALSE;
        socket.sendTextMessage(setOutput(valueGreen, SIGNAL_GREEN));
        valueYellow = VAL_FALSE;
        socket.sendTextMessage(setOutput(valueYellow, SIGNAL_YELLOW));
        valueRed = VAL_TRUE;
        socket.sendTextMessage(setOutput(valueRed, SIGNAL_RED));
    } else {
        if(m_debug){
            qDebug() << "Unknows message input";
        }
    }
}
//! [sendOutput]

//! [getFn_ID_0_Send_gate]
//! @returns fn_ID_0_Send_gate
QString JSON_Objects::getFn_ID_0_Send_gate() const
{
    return fn_ID_0_Send_gate;
}
//! [getFn_ID_0_Send_gate]

//! [getFn_ID_0_Send_ioControl]
//! @returns fn_ID_0_Send_ioControl
QString JSON_Objects::getFn_ID_0_Send_ioControl() const
{
    return fn_ID_0_Send_ioControl;
}
//! [getFn_ID_0_Send_ioControl]

//! [getFn_dir]
//! @returns fn_dir
QString JSON_Objects::getFn_dir() const
{
    return fn_dir;
}
//! [getFn_dir]
