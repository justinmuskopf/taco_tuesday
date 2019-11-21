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

    friend class ConfigurationDialog;
signals:
    void on_apiKey_changed(QString apiKey);
    void on_apiBaseUrl_changed(QString apiBaseUrl);
private:
    const QString CONFIG_FILENAME = QStandardPaths::writableLocation(QStandardPaths::ConfigLocation) + "/tt_conf.ini";

    TacoTuesdayConfig();
    ~TacoTuesdayConfig();

    static TacoTuesdayConfig *instance;

    QString get(QString key);
    void set(QString key, QString value);

    QString apiKey;
    QString apiBaseUrl;

    bool configured = true;

    void setApiKey(QString _apiKey);
    void setApiBaseUrl(QString _apiBaseUrl);
};

#endif // TACOTUESDAYCONFIG_H
