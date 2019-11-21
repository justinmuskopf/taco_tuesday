#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "tacotuesdayapihandler.h"

#include <QMainWindow>
#include <QMap>
#include <QTableWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_employeeRefreshButton_clicked();
    void on_employeeSaveButton_clicked();
    void on_actionConfigure_triggered();

private:
    const QString GENERAL_TAB = "general";
    const QString EMPLOYEE_TAB = "employee";
    const QString ORDER_TAB = "order";

    Ui::MainWindow *ui;
    QMap<QString, QWidget*> tabs;

    TacoTuesdayApiHandler apiHandler;

    void initTabs();
    void initGeneralTab();
    void initEmployeeTab();
    void initOrderTab();

    void initTacos();
    void initEmployees();

    QList<Taco> tacos;
};

#endif // MAINWINDOW_H
