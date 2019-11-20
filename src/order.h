#ifndef ORDER_H
#define ORDER_H

#include <QList>
#include <QString>
#include <QMap>
#include <QObject>

#include "taco.h"
#include "tacotuesdayapihandler.h"

class Order : public QObject
{
    Q_OBJECT
public:
    Order();
private:
    static QList<Taco> Tacos;
    QMap<QString, int> tacoCounts;
};

#endif // ORDER_H
