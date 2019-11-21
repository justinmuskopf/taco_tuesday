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
    static TacoTuesdayApiClient *Instance();

    ApiReply *get(QString path);

signals:

public slots:
    void on_apiKey_updated(QString apiKey);
    void on_apiBaseUrl_updated(QString apiBaseUrl);

private:
    TacoTuesdayApiClient(QObject *parent = nullptr);

    static TacoTuesdayApiClient *instance;

    QString getApiUrl(QString extension);
    ApiRequest getBaseRequest(QString extension);

    QString apiKey;
    QString apiBaseUrl;

    enum TacoTuesdayRequests
    {
        GET_TACOS,
        GET_EMPLOYEES,
        GET_EMPLOYEE_BY_SLACK_ID,
        GET_FULL_ORDERS,
        GET_FULL_ORDER_BY_ID,
        GET_INDIVIDUAL_ORDERS,
        GET_INDIVIDUAL_ORDER_BY_ID,
        CREATE_EMPLOYEE,
        CREATE_FULL_ORDER,
    };
};

#endif // TACOTUESDAYAPICLIENT_H
