#include "ui_mainwindow.h"
#include "QPushButton"
#include "order.h"
#include "fullorder.h"
#include "configurationdialog.h"

#include <QNetworkReply>
#include <QDebug>
#include <QObject>
#include <QTimer>
#include <src/jsonparser.h>
#include <src/mainwindow.h>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    apiHandler = TacoTuesdayApiHandler::Instance();

    ui->setupUi(this);
    initTabs();

    requestButtons.append(ui->employeeRefreshButton);
    requestButtons.append(ui->employeeSaveButton);
    requestButtons.append(ui->generalRefreshButton);

    ui->requestCooldownBar->setValue(0);
    connect(apiHandler, &TacoTuesdayApiHandler::on_request, this, &MainWindow::on_coolDown_triggered);
    connect(ui->requestCooldownBar, &CooldownBar::cooled, this, &MainWindow::enableRequestButtons);
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
    initOrders();
}

void MainWindow::initEmployeeTab()
{
    ui->employeeTab->setLayout(ui->employeeTabLayout);
    tabs.insert(EMPLOYEE_TAB, ui->employeeTab);

    initEmployees();
}

void MainWindow::initTacos()
{
    Order::initTacos();

    connect(apiHandler, &TacoTuesdayApiHandler::on_finished_getting_tacos, [=](QList<Taco *> tacos){
        qDebug() << tacos;
    });

    apiHandler->requestTacos();
}

void MainWindow::initEmployees()
{
    connect(apiHandler, &TacoTuesdayApiHandler::on_finished_getting_employees, [=](QList<Employee *> employees){
        ui->employeeTable->resetData(employees);
    });

    apiHandler->requestEmployees();
}

void MainWindow::initOrders()
{
    Order::initTacos();

    connect(apiHandler, &TacoTuesdayApiHandler::on_finished_getting_orders, [=](QList<FullOrder *> orders){
       ui->orderTree->setOrders(orders);
    });

    connect(apiHandler, &TacoTuesdayApiHandler::on_finished_getting_tacos, [=](QList<Taco *> tacos){
        apiHandler->requestFullOrders();
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_employeeRefreshButton_clicked()
{
    apiHandler->requestEmployees();
}

void MainWindow::on_employeeSaveButton_clicked()
{
    QList<Employee *> employees = ui->employeeTable->save();
    foreach (Employee *employee, employees)
    {
        apiHandler->updateEmployee(employee);
    }
}

void MainWindow::on_actionConfigure_triggered()
{
    ConfigurationDialog *dialog = new ConfigurationDialog();
    dialog->setAttribute(Qt::WA_DeleteOnClose);
    dialog->show();
}

void MainWindow::disableRequestButtons()
{
    foreach (QPushButton *button, requestButtons)
    {
        button->setEnabled(false);
    }
}

void MainWindow::enableRequestButtons()
{
    foreach (QPushButton *button, requestButtons)
    {
        button->setEnabled(true);
    }
}

void MainWindow::on_coolDown_triggered()
{
    disableRequestButtons();
    ui->requestCooldownBar->beginCoolingSequence();
}

void MainWindow::on_generalRefreshButton_clicked()
{
    apiHandler->refresh();
}
