#ifndef SERIALIZABLEOBJECT_H
#define SERIALIZABLEOBJECT_H

#include <QJsonDocument>
#include <QJsonObject>

class TTLogger;

enum DomainRealm {
    DOMAIN,
    API,
    UI,
};

class DomainObject
{
public:
    DomainObject(DomainRealm realm, QString object);

    virtual QJsonObject serialize() = 0;
    virtual ~DomainObject();
protected:
    TTLogger *logger;
};

typedef QList<DomainObject *> DomainList;

#endif // SERIALIZABLEOBJECT_H
