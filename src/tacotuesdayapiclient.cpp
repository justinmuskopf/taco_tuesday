#include "tacotuesdayapiclient.h"
#include "tacotuesdayconfig.h"

#include <QUrlQuery>

TacoTuesdayApiClient *TacoTuesdayApiClient::instance = nullptr;

TacoTuesdayApiClient::TacoTuesdayApiClient(QObject *parent) : QNetworkAccessManager(parent)
{
    TacoTuesdayConfig *config = TacoTuesdayConfig::Instance();
    apiKey = config->ApiKey();
    apiBaseUrl = config->ApiBaseUrl();

    connect(config, &TacoTuesdayConfig::on_apiKey_changed, [=](QString _apiKey){
        qDebug() << "Configuration signalled ApiKey has been updated: " << _apiKey;
        apiKey = _apiKey;
    });

    connect(config, &TacoTuesdayConfig::on_apiBaseUrl_changed, [=](QString _apiBaseUrl){
        qDebug() << "Configuration signalled ApiBaseUrl has been updated: " << _apiBaseUrl;
        apiBaseUrl = _apiBaseUrl;
    });
}

TacoTuesdayApiClient *TacoTuesdayApiClient::Instance()
{
    if (!instance)
    {
        instance = new TacoTuesdayApiClient();
    }

    return instance;
}

QString TacoTuesdayApiClient::getApiUrl(QString extension)
{
    return apiBaseUrl + "/" + extension;
}

ApiRequest TacoTuesdayApiClient::getBaseRequest(QString extension)
{
    QUrl url(getApiUrl(extension));

    QUrlQuery query;
    query.addQueryItem("apiKey", apiKey);

    url.setQuery(query);

    return QNetworkRequest(url);
}

ApiReply *TacoTuesdayApiClient::request(HttpOperation op, TacoTuesdayRequests requestType, QByteArray json, QString id)
{
    QString path = TacoTuesdayPaths[requestType];
    if (id != nullptr && !id.isEmpty())
    {
        path = path.arg(id);
    }

    QNetworkRequest r = getBaseRequest(path);

    switch (op)
    {
    case GET:
        return QNetworkAccessManager::get(r);
    case POST:
        return QNetworkAccessManager::post(r, json);
    case PATCH:
        return nullptr; // TODO
    }
}

ApiReply *TacoTuesdayApiClient::request(HttpOperation op, TacoTuesdayRequests requestType, QString id)
{
    return request(op, requestType, nullptr, id);
}

ApiReply *TacoTuesdayApiClient::get(TacoTuesdayRequests requestType, QString id)
{
    return request(GET, requestType, id);
}

ApiReply *TacoTuesdayApiClient::post(TacoTuesdayRequests requestType, QByteArray json, QString id)
{
    return request(POST, requestType, json, id);
}

ApiReply *TacoTuesdayApiClient::patch(TacoTuesdayRequests requestType, QByteArray json, QString id)
{
    //QNetworkRequest r = getBaseRequest(TacoTuesdayPaths[requestType]);
    //return QNetworkAccessManager::get(r);
    return nullptr;
}
