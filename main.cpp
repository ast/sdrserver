#include <QCoreApplication>
#include <QtRemoteObjects>
#include <QDebug>

#include <iostream>



#include "radio.h"

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    Radio radio;
    QRemoteObjectHost* hostNode = new QRemoteObjectHost(QUrl(QStringLiteral("local:/tmp/wsdr")), &app);
    if(!hostNode->enableRemoting(&radio)) {
        qDebug() << "some error";
    }



    app.exec();

    return 0;
}
