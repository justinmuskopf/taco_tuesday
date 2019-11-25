#include "domainobject.h"
#include "ttlogger.h"

DomainObject::DomainObject(DomainRealm realm, QString object)
{
    logger = TTLoggerFactory::Logger(realm, object);
}

DomainObject::~DomainObject() {}
