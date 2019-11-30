#include <QDebug>
#include <QUrlQuery>
#include <QObject>
#include <QJsonArray>

#include "tacotuesdayapihandler.h"
#include "employee.h"
#include "taco.h"
#include "fullorder.h"

TacoTuesdayApiClient *TacoTuesdayApiHandler::WebClient = TacoTuesdayApiClient::Instance();
TacoTuesdayApiHandler *TacoTuesdayApiHandler::instance = nullptr;

TacoTuesdayApiHandler *TacoTuesdayApiHandler::Instance()
{
    if (instance == nullptr)
    {
        instance = new TacoTuesdayApiHandler();
    }

    return instance;
}

TacoTuesdayApiHandler::TacoTuesdayApiHandler()
{
    refresh();
}

void TacoTuesdayApiHandler::refresh()
{
    requestTacos();
    requestEmployees();
    requestFullOrders();
    requestApiStatusCheck();
}

ApiReply *TacoTuesdayApiHandler::request(TTRequests requestType, TTOperations operation, QList<DomainObject *> (JsonParser::*jpMethod)(QString),
                                   QJsonObject json)
{
    emit on_request();

    return WebClient->request(operation, requestType, jpMethod, QJsonDocument(json).toJson());
}

void TacoTuesdayApiHandler::requestTacos()
{
    ApiReply *r = request(TTRequests::TACOS, TTOperations::GET, &JsonParser::parseTacos);
    connect(r, &ApiReply::finished, [=](int transId, QList<DomainObject *> objects){
        QList<Taco *> tacos;
        foreach (DomainObject *o, objects) tacos.append(static_cast<Taco *>(o));
        emit on_finished_getting_tacos(tacos);

        r->deleteLater();
    });
}

void TacoTuesdayApiHandler::requestEmployees()
{
    ApiReply *r = request(TTRequests::EMPLOYEES, TTOperations::GET, &JsonParser::parseEmployees);
    connect(r, &ApiReply::finished, [=](int transId, QList<DomainObject *> objects){
        QList<Employee *> employees;
        foreach (DomainObject *o, objects) employees.append(static_cast<Employee *>(o));
        emit on_finished_getting_employees(employees);

        r->deleteLater();
    });
}

void TacoTuesdayApiHandler::requestFullOrders()
{
    ApiReply *r = request(TTRequests::FULL_ORDERS, TTOperations::GET, &JsonParser::parseFullOrders);
    connect(r, &ApiReply::finished, [=](int transId, QList<DomainObject *> objects){

        QList<FullOrder *> fullOrders;
        foreach (DomainObject *o, objects) fullOrders.append(static_cast<FullOrder *>(o));
        emit on_finished_getting_orders(fullOrders);

        r->deleteLater();
    });
}

void TacoTuesdayApiHandler::updateEmployees(QList<Employee *> employees)
{
    QJsonArray jsonObjects;
    foreach (Employee *employee, employees)
    {
        qDebug() << "Adding employee to update list:" << employee;
        jsonObjects.append(employee->serialize());
    }

    ApiReply *r = WebClient->request(TTOperations::PATCH, TTRequests::EMPLOYEES, &JsonParser::parseEmployees, QJsonDocument(jsonObjects).toJson());
    connect(r, &ApiReply::finished, [=](int transId, QList<DomainObject *> objects){
        QList<Employee *> employees;
        foreach (DomainObject *o, objects) employees.append(static_cast<Employee *>(o));

        emit on_finished_updating_employees(employees);

        r->deleteLater();
    });
}

void TacoTuesdayApiHandler::requestApiStatusCheck()
{
    QNetworkReply *r = WebClient->raw_get("/actuator/health");
    connect(r, &QNetworkReply::finished, [=]{
       bool apiIsUp = JsonParser::Instance()->parseApiStatus(r->readAll());
       emit on_finished_pinging_api(apiIsUp);
    });
}

