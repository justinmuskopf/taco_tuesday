#include "ttlogger.h"

QList<TTLogger *> TTLoggerFactory::GeneratedLoggers;

TTLogger::TTLogger(int id, DomainRealm realm, QString registrant)
{
    this->id = id;
    this->realm = realm;
    this->registrant = registrant;
}

void TTLogger::debug(QString msg)
{

}

void TTLogger::info(QString msg)
{

}

void TTLogger::warning(QString msg)
{

}

void TTLogger::error(QString msg)
{

}


int TTLoggerFactory::sequenceId = 999;

TTLoggerFactory::TTLoggerFactory() {}

TTLogger *TTLoggerFactory::Logger(DomainRealm realm, QString registrant)
{
    TTLogger *logger = new TTLogger(nextSequenceId(), realm, registrant);
    GeneratedLoggers.append(logger);

    return logger;
}

int TTLoggerFactory::nextSequenceId() { return ++sequenceId; }
