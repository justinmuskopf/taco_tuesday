#ifndef TACOTUESDAYAPIHANDLER_H
#define TACOTUESDAYAPIHANDLER_H

#include "employee.h"
#include "taco.h"

#include <QObject>
#include <QNetworkAccessManager>

typedef QNetworkReply ApiReply;

class TacoTuesdayApiHandler : public QObject
{
    Q_OBJECT

public:
    explicit TacoTuesdayApiHandler();

    QNetworkReply *getTacos();
    QNetworkReply *getEmployees();
    QNetworkReply *getEmployeeBySlackId(QString slackId);
    QNetworkReply *getFullOrders();
    QNetworkReply *getFullOrderById(QString id);

    QNetworkReply *updateEmployee(Employee *employee);
private:
    static QNetworkAccessManager *WebClient;

    

    QString getApiUrl(QString extension);
    QNetworkRequest getBaseRequest(QString extension);

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

#endif // TACOTUESDAYAPIHANDLER_H
