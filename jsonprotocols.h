#ifndef JSONPROTOCOLS_H
#define JSONPROTOCOLS_H

#include <QObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>

class JsonProtocols : public QObject
{
    Q_OBJECT
public:
    explicit JsonProtocols(QObject *parent = nullptr);

    QString createJson_method_use_IO_COntrol(int nId);
    QString createJson_method_SetOutput(int nId, QString value, QString name);
    QString createJson_method_use_gate(int nId);
signals:

};

#endif // JSONPROTOCOLS_H
