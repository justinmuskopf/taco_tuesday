#ifndef ORDER_H
#define ORDER_H

#include <QList>
#include <QString>
#include <QMap>
#include <QObject>
#include "jsonparser.h"

#include "taco.h"
#include "tacotuesdayapihandler.h"
#include "domainobject.h"


typedef QMap<QString, float> TacoPriceMap;
typedef QMap<QString, int> OrderedTacoMap;

class Order : public QObject, public DomainObject
{
    Q_OBJECT
public:
    Order();
    Order(Order *);

    void addTacos(QString tacoType, int count);
    float price(float pastorPrice);
    OrderedTacoMap getTacoCounts();

    QJsonObject serialize() override;
    QJsonObject serialize(float pastorPrice);

    friend Order *JsonParser::parseOrder(QJsonObject order);
signals:
    void updated(Order *order);
private:
    static TacoPriceMap TacoPrices;
protected:
    OrderedTacoMap tacosInOrder;
};

#endif // ORDER_H
