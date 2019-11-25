#include "individualorder.h"

IndividualOrder::IndividualOrder(Employee *employee) : Order()
{
    this->employee = employee;
}
