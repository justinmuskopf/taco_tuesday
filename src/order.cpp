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

void Order::initTacoCounts()
{
    foreach (Taco taco, Tacos)
    {
        tacoCounts[taco.type] = 0;
    }
}

float Order::price(float pastorPrice)
{
    float total = 0;
    foreach (Taco taco, Tacos)
    {
        total += taco.type == "PASTOR" ? tacoCounts[taco.type] * pastorPrice : tacoCounts[taco.type] * taco.price;
    }
}
