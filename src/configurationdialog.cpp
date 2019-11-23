#include "src/configurationdialog.h"
#include "ui_configurationdialog.h"
#include "tacotuesdayconfig.h"

ConfigurationDialog::ConfigurationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfigurationDialog)
{
    ui->setupUi(this);
    config = TacoTuesdayConfig::Instance();

    connect(ui->cooldownDurationSlider, &QSlider::valueChanged, ui->cooldownDurationBox, [&](int value){
       ui->cooldownDurationBox->setText(QString::number(value) + " ms");
    });

    connect(ui->pBarRefreshRateSlider, &QSlider::valueChanged, ui->pBarRefreshRateBox, [&](int value){
        ui->pBarRefreshRateBox->setText(QString::number(value) + "%");
    });

    ui->apiKeyInput->setText(config->ApiKey());
    ui->apiBaseUrlInput->setText(config->ApiBaseUrl());
    ui->pBarRefreshRateSlider->setValue(config->NumSteps());
    ui->cooldownDurationSlider->setValue(config->CooldownMs());

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
    config->setNumSteps(100 - ui->pBarRefreshRateSlider->value());
    config->setCooldownMs(ui->cooldownDurationSlider->value());

    deleteLater();
}
