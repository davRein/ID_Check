#include <QtCore/QCoreApplication>
#include <QtCore/QCommandLineParser>
#include <QtCore/QCommandLineOption>
#include "ws_client.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QCommandLineParser parser;
    parser.setApplicationDescription("QtWebSockets example: echoclient");
    parser.addHelpOption();

    QCommandLineOption dbgOption(QStringList() << "d" << "debug",
            QCoreApplication::translate("main", "Debug output [default: off]."));
    parser.addOption(dbgOption);
    parser.process(a);
    //bool debug = parser.isSet(dbgOption);
    // TKS
    bool debug = true;

    // QString str_URL = QStringLiteral("ws://192.168.0.193:42424");
    QString str_URL = QStringLiteral("ws://localhost:1234");

    WS_Client client(QUrl(str_URL), debug);
    QObject::connect(&client, &WS_Client::closed_dummyGate, &a, &QCoreApplication::quit);

    return a.exec();
}
