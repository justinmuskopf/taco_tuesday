#include <QString>
#include <QJsonDocument>
#include <QDebug>
#include <QJsonArray>

#include "jsonparser.h"
#include "employee.h"
#include "order.h"
#include "individualorder.h"
#include "fullorder.h"
#include "ttlogger.h"

JsonParser *JsonParser::instance = nullptr;

JsonParser::JsonParser()
{
    logger = TTLoggerFactory::Logger(DomainRealm::DOMAIN, "JsonParser");
}

JsonParser *JsonParser::Instance()
{
    if (instance == nullptr)
    {
        instance = new JsonParser();
    }

    return instance;
}

QJsonDocument JsonParser::getJsonDocument(QString json)
{
    QJsonDocument doc = QJsonDocument::fromJson(json.toUtf8());
    if (!doc.isNull())
    {
        return doc;
    }
    else
    {
        logger->error("JSON is null!");
    }
}

QJsonArray JsonParser::parseArray(QString json)
{
    QJsonDocument doc = getJsonDocument(json);

    return doc.array();
}

QJsonObject JsonParser::parseObject(QString json)
{
    QJsonDocument doc = getJsonDocument(json);

    return doc.object();
}

Employee *JsonParser::parseEmployee(QJsonObject employeeObject)
{
    if (!employeeObject.contains("fullName"))
    {
        throw "No full name for employee!";
    }
    else if (!employeeObject.contains("slackId"))
    {
        throw "No Slack ID for employee!";
    }

    QString fullName = employeeObject["fullName"].toString();
    QString slackId = employeeObject["slackId"].toString();

    QString nickName = "";
    if (employeeObject.contains("nickName"))
    {
        nickName = employeeObject["nickName"].toString();
    }

    bool isAdmin = false;
    if (employeeObject.contains("admin"))
    {
        isAdmin = employeeObject["admin"].toBool();
    }

    return new Employee(fullName, nickName, slackId, isAdmin);
}

QList<DomainObject *> JsonParser::parseEmployees(QString json)
{
    QJsonArray employeesJson = parseArray(json);

    QList<DomainObject *> employees;
    foreach (QJsonValue o, employeesJson)
    {
        employees << parseEmployee(o.toObject());
    }

    return employees;
}

Taco *JsonParser::parseTaco(QJsonObject tacoObject)
{
    if (!tacoObject.contains("type") or !tacoObject.contains("name") or !tacoObject.contains("price"))
    {
        throw "Invalid JSON Object provided to parseTaco!";
    }

    return new Taco(tacoObject["type"].toString(),
            tacoObject["name"].toString(),
            tacoObject["price"].toDouble());
}

QList<DomainObject *> JsonParser::parseTacos(QString json)
{
    QJsonArray tacosJson = parseArray(json);

    QList<DomainObject *> tacos;
    foreach (QJsonValue o, tacosJson)
    {
        tacos << parseTaco(o.toObject());
    }

    return tacos;
}

Order *JsonParser::parseOrder(QJsonObject orderObject)
{
    Employee *employee = parseEmployee(orderObject["employee"].toObject());
    Order *order = new IndividualOrder(employee);

    TacoPriceMap tacoPrices = Order::TacoPrices;
    foreach (TacoType ttype, tacoPrices.keys())
    {
        order->addTacos(ttype, orderObject[ttype].toInt());
    }

    order->setCreatedAt(orderObject["createdAt"].toString());

    return order;
}

IndividualOrder *JsonParser::parseIndividualOrder(QJsonObject orderObject)
{
    return static_cast<IndividualOrder *>(parseOrder(orderObject));
}

QList<DomainObject *> JsonParser::parseIndividualOrders(QString json)
{
    QJsonArray ordersJson = parseArray(json);

    QList<DomainObject *> orders;
    foreach (QJsonValue o, ordersJson)
    {
        orders << parseIndividualOrder(o.toObject());
    }

    return orders;
}

FullOrder *JsonParser::parseFullOrder(QJsonObject orderObject)
{
    FullOrder *fullOrder = new FullOrder();

    OrderedTacoMap tacos;
    foreach (QJsonValue v, orderObject["individualOrders"].toArray())
    {
        QJsonObject o = v.toObject();
        fullOrder->addOrder(parseIndividualOrder(o));
    }

    return fullOrder;
}

QList<DomainObject *> JsonParser::parseFullOrders(QString json)
{
    QJsonArray ordersJson = parseArray(json);

    QList<DomainObject *> orders;
    foreach (QJsonValue o, ordersJson)
    {
        orders << parseFullOrder(o.toObject());
    }

    return orders;
}

bool JsonParser::parseApiStatus(QString json)
{
    QJsonObject o = parseObject(json);
    return o["status"].toString() == "UP";
}
