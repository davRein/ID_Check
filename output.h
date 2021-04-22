#ifndef OUTPUT_H
#define OUTPUT_H

#include "check_uii.h"
#include "json_objects.h"
#include <QObject>
#include <QtWebSockets/QWebSocket>

class Output : public QObject
{
    Q_OBJECT
public:
    explicit Output(QObject *parent = nullptr);

    void setOutput(JSON_Objects obj,  QWebSocket &socket, QString name);
private:


signals:

};

#endif // OUTPUT_H
