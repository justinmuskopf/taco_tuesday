#ifndef TACOTUESDAYCONFIG_H
#define TACOTUESDAYCONFIG_H

#include "configurationdialog.h"

#include <QObject>
#include <QString>
#include <QSettings>
#include <QStandardPaths>


class TacoTuesdayConfig : public QObject
{
    Q_OBJECT
public:
    static TacoTuesdayConfig *Instance();

    QString ApiKey();
    QString ApiBaseUrl();
    int CooldownMs();
    int NumSteps();


    friend class ConfigurationDialog;
signals:
    void on_apiKey_changed(QString apiKey);
    void on_apiBaseUrl_changed(QString apiBaseUrl);
    void on_cooldownMs_changed(int cooldownMs);
    void on_numSteps_changed(int numSteps);
private:
    const QString CONFIG_FILENAME = QStandardPaths::writableLocation(QStandardPaths::ConfigLocation) + "/tt_conf.ini";

    TacoTuesdayConfig();
    ~TacoTuesdayConfig();

    static TacoTuesdayConfig *instance;

    QString get(QString key);
    void set(QString key, QString value);

    void setApiKey(QString _apiKey);
    void setApiBaseUrl(QString _apiBaseUrl);
    void setCooldownMs(int _cooldownMs);
    void setNumSteps(int _numSteps);

    QString apiKey;
    QString apiBaseUrl;
    QString cooldownMs = "2000";
    QString numSteps = "10";

    bool configured = true;
};

#endif // TACOTUESDAYCONFIG_H
