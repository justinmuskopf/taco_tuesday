#ifndef TACOTUESDAYAPICLIENT_H
#define TACOTUESDAYAPICLIENT_H

#include "apireply.h"
#include "domainobject.h"
#include "jsonparser.h"

#include <QNetworkAccessManager>
#include <QObject>
#include <QSettings>
#include <QJsonObject>

typedef QNetworkRequest ApiRequest;

class TacoTuesdayApiClient : public QNetworkAccessManager
{
public:
    friend class TacoTuesdayApiHandler;
signals:
    void configured(bool configured);
    void transaction_complete(int transactionId, QList<DomainObject *> domainObjects);
public slots:
    void on_apiKey_updated(QString apiKey);
    void on_apiBaseUrl_updated(QString apiBaseUrl);

private:
    TacoTuesdayApiClient(QObject *parent = nullptr);

    static TacoTuesdayApiClient *Instance();
    static TacoTuesdayApiClient *instance;
    static int transactionId;

    int nextTransactionId();

    enum HttpOperation
    {
        GET,
        POST,
        PATCH
    };

    enum TacoTuesdayRequests
    {
        TACOS,
        EMPLOYEES,
        EMPLOYEE_BY_SLACK_ID,
        FULL_ORDERS,
        FULL_ORDER_BY_ID,
        INDIVIDUAL_ORDERS,
        INDIVIDUAL_ORDER_BY_ID
    };

    ApiReply *request(HttpOperation op, TacoTuesdayRequests requestType, QList<DomainObject *> (JsonParser::*jpMethod)(QString),
                      QJsonObject json = QJsonObject(), QString id = QString());
    ApiReply *request(HttpOperation op, TacoTuesdayRequests requestType, QList<DomainObject *> (JsonParser::*jpMethod)(QString),
                      QString id = QString());
    QNetworkReply *raw_get(QString fullPath);

    QString getApiUrl(QString extension);
    ApiRequest getBaseRequest(QString extension);

    JsonParser *jp;

    QString apiKey;
    QString apiBaseUrl;
    QString apiUrlNoPath;

    const QStringList TacoTuesdayPaths
    {
        "/tacos",
        "/employees",
        "/employees/%1",
        "/orders/full",
        "/orders/full/%1",
        "/orders/individual",
        "/orders/individual/%1"
    };
};

#endif // TACOTUESDAYAPICLIENT_H
