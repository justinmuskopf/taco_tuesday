#ifndef CONFIGURATIONDIALOG_H
#define CONFIGURATIONDIALOG_H

#include <QDialog>

class TacoTuesdayConfig;

namespace Ui {
class ConfigurationDialog;
}

class ConfigurationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConfigurationDialog(QWidget *parent = nullptr);
    ~ConfigurationDialog();

private slots:
    void on_ConfigurationDialog_accepted();

private:
    Ui::ConfigurationDialog *ui;
    TacoTuesdayConfig *config;
};

#endif // CONFIGURATIONDIALOG_H
