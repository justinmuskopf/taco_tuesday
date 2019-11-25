#ifndef TTLOGGER_H
#define TTLOGGER_H

#include <QMessageLogger>
#include <QLoggingCategory>

#include "domainobject.h"

enum TTLogLevels {
    DEBUG,
    INFO,
    WARN,
    ERROR
};

class TTLogger
{
public:
    void debug(QString msg);
    void info(QString msg);
    void warning(QString msg);
    void error(QString msg);

    friend class TTLoggerFactory;
private:
    TTLogger();
    TTLogger(int id, DomainRealm realm, QString registrant);

    DomainRealm realm;
    QString registrant;

    int id;
    char *registrantName;
};

class TTLoggerFactory
{
public:
    static TTLogger *Logger(DomainRealm realm, QString registrant);
    ~TTLoggerFactory();
private:
    TTLoggerFactory();

    static int sequenceId;
    static int nextSequenceId();
    static QList<TTLogger *> GeneratedLoggers;
};

#endif // TTLOGGER_H
