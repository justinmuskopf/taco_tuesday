#include <QString>
#include <QJsonDocument>
#include <QDebug>
#include <QJsonArray>

#include "jsonparser.h"


JsonParser::JsonParser()
{

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
        throw "JSON is null!";
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

QList<Employee *> JsonParser::parseEmployees(QString json)
{
    QJsonArray employeesJson = parseArray(json);

    QList<Employee *> employees;
    foreach (QJsonValue o, employeesJson)
    {
        employees << parseEmployee(o.toObject());
    }

    return employees;
}

Taco JsonParser::parseTaco(QJsonObject tacoObject)
{
    if (!tacoObject.contains("type") or !tacoObject.contains("name") or !tacoObject.contains("price"))
    {
        throw "Invalid JSON Object provided to parseTaco!";
    }

    Taco taco;
    taco.type = tacoObject["type"].toString();
    taco.name = tacoObject["name"].toString();
    taco.price = tacoObject["price"].toDouble();

    return taco;
}

QList<Taco> JsonParser::parseTacos(QString json)
{
    QJsonArray tacosJson = parseArray(json);

    QList<Taco> tacos;
    foreach (QJsonValue o, tacosJson)
    {
        tacos << parseTaco(o.toObject());
    }

    return tacos;
}

Order *JsonParser::parseOrder(QJsonObject orderObject)
{

}

IndividualOrder *JsonParser::parseIndividualOrder(QJsonObject orderObject)
{
    IndividualOrder *o = new IndividualOrder();


}

QList<IndividualOrder *> JsonParser::parseIndividualOrders(QString json)
{

}

FullOrder *JsonParser::parseFullOrder(QJsonObject orderObject)
{

}

QList<FullOrder *> JsonParser::parseFullOrders(QString json)
{

}
