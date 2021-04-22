#include "json_objects.h"

JSON_Objects::JSON_Objects()
{

}

QString JSON_Objects::readJsonFile(const QString &filename){
    QString val;
    QFile file;
    file.setFileName(filename);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    val = file.readAll();
    file.close();

    return val;
}

QString JSON_Objects::readGateEvent(QString &gateEvent){
    QJsonDocument d = QJsonDocument::fromJson(gateEvent.toUtf8());
    QJsonObject sett2 = d.object();
    QJsonValue params = sett2.value(QString("params"));

    QJsonObject item = params.toObject();
    QJsonValue tags = item.value(QString("tags"));

    item = tags[0].toObject();
    QJsonValue qval = item.value(QString("UII"));

    QString result = qval.toString();

    return result;
}

QString JSON_Objects::sendSetOutput(QString value, QString name){
    QJsonObject outputObj;
    outputObj.insert("id", "1");
    outputObj.insert("jsonrpc", "2.0");
    outputObj.insert("method", "setOutput");
    QJsonObject paramsObj;
    paramsObj.insert("name", name);
    paramsObj.insert("value", value);
    outputObj.insert("params", paramsObj);
    QJsonDocument doc(outputObj);

    qDebug() << doc;

    QString result(doc.toJson(QJsonDocument::Compact));
    return result;
}

QString JSON_Objects::getFn_ID_0_Send_gate() const
{
    return fn_ID_0_Send_gate;
}

QString JSON_Objects::getFn_ID_0_Send_ioControl() const
{
    return fn_ID_0_Send_ioControl;
}


QString JSON_Objects::getFn_ID_0_Receive() const
{
    return fn_ID_0_Receive;
}

QString JSON_Objects::getFn_ID_1_Send() const
{
    return fn_ID_1_Send;
}

QString JSON_Objects::getFn_ID_1_Receive() const
{
    return fn_ID_1_Receive;
}

QString JSON_Objects::getFn_dir() const
{
    return fn_dir;
}
