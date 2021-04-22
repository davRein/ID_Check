#include "output.h"


Output::Output(QObject *parent) : QObject(parent)
{

}

void Output::setOutput(JSON_Objects obj,  QWebSocket &socket, QString name){
    qDebug() << "Name " + name;

    if(name.compare("green") == 0){
        socket.sendTextMessage(obj.sendSetOutput("true", "green"));
        socket.sendTextMessage(obj.sendSetOutput("false", "yellow"));
        socket.sendTextMessage(obj.sendSetOutput("false", "red"));
    } else if (name.compare("yellow")== 0){
        socket.sendTextMessage(obj.sendSetOutput("false", "green"));
        socket.sendTextMessage(obj.sendSetOutput("true", "yellow"));
        socket.sendTextMessage(obj.sendSetOutput("false", "red"));
    } else if(name.compare("red")== 0){
        socket.sendTextMessage(obj.sendSetOutput("false", "green"));
        socket.sendTextMessage(obj.sendSetOutput("false", "yellow"));
        socket.sendTextMessage(obj.sendSetOutput("true", "red"));
    } else{
        qDebug() << "Wrong input " + name;
    }


}
