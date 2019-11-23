#include <QDebug>
#include <QUrlQuery>
#include <QObject>

#include "tacotuesdayapihandler.h"

TacoTuesdayApiClient *TacoTuesdayApiHandler::WebClient = TacoTuesdayApiClient::Instance();


TacoTuesdayApiHandler::TacoTuesdayApiHandler()
{

}

ApiReply *TacoTuesdayApiHandler::request(TTRequests requestType, TTOperations operation, QByteArray json, QString id)
{
    emit on_request();
    return WebClient->request(operation, requestType, json, id);
}

ApiReply *TacoTuesdayApiHandler::getTacos()
{
    return request(TTRequests::TACOS, TTOperations::GET);
}

ApiReply *TacoTuesdayApiHandler::getEmployees()
{
    return request(TTRequests::EMPLOYEES, TTOperations::GET);
}

ApiReply *TacoTuesdayApiHandler::getFullOrders()
{

    return request(TTRequests::FULL_ORDERS, TTOperations::GET);
}

ApiReply *TacoTuesdayApiHandler::updateEmployee(Employee *employee)
{
    qDebug() << employee->json();
    return nullptr;//WebClient->put
}
