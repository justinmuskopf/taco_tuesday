#include "src/configurationdialog.h"
#include "ui_configurationdialog.h"
#include "tacotuesdayconfig.h"

ConfigurationDialog::ConfigurationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfigurationDialog)
{
    ui->setupUi(this);
    config = TacoTuesdayConfig::Instance();

    ui->apiKeyInput->setText(config->ApiKey());
    ui->apiBaseUrlInput->setText(config->ApiBaseUrl());

    setModal(true);
    show();
}

ConfigurationDialog::~ConfigurationDialog()
{
    delete ui;
}

void ConfigurationDialog::on_ConfigurationDialog_accepted()
{
    // TODO: Dynamic config! (ConfigItem)
    config->setApiKey(ui->apiKeyInput->text());
    config->setApiBaseUrl(ui->apiBaseUrlInput->text());

    deleteLater();
}
