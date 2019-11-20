#ifndef JSONPARSER_H
#define JSONPARSER_H

#include <QJsonObject>
#include <QJsonDocument>

#include "taco.h"
#include "employee.h"


class JsonParser
{
public:
    JsonParser();
    QJsonObject parseObject(QString json);
    QJsonArray parseArray(QString json);

    Employee *parseEmployee(QJsonObject employeeObject);
    QList<Employee *> parseEmployees(QString json);

    Taco parseTaco(QJsonObject tacoObject);
    QList<Taco> parseTacos(QString json);
private:
    QJsonDocument getJsonDocument(QString json);
};

#endif // JSONPARSER_H
