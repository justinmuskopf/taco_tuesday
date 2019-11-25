#include "fullorder.h"

#include <QJsonArray>

FullOrder::FullOrder() : Order()
{

}

FullOrder::FullOrder(Order *order) : Order(order)
{
}

QJsonObject FullOrder::serialize()
{
    QJsonObject o = Order::serialize();

    QJsonArray orderArray;
    foreach (IndividualOrder *order, individualOrders)
    {
        orderArray.append(order->serialize());
    }

    o["individualOrders"] = orderArray;

    return o;
}
