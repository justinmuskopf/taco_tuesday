#include "apireply.h"
#include <QObject>

TTLogger *ApiReply::logger = TTLoggerFactory::Logger(DomainRealm::API, "ApiReply");

ApiReply::ApiReply(int transactionId, QNetworkReply *reply, QList<DomainObject *> (JsonParser::*jpMethod)(QString)) : QObject()
{
    this->transactionId = transactionId;
    this->reply = reply;
    this->jpMethod = jpMethod;

    connect(reply, &QNetworkReply::finished, this, &ApiReply::on_reply_finished);
}

void ApiReply::on_reply_finished()
{
    if (reply->error())
    {
        return logger->error("Error retrieving results from API: " + reply->errorString());
    }

    jsonString = reply->readAll();

    DomainList objects = (JsonParser::Instance()->*jpMethod)(jsonString);

    emit finished(transactionId, objects);
}

bool ApiReply::error()
{
    return reply->error();
}

QString ApiReply::errorString()
{
    return reply->errorString();
}

QString ApiReply::json()
{
    return jsonString;
}
