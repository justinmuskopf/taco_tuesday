#include "ui_mainwindow.h"
#include "QPushButton"
#include "order.h"

#include <QNetworkReply>
#include <src/jsonparser.h>
#include <src/mainwindow.h>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initTabs();
    initTacos();
    initEmployees();
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
}

void MainWindow::initEmployeeTab()
{
    ui->employeeTab->setLayout(ui->employeeTabLayout);
    tabs.insert(EMPLOYEE_TAB, ui->employeeTab);
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
    JsonParser *jsonParser = new JsonParser();
    QNetworkReply *r = apiHandler.getEmployees();
    connect(r, &QNetworkReply::finished, this, [=]{
        QString response = r->readAll();
        qDebug() << response;
        QList<Employee *> employees = jsonParser->parseEmployees(response);
        ui->employeeTable->setEmployees(employees);
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}
