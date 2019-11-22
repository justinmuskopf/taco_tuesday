#include <QNetworkReply>
#include <QDebug>
#include <QUrlQuery>
#include <QObject>

#include "tacotuesdayapihandler.h"

TacoTuesdayApiClient *TacoTuesdayApiHandler::WebClient = TacoTuesdayApiClient::Instance();

TacoTuesdayApiHandler::TacoTuesdayApiHandler()
{

}

QNetworkReply *TacoTuesdayApiHandler::getTacos()
{
    emit on_request();
    return WebClient->get("tacos");
}

QNetworkReply *TacoTuesdayApiHandler::getEmployees()
{
    emit on_request();
    return WebClient->get("employees");
}

QNetworkReply *TacoTuesdayApiHandler::getFullOrders()
{
    emit on_request();
    return WebClient->get("orders/full");
}

QNetworkReply *TacoTuesdayApiHandler::updateEmployee(Employee *employee)
{
    qDebug() << employee->json();
    emit on_request();
    return nullptr;//WebClient->put
}
