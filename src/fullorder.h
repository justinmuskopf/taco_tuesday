#ifndef FULLORDER_H
#define FULLORDER_H

#include "individualorder.h"
#include "order.h"



class FullOrder : public Order
{
public:
    FullOrder();

    QJsonObject json();
private:
    QList<IndividualOrder *> individualOrders;
};

#endif // FULLORDER_H
