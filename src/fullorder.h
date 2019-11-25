#ifndef FULLORDER_H
#define FULLORDER_H

#include "individualorder.h"
#include "order.h"



class FullOrder : public Order
{
public:
    FullOrder();
    FullOrder(Order *);

    void addOrder(IndividualOrder *order);
    void updateOrder(IndividualOrder *order);

    QJsonObject serialize() override;
private:
    QMap<QString, IndividualOrder *> individualOrders;
private slots:
    void on_order_updated(IndividualOrder *);
};

#endif // FULLORDER_H
