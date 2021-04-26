#ifndef JSON_OBJECTS_H
#define JSON_OBJECTS_H

#include <QString>
#include <QFile>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QWebSocket>
#include "jsonfilenames.h"
#include "check_uii.h"


class JSON_Objects
{
public:
    JSON_Objects();
    QString readJsonFile(const QString &filename);

    QString getFn_ID_0_Send_gate() const;
    QString getFn_dir() const;
    QString getFn_ID_0_Send_ioControl() const;

    int readGateEvent(QString &gateEvent);
    QString setOutput(QString value, QString name);

    void checkJsonMessage(QString &message, QWebSocket &socket);

    void sendOutput(QString &message, QWebSocket &socket);
private:
    const QString fn_dir = "json_files/";

    const QString fn_ID_0_Send_gate = "useGate.json";
    const QString fn_ID_0_Send_ioControl = "use_iocontrol.json";
    const QString fn_ID_0_Receive = "id_0_result_ok.json";
    const QString fn_ID_1_Send = "id_1_setOutput.json";
    const QString fn_ID_1_Receive = "id_1_result_true.json";

    const QString VAL_TRUE = "true";
    const QString VAL_FALSE = "false";

    const QString SIGNAL_GREEN = "green";
    const QString SIGNAL_YELLOW = "yellow";
    const QString SIGNAL_RED = "red";

    QString valueRed;
    QString valueYellow;
    QString valueGreen;

    QString name;

    bool m_debug = false;

    Check_UII chck;
};

#endif // JSON_OBJECTS_H
