#include <QDebug>
#include <QUrlQuery>
#include <QObject>

#include "tacotuesdayapihandler.h"
#include "employee.h"
#include "taco.h"
#include "fullorder.h"

TacoTuesdayApiClient *TacoTuesdayApiHandler::WebClient = TacoTuesdayApiClient::Instance();

TacoTuesdayApiHandler::TacoTuesdayApiHandler()
{

}

ApiReply *TacoTuesdayApiHandler::request(TTRequests requestType, TTOperations operation, QList<DomainObject *> (JsonParser::*jpMethod)(QString),
                                   QJsonObject json)
{
    emit on_request();

    return WebClient->request(operation, requestType, jpMethod, json);
}

void TacoTuesdayApiHandler::requestTacos()
{
    ApiReply *r = request(TTRequests::TACOS, TTOperations::GET, &JsonParser::parseTacos);
    connect(r, &ApiReply::finished, [=](QList<DomainObject *> objects){
        QList<Taco> tacos;
        foreach (DomainObject *o, objects) tacos.append(*static_cast<Taco *>(o));
        emit on_finished_getting_tacos(tacos);

        r->deleteLater();
    });
}

void TacoTuesdayApiHandler::requestEmployees()
{
    ApiReply *r = request(TTRequests::EMPLOYEES, TTOperations::GET, &JsonParser::parseEmployees);
    connect(r, &ApiReply::finished, [=](QList<DomainObject *> objects){
        QList<Employee *> employees;
        foreach (DomainObject *o, objects) employees.append(static_cast<Employee *>(o));
        emit on_finished_getting_employees(employees);

        r->deleteLater();
    });
}

void TacoTuesdayApiHandler::requestFullOrders()
{
    ApiReply *r = request(TTRequests::FULL_ORDERS, TTOperations::GET, &JsonParser::parseFullOrders);
    connect(r, &ApiReply::finished, [=](QList<DomainObject *> objects){
        QList<FullOrder *> fullOrders;
        foreach (DomainObject *o, objects) fullOrders.append(static_cast<FullOrder *>(o));
        emit on_finished_getting_orders(fullOrders);

        r->deleteLater();
    });
}

void TacoTuesdayApiHandler::updateEmployee(Employee *employee)
{
    qDebug() << employee->serialize();
    //return nullptr;//WebClient->put
}
