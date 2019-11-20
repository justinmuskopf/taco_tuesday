#ifndef EMPLOYEETABLE_H
#define EMPLOYEETABLE_H

#include "employee.h"
#include "employeerow.h"

#include <QWidget>
#include <QTableWidget>

class EmployeeTable : public QTableWidget
{
public:
    EmployeeTable(QWidget *parent = nullptr);

    void addEmployee(Employee *employee);
    void setEmployees(QList<Employee *> employees);
    void resetData(QList<Employee *> employees);

    QList<Employee *> save();

private:
    bool hasEmployeeRow(QString slackId);
    EmployeeRow *getEmployeeRow(QString slackId);
    void addEmployeeRow(Employee *employee);
    void setupHeader();

    QMap<QString, EmployeeRow *> rows;
    QList<EmployeeRow *> orderedRows;
private slots:
    void onRowModify(QTableWidgetItem *row);
};

#endif // EMPLOYEETABLE_H
