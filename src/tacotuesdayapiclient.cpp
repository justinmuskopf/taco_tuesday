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

ApiReply *TacoTuesdayApiClient::get(QString path)
{
    QNetworkRequest r = getBaseRequest(path);
    return QNetworkAccessManager::get(r);
}
