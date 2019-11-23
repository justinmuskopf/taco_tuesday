#ifndef TACOTUESDAYAPIHANDLER_H
#define TACOTUESDAYAPIHANDLER_H

#include "employee.h"
#include "taco.h"
#include "tacotuesdayapiclient.h"

#include <QObject>
#include <QNetworkAccessManager>

typedef QNetworkReply ApiReply;

class TacoTuesdayApiHandler : public QObject
{
    Q_OBJECT

public:
    explicit TacoTuesdayApiHandler();

    ApiReply *getTacos();
    ApiReply *getEmployees();
    ApiReply *getEmployeeBySlackId(QString slackId);
    ApiReply *getFullOrders();
    ApiReply *getFullOrderById(QString id);

    ApiReply *updateEmployee(Employee *employee);

signals:
    void on_request();

private:
    typedef TacoTuesdayApiClient::TacoTuesdayRequests TTRequests;
    typedef TacoTuesdayApiClient::HttpOperation TTOperations;

    ApiReply *request(TTRequests requestType, TTOperations operation, QByteArray json="", QString id="");

    static TacoTuesdayApiClient *WebClient;
    static QList<Taco> tacos;
};

#endif // TACOTUESDAYAPIHANDLER_H
