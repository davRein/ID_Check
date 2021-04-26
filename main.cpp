#include <QtCore/QCoreApplication>
#include <QtCore/QCommandLineParser>
#include <QtCore/QCommandLineOption>
#include "ws_client.h"

//! [main] the main ...
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    bool debug = false;

    QString str_URL = QStringLiteral("ws://localhost:1234");

    WS_Client client(QUrl(str_URL), debug);
    QObject::connect(&client, &WS_Client::closed_dummyGate, &a, &QCoreApplication::quit);

    return a.exec();
}
