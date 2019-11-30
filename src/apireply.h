#ifndef APIREPLY_H
#define APIREPLY_H

#include "jsonparser.h"
#include "ttlogger.h"

#include <QNetworkReply>
#include <QObject>

class ApiReply : public QObject
{
    Q_OBJECT

public:
    ApiReply(int transactionId, QNetworkReply *reply, QList<DomainObject *> (JsonParser::*jpMethod)(QString));

    bool error();
    QString errorString();
    QString json();
signals:
    void finished(int id, QList<DomainObject *>);

private:
    int transactionId;
    static TTLogger *logger;
    QNetworkReply *reply;
    DomainList (JsonParser::*jpMethod)(QString);
    QString jsonString = "";
private slots:
    void on_reply_finished();
};

#endif // APIREPLY_H
