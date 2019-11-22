#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "tacotuesdayapihandler.h"

#include <QMainWindow>
#include <QMap>
#include <QPushButton>
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
    void on_coolDown_triggered();
    void enableRequestButtons();
    void disableRequestButtons();

private:
    const QString GENERAL_TAB = "general";
    const QString EMPLOYEE_TAB = "employee";
    const QString ORDER_TAB = "order";

    Ui::MainWindow *ui;
    QMap<QString, QWidget*> tabs;
    QTimer *cooldownTimer;
    QList<QPushButton *> requestButtons;

    TacoTuesdayApiHandler apiHandler;
    int progress = 0;
    int cooldownMs = 2000;
    int steps = 10;
    int stepCount = 0;

    void initTabs();
    void initGeneralTab();
    void initEmployeeTab();
    void initOrderTab();
    void cooldownRoutine(int msPerStep);

    void initTacos();
    void initEmployees();

    QList<Taco> tacos;
};

#endif // MAINWINDOW_H
