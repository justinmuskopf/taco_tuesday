#include "ui_mainwindow.h"
#include "QPushButton"
#include "order.h"
#include "configurationdialog.h"

#include <QNetworkReply>
#include <src/jsonparser.h>
#include <src/mainwindow.h>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initTabs();
}

void MainWindow::initTabs()
{
    initGeneralTab();
    initOrderTab();
    initEmployeeTab();
}

void MainWindow::initGeneralTab()
{
    ui->generalTab->setLayout(ui->generalTabLayout);
    tabs.insert(GENERAL_TAB, ui->generalTab);
}


void MainWindow::initOrderTab()
{
    ui->orderTab->setLayout(ui->orderTabLayout);
    tabs.insert(ORDER_TAB, ui->orderTab);

    initTacos();
}

void MainWindow::initEmployeeTab()
{
    ui->employeeTab->setLayout(ui->employeeTabLayout);
    tabs.insert(EMPLOYEE_TAB, ui->employeeTab);

    initEmployees();
}

void MainWindow::initTacos()
{
    QNetworkReply *r = apiHandler.getTacos();
    connect(r, &QNetworkReply::finished, this, [=]{
        qDebug() << r->readAll();
    });
}

void MainWindow::initEmployees()
{
    QNetworkReply *r = apiHandler.getEmployees();
    connect(r, &QNetworkReply::finished, this, [=]{
        QList<Employee *> employees = JsonParser().parseEmployees(r->readAll());
        ui->employeeTable->setEmployees(employees);
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_employeeRefreshButton_clicked()
{
    ApiReply *r = apiHandler.getEmployees();
    connect(r, &ApiReply::finished, this, [=]{
        QList<Employee *> employees = JsonParser().parseEmployees(r->readAll());
        ui->employeeTable->resetData(employees);
    });
}

void MainWindow::on_employeeSaveButton_clicked()
{
    QList<Employee *> employees = ui->employeeTable->save();
    foreach(Employee *employee, employees)
    {
        apiHandler.updateEmployee(employee);
    }
}

void MainWindow::on_actionConfigure_triggered()
{
    ConfigurationDialog *dialog = new ConfigurationDialog();
    dialog->show();
}
