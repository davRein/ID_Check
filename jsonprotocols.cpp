#include "jsonprotocols.h"

JsonProtocols::JsonProtocols(QObject *parent) : QObject(parent)
{

}

//! [createJson_method_use_IO_COntrol]
//! Creates the json protocol which advise the server to use the dummy IO Control application
//! @param nId: Incremented Id to identify json messages
//! @returns result: QJSONDocument as QString
QString JsonProtocols::createJson_method_use_IO_COntrol(int nId)
{
    QJsonObject rootObj;
    rootObj.insert("id", nId);
    rootObj.insert("jsonrpc", "2.0");
    rootObj.insert("methodd", "use");

    QJsonObject paramsObj;
    paramsObj.insert("app", "iocontrol");

    rootObj.insert("params", paramsObj);
    QJsonDocument doc(rootObj);
    QString result(doc.toJson(QJsonDocument::Compact));

    return result;
}
//! [createJson_method_use_IO_COntrol]


//! [createJson_method_SetOutput]
//! Creates the json protocol which passes name and value to the server
//! @param nId: Incremented Id to identify json messages
//! @param value: true or false, depends on read UII
//! @param name: name of the result after reading the gateEvent -> green, yellow or red
//! @returns result: JSON setOutput as QString
QString JsonProtocols::createJson_method_SetOutput(int nId, QString value, QString name){
    QJsonObject outputObj;
    outputObj.insert("id", nId);
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
//! [createJson_method_SetOutput]


//! [createJson_method_use_gate]
//! Creates the json protocol which advise the server to use the dummy gate application
//! @param nId: Incremented Id to identify json messages
//! @returns result: QJSONDocument as QString
QString JsonProtocols::createJson_method_use_gate(int nId)
{
    QJsonObject rootObj;
    rootObj.insert("id", nId);
    rootObj.insert("jsonrpc", "2.0");
    rootObj.insert("methodd", "use");

    QJsonObject paramsObj;
    paramsObj.insert("app", "gate");

    rootObj.insert("params", paramsObj);
    QJsonDocument doc(rootObj);
    QString result(doc.toJson(QJsonDocument::Compact));

    return result;

}
//! [createJson_method_use_gate]



























