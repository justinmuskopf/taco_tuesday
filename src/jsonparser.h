#ifndef JSONPARSER_H
#define JSONPARSER_H

#include "domainobject.h"

#include <QJsonObject>
#include <QJsonDocument>

class Taco;
class Order;
class IndividualOrder;
class FullOrder;
class Employee;

class JsonParser
{
public:
    static JsonParser *Instance();

    QJsonObject parseObject(QString json);
    QJsonArray parseArray(QString json);

    Employee *parseEmployee(QJsonObject employeeObject);
    QList<DomainObject *> parseEmployees(QString json);

    Taco *parseTaco(QJsonObject tacoObject);
    QList<DomainObject *> parseTacos(QString json);

    Order *parseOrder(QJsonObject orderObject);

    IndividualOrder *parseIndividualOrder(QJsonObject orderObject);
    QList<DomainObject *> parseIndividualOrders(QString json);

    FullOrder *parseFullOrder(QJsonObject orderObject);
    QList<DomainObject *> parseFullOrders(QString json);

    bool parseApiStatus(QString json);

private:
    JsonParser();
    static JsonParser *instance;
    TTLogger *logger;
    QJsonDocument getJsonDocument(QString json);
};

#endif // JSONPARSER_H
