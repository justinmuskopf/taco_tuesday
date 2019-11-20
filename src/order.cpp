#include "jsonparser.h"
#include "order.h"
#include "tacotuesdayapihandler.h"

#include <QNetworkReply>

QList<Taco> Order::Tacos;

Order::Order() : QObject(nullptr)
{
    if (Tacos.isEmpty())
    {
        TacoTuesdayApiHandler handler;
        ApiReply *reply = handler.getTacos();
        connect(reply, &ApiReply::finished, this, [=]{
            Tacos = JsonParser().parseTacos(reply->readAll());
        });
    }
}
