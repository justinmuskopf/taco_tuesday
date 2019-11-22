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

    QNetworkReply *getTacos();
    QNetworkReply *getEmployees();
    QNetworkReply *getEmployeeBySlackId(QString slackId);
    QNetworkReply *getFullOrders();
    QNetworkReply *getFullOrderById(QString id);

    QNetworkReply *updateEmployee(Employee *employee);

signals:
    void on_request();

private:
    static TacoTuesdayApiClient *WebClient;
};

#endif // TACOTUESDAYAPIHANDLER_H
