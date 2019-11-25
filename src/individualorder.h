#ifndef INDIVIDUALORDER_H
#define INDIVIDUALORDER_H

#include "order.h"

class IndividualOrder : public Order
{
public:
    IndividualOrder(Employee *employee);
private slots:
    void updated(IndividualOrder *order);
    Employee *employee;
};

#endif // INDIVIDUALORDER_H
