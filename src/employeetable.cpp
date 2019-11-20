#include "employeetable.h"

#include <QHeaderView>
#include <QDebug>

EmployeeTable::EmployeeTable(QWidget *parent) : QTableWidget(parent)
{
    setColumnCount(EmployeeRow::NUM_COLUMNS);
}

bool EmployeeTable::hasEmployeeRow(QString slackId)
{
    return rows.contains(slackId);
}

EmployeeRow *EmployeeTable::getEmployeeRow(QString slackId)
{
    return rows.value(slackId);
}

void EmployeeTable::addEmployee(Employee *employee)
{
    QString slackId = employee->getSlackId();
    if (hasEmployeeRow(slackId))
    {
        getEmployeeRow(slackId)->update(employee);
    }
    else
    {
        addEmployeeRow(employee);
    }
}

void EmployeeTable::setEmployees(QList<Employee *> employees)
{
    foreach (Employee *employee, employees)
    {
        addEmployee(employee);
    }
}

void EmployeeTable::addEmployeeRow(Employee *employee)
{
    int row = rowCount();
    insertRow(row);

    // Workaround for a dumb bug where a row needs to exist
    // for a header to be visible
    if (row == 0)
    {
        setupHeader();
    }

    EmployeeRow *employeeRow = new EmployeeRow(row, employee);
    rows.insert(employee->getSlackId(), employeeRow);

    QList<QTableWidgetItem *> columns = employeeRow->getColumns();
    for (int col = 0; col < columns.size(); col++)
    {
        setItem(row, col, columns[col]);
    }
}

void EmployeeTable::setupHeader()
{
    QHeaderView *header = horizontalHeader();
    header->setSectionResizeMode(QHeaderView::Stretch);
    header->setVisible(true);
    setHorizontalHeaderLabels(EmployeeRow::ColumnLabels);

    verticalHeader()->setVisible(true);
}
