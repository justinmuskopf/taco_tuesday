#include "taco.h"

QString Taco::PastorType = "pastor";
bool Taco::isPastor(QString type)
{
    return type == PastorType;
}

Taco::Taco(QString type, QString name, float price) : DomainObject(DomainRealm::DOMAIN, "Taco")
{
    this->type = type;
    this->name = name;
    this->price = price;
}

QString Taco::getType()
{
    return type;
}

QString Taco::getName()
{
    return name;
}

float Taco::getPrice()
{
    return price;
}
