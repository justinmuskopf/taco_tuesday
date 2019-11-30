#ifndef TACOTUESDAYAPIHANDLER_H
#define TACOTUESDAYAPIHANDLER_H

#include "jsonparser.h"
#include "tacotuesdayapiclient.h"

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class Employee;
class FullOrder;
class Taco;

class TacoTuesdayApiHandler : public QObject
{
    Q_OBJECT

public:
    static TacoTuesdayApiHandler *Instance();

    void requestTacos();
    void requestEmployees();
    void requestEmployeeBySlackId(QString slackId);
    void requestFullOrders();
    void requestFullOrderById(QString id);
    void requestApiStatusCheck();

    void updateEmployees(QList<Employee *> employee);

    void refresh();
signals:
    void on_request();
    void on_finished_getting_employees(QList<Employee *> employees);
    void on_finished_getting_employee_by_slack_id(Employee *employee);
    void on_finished_getting_orders(QList<FullOrder *> orders);
    void on_finished_getting_tacos(QList<Taco *> tacos);
    void on_finished_pinging_api(bool apiIsUp);
    void on_finished_updating_employees(QList<Employee *> employee);
private:
    TacoTuesdayApiHandler();
    static TacoTuesdayApiHandler *instance;

    typedef TacoTuesdayApiClient::TacoTuesdayRequests TTRequests;
    typedef TacoTuesdayApiClient::HttpOperation TTOperations;

    ApiReply *request(TTRequests requestType, TTOperations operation, QList<DomainObject *> (JsonParser::*jpMethod)(QString), QJsonObject json = QJsonObject());

    static TacoTuesdayApiClient *WebClient;
};

#endif // TACOTUESDAYAPIHANDLER_H
