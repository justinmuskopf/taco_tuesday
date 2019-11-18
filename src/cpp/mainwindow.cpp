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
    initializeGeneralTab();
    initializeOrderTab();
    initializeEmployeeTab();
}

void MainWindow::initializeGeneralTab()
{
    ui->generalTab->setLayout(ui->generalTabLayout);
    tabs.insert(GENERAL_TAB, ui->generalTab);
}

void MainWindow::initializeEmployeeTab()
{
    ui->employeeTab->setLayout(ui->employeeTabLayout);
    tabs.insert(EMPLOYEE_TAB, ui->employeeTab);
}

void MainWindow::initializeOrderTab()
{
    ui->orderTab->setLayout(ui->orderTabLayout);
    tabs.insert(ORDER_TAB, ui->orderTab);
}

MainWindow::~MainWindow()
{
    delete ui;
}
