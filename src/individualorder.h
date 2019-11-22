#ifndef INDIVIDUALORDER_H
#define INDIVIDUALORDER_H

#include "order.h"

class IndividualOrder : public Order
{
public:
    IndividualOrder();
private slots:
    void updated(IndividualOrder *order);
};

#endif // INDIVIDUALORDER_H
