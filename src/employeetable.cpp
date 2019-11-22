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

    connect(this, &EmployeeTable::itemChanged, this, &EmployeeTable::onRowModify);
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
    orderedRows.append(employeeRow);

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

void EmployeeTable::onRowModify(QTableWidgetItem *column)
{
    int col = column->column();
    int row = column->row();

    qDebug() << QString("Column %1, Row %2 modified. Updating!").arg(col).arg(row);

    orderedRows[row]->modify(column);
}

void EmployeeTable::resetData(QList<Employee *> employees)
{
    disconnect(this, &EmployeeTable::itemChanged, this, &EmployeeTable::onRowModify);

    foreach (EmployeeRow *row, rows)
    {
        delete row;
    }

    // Delete rows backwards in case they move up on deletion
    for (int row = rowCount() - 1; row >= 0; row--)
    {
        removeRow(row);
    }

    rows.clear();

    clearContents();
    setEmployees(employees);
}

QList<Employee *> EmployeeTable::save()
{
    QList<Employee *> employees;
    foreach (EmployeeRow *row, rows)
    {
        employees << row->save();
    }

    return employees;
}

EmployeeTable::~EmployeeTable()
{
    foreach (EmployeeRow *row, rows)
    {
        if (row) delete row;
    }
}
