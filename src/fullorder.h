#ifndef FULLORDER_H
#define FULLORDER_H

#include "individualorder.h"
#include "order.h"



class FullOrder : public Order
{
public:
    FullOrder();

    void addOrder(IndividualOrder *order);
    void updateOrder(IndividualOrder *order);

    QJsonObject json();
private:
    QMap<QString, IndividualOrder *> individualOrders;
private slots:
    void on_order_updated(IndividualOrder *);
};

#endif // FULLORDER_H
