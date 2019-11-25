#ifndef TACO_H
#define TACO_H

#include "domainobject.h"

#include <QString>

class Taco : public DomainObject
{
public:
    Taco(QString type, QString name, float price);

    static QString PastorType;
    static bool isPastor(QString type);

    QString getType();
    QString getName();
    float getPrice();

    QJsonObject serialize() override;
private:
    QString type;
    QString name;
    float price;
};

typedef QList<Taco> TacoList;
typedef QString TacoType;

#endif // TACO_H
