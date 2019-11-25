#include "jsonparser.h"
#include "order.h"
#include "tacotuesdayapihandler.h"
#include "ttlogger.h"

#include <QNetworkReply>
#include <QDebug>

TacoPriceMap Order::TacoPrices;

Order::Order() : QObject(nullptr), DomainObject(DomainRealm::DOMAIN, "Order")
{
}

Order::Order(Order *order) : Order()
{
    tacosInOrder = order->tacosInOrder;
}

void Order::initTacos()
{
    TacoTuesdayApiHandler *ttapihandler = TacoTuesdayApiHandler::Instance();
    connect(ttapihandler, &TacoTuesdayApiHandler::on_finished_getting_tacos, [=](QList<Taco *> tacos){
        qDebug() << "Finished getting tacos!";
        foreach (Taco *taco, tacos)
        {
            qDebug() << taco->getType() << taco->getPrice();
            TacoPrices[taco->getType()] = taco->getPrice();
        }

        ttapihandler->deleteLater();
    });
}

float Order::price(float pastorPrice)
{
    float total = 0;
    foreach (TacoType ttype, tacosInOrder.keys())
    {
        int numTacosInOrder = tacosInOrder[ttype];
        if (numTacosInOrder == 0) continue;

        total += Taco::isPastor(ttype) ? numTacosInOrder * pastorPrice : numTacosInOrder * TacoPrices[ttype];
    }

    return total;
}

OrderedTacoMap Order::getTacoCounts()
{
    return tacosInOrder;
}

void Order::addTacos(QString tacoType, int count)
{
    if (!TacoPrices.contains(tacoType))
    {
        return logger->warning("Wrong taco type provided to order: " + tacoType + "!");
    }


    if (!tacosInOrder.contains(tacoType))
    {
        tacosInOrder[tacoType] = 0;
    }

    tacosInOrder[tacoType] += count;
}

QJsonObject Order::serialize(float pastorPrice)
{
    QJsonObject o;
    foreach (QString tacoType, tacosInOrder.keys())
    {
        o[tacoType] = tacosInOrder[tacoType];
    }

    o["total"] = price(pastorPrice);

    return o;
}

void Order::setCreatedAt(QString dateString)
{
    createdAt = QDateTime::fromString(dateString);
}


QJsonObject Order::serialize() { return serialize(TacoPrices[Taco::PastorType]); }

