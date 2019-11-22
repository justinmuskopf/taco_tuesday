#include <QDebug>

#include "tacotuesdayconfig.h"

TacoTuesdayConfig *TacoTuesdayConfig::instance = nullptr;

TacoTuesdayConfig::TacoTuesdayConfig()
{
    apiKey = get("api/key");
    apiBaseUrl = get("api/baseUrl");
}

TacoTuesdayConfig *TacoTuesdayConfig::Instance()
{
    if (!instance)
    {
        instance = new TacoTuesdayConfig();
    }

    return instance;
}

void TacoTuesdayConfig::setApiKey(QString _apiKey)
{
    set("api/key", _apiKey);
    apiKey = _apiKey;

    emit on_apiKey_changed(apiKey);
}

void TacoTuesdayConfig::setApiBaseUrl(QString _apiBaseUrl)
{
    set("api/baseUrl", _apiBaseUrl);
    apiBaseUrl = _apiBaseUrl;

    emit on_apiBaseUrl_changed(apiBaseUrl);
}

void TacoTuesdayConfig::setCooldownMs(int _cooldownMs)
{
    QString num = QString::number(_cooldownMs);

    set("cooldownMs", num);
    cooldownMs = cooldownMs;

    emit on_cooldownMs_changed(_cooldownMs);
}

void TacoTuesdayConfig::setNumSteps(int _numSteps)
{
    QString num = QString::number(_numSteps);

    set("numCooldownSteps", num);
    numSteps = num;

    emit on_numSteps_changed(_numSteps);
}

QString TacoTuesdayConfig::ApiKey()
{
    return apiKey;
}

QString TacoTuesdayConfig::ApiBaseUrl()
{
    return apiBaseUrl;
}

int TacoTuesdayConfig::NumSteps()
{
    return numSteps.toInt();
}

int TacoTuesdayConfig::CooldownMs()
{
    return cooldownMs.toInt();
}

QString TacoTuesdayConfig::get(QString key)
{
    QSettings settings(CONFIG_FILENAME, QSettings::IniFormat);

    QVariant v = settings.value(key);
    if (!v.isValid())
    {
        configured = false;
    }

    return v.toString();
}

void TacoTuesdayConfig::set(QString key, QString value)
{
    QSettings settings(CONFIG_FILENAME, QSettings::IniFormat);
    if (get(key) == value)
    {
        return;
    }

    settings.setValue(key, QVariant(value));
}

TacoTuesdayConfig::~TacoTuesdayConfig()
{
}
