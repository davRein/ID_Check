#ifndef WS_CLIENT_H
#define WS_CLIENT_H

#include "json_objects.h"
#include "check_uii.h"
#include "jsonprotocols.h"
#include <QtCore/QObject>
#include <QtWebSockets/QWebSocket>
#include <QString>
#include <QDebug>

class WS_Client : public QObject
{
    Q_OBJECT
public:
    explicit WS_Client(const QUrl &url, bool debug = false, QObject *parent = nullptr);

Q_SIGNALS:
    void closed_dummyGate();
    void closed_dummyIO_Control();

private Q_SLOTS:
    void onConnected_dummyGate();
    void onConnected_dummyIO_Control();
    void onTextMessageReceived_dummyGate(QString message);
    void onTextMessageReceived_dummyIO_Control(QString message);

private:
    QWebSocket m_webSocket_dummyGate;
    QWebSocket m_webSocket_dummyIO_Control;
    QUrl m_url;
    bool m_debug = false;
    bool isConnected;
    JSON_Objects obj;
    Check_UII chck;
    JsonProtocols protocols;

    // TMP
    int nId = 1;
};

#endif // WS_CLIENT_H
