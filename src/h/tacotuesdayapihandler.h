#ifndef TACOTUESDAYAPIHANDLER_H
#define TACOTUESDAYAPIHANDLER_H

#include <QObject>
#include <QNetworkAccessManager>

class TacoTuesdayApiHandler
{
public:
    TacoTuesdayApiHandler();
private:
    QNetworkAccessManager *client;
};

#endif // TACOTUESDAYAPIHANDLER_H
