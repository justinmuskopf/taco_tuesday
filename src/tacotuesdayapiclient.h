#ifndef TACOTUESDAYAPICLIENT_H
#define TACOTUESDAYAPICLIENT_H

#include <QNetworkAccessManager>
#include <QObject>
#include <QSettings>

typedef QNetworkReply ApiReply;
typedef QNetworkRequest ApiRequest;

class TacoTuesdayApiClient : public QNetworkAccessManager
{
public:
    friend class TacoTuesdayApiHandler;
signals:
    void configured(bool configured);
public slots:
    void on_apiKey_updated(QString apiKey);
    void on_apiBaseUrl_updated(QString apiBaseUrl);

private:
    TacoTuesdayApiClient(QObject *parent = nullptr);

    static TacoTuesdayApiClient *instance;

    static TacoTuesdayApiClient *Instance();

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

    ApiReply *get(TacoTuesdayRequests requestType, QString id = nullptr);
    ApiReply *post(TacoTuesdayRequests requestType, QByteArray json, QString id = QString());
    ApiReply *patch(TacoTuesdayRequests requestType, QByteArray json, QString id = QString());
    ApiReply *request(HttpOperation op, TacoTuesdayRequests requestType, QByteArray json = QByteArray(), QString id = QString());
    ApiReply *request(HttpOperation op, TacoTuesdayRequests requestType, QString id = QString());

    QString getApiUrl(QString extension);
    ApiRequest getBaseRequest(QString extension);

    QString apiKey;
    QString apiBaseUrl;

    const QStringList TacoTuesdayPaths
    {
        "/tacos",
        "/employees",
        "/employees/%1",
        "/orders/full",
        "/orders/full/%1",
        "/orders/individual",
        "/orders/individual/%1",
    };
};

#endif // TACOTUESDAYAPICLIENT_H
