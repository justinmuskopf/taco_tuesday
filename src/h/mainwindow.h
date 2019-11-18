#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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

private:
    const QString GENERAL_TAB = "general";
    const QString EMPLOYEE_TAB = "employee";
    const QString ORDER_TAB = "order";

    Ui::MainWindow *ui;
    QMap<QString, QWidget*> tabs;

    QTableWidget *employeeList;

    void initializeTabs();
    void initializeGeneralTab();
    void initializeEmployeeTab();
    void initializeOrderTab();
};
#endif // MAINWINDOW_H
