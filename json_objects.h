#ifndef JSON_OBJECTS_H
#define JSON_OBJECTS_H

#include <QString>
#include <QFile>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include "jsonfilenames.h"

class JSON_Objects
{
public:
    JSON_Objects();
    QString readJsonFile(const QString &filename);

    QString getFn_ID_0_Send_gate() const;
    QString getFn_ID_0_Receive() const;
    QString getFn_ID_1_Send() const;
    QString getFn_ID_1_Receive() const;
    QString getFn_dir() const;
    QString getFn_ID_0_Send_ioControl() const;

    QString readGateEvent(QString &gateEvent);
    QString sendSetOutput(QString value, QString name);




private:
    const QString fn_dir = "json_files/";

    const QString fn_ID_0_Send_gate = "useGate.json";
    const QString fn_ID_0_Send_ioControl = "use_iocontrol.json";
    const QString fn_ID_0_Receive = "id_0_result_ok.json";
    const QString fn_ID_1_Send = "id_1_setOutput.json";
    const QString fn_ID_1_Receive = "id_1_result_true.json";



};

#endif // JSON_OBJECTS_H
