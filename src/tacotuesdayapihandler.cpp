#include <QNetworkReply>
#include <QDebug>
#include <QUrlQuery>
#include <QObject>

#include "tacotuesdayapihandler.h"

QNetworkAccessManager *TacoTuesdayApiHandler::WebClient = new QNetworkAccessManager();


TacoTuesdayApiHandler::TacoTuesdayApiHandler()
{

}

QString TacoTuesdayApiHandler::getApiUrl(QString extension)
{
    return baseApiUrl + "/" + extension;
}

QNetworkReply *TacoTuesdayApiHandler::getTacos()
{
    qDebug() << "Tacos!";
    return WebClient->get(getBaseRequest("tacos"));
}

QNetworkReply *TacoTuesdayApiHandler::getEmployees()
{
    return WebClient->get(getBaseRequest("employees"));
}

QNetworkReply *TacoTuesdayApiHandler::getFullOrders()
{
    return WebClient->get(getBaseRequest("orders/full"));
}

QNetworkRequest TacoTuesdayApiHandler::getBaseRequest(QString extension)
{
    QUrl url(getApiUrl(extension));

    QUrlQuery query;
    query.addQueryItem("apiKey", apiKey);

    url.setQuery(query);

    return QNetworkRequest(url);
}
