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
    return WebClient->get("tacos");
}

QNetworkReply *TacoTuesdayApiHandler::getEmployees()
{
    return WebClient->get("employees");
}

QNetworkReply *TacoTuesdayApiHandler::getFullOrders()
{
    return WebClient->get("orders/full");
}

QNetworkReply *TacoTuesdayApiHandler::updateEmployee(Employee *employee)
{
    return nullptr;//WebClient->put
}
