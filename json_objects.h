#ifndef JSON_OBJECTS_H
#define JSON_OBJECTS_H

#include "jsonfilenames.h"
#include "check_uii.h"
#include "jsonprotocols.h"

#include <QDebug>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QString>
#include <QWebSocket>


class JSON_Objects
{
public:
    JSON_Objects();

    QString readJsonFile(const QString &filename);
    int readGateEvent(QString &gateEvent);
    void checkJsonMessage(QString &message, QWebSocket &socket);
    void sendOutput(QString &message, QWebSocket &socket);

private:
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
    JsonProtocols protocols;

    // TMP
    int nId;
};

#endif // JSON_OBJECTS_H
