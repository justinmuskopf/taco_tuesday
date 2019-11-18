#include "ui_mainwindow.h"
#include "QPushButton"

#include <src/h/mainwindow.h>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initializeTabs();

}

void MainWindow::initializeTabs()
{
    ui->generalTab->setLayout(ui->generalTabLayout);
    ui->employeeTab->setLayout(ui->employeeTabLayout);
    ui->orderTab->setLayout(ui->orderTabLayout);

    tabs.insert(GENERAL_TAB, ui->generalTab);
    tabs.insert(EMPLOYEE_TAB, ui->employeeTab);
    tabs.insert(ORDER_TAB, ui->orderTab);
}

void MainWindow::initializeGeneralTab()
{

}

void MainWindow::initializeEmployeeTab()
{

}

void MainWindow::initializeOrderTab()
{

}

MainWindow::~MainWindow()
{
    delete ui;
}
