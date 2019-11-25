#include "tacotuesdayapiclient.h"
#include "tacotuesdayconfig.h"

#include <QJsonDocument>
#include <QNetworkReply>
#include <QUrlQuery>

TacoTuesdayApiClient *TacoTuesdayApiClient::instance = nullptr;
int TacoTuesdayApiClient::transactionId = 1000;

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

    jp = JsonParser::Instance();
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

ApiReply *TacoTuesdayApiClient::request(HttpOperation op, TacoTuesdayRequests requestType, QList<DomainObject *> (JsonParser::*jpMethod)(QString),
                                        QJsonObject json, QString id)
{
    int transactionId = nextTransactionId();

    QString path = TacoTuesdayPaths[requestType];
    if (id != nullptr && !id.isEmpty())
    {
        path = path.arg(id);
    }

    QNetworkRequest request = getBaseRequest(path);
    QNetworkReply *reply;

    switch (op)
    {
    case GET:
        reply = QNetworkAccessManager::get(request);
        break;
    case POST:
        reply = QNetworkAccessManager::post(request, QJsonDocument(json).toJson());
        break;
    case PATCH:
        return 0; // TODO
    }

    return new ApiReply(transactionId, reply, jpMethod);
}

ApiReply *TacoTuesdayApiClient::request(HttpOperation op, TacoTuesdayRequests requestType, QList<DomainObject *> (JsonParser::*jpMethod)(QString),
                                        QString id)
{
    return request(op, requestType, jpMethod, QJsonObject(), id);
}

int TacoTuesdayApiClient::nextTransactionId()
{
    return ++transactionId;
}
