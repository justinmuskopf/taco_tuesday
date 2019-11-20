#include "employeerow.h"
#include "employeetable.h"

#include <QDebug>

const QStringList EmployeeRow::ColumnLabels = QStringList({"Full Name",
                                                           "Slack ID",
                                                           "Nickname",
                                                           "Is Admin"});
const int EmployeeRow::NUM_COLUMNS = ColumnLabels.size();


EmployeeRow::EmployeeRow(int _row, Employee *_employee)
{ 
    row = _row;
    qDebug() << "Creating employee row (#" << row << ") for"
             << _employee->getFullName() << "(" << _employee->getSlackId() << ")"
             << "( Admin:" << _employee->isAdmin() << ")";

    for (int i = 0; i < NUM_COLUMNS; i++)
    {
        QTableWidgetItem *item = new QTableWidgetItem();
        columns.append(item);
    }

    update(_employee);
}

QTableWidgetItem *EmployeeRow::getColumn(int column)
{
    validateColumnNumber(column);

    return columns[column];
}

QList<QTableWidgetItem *> EmployeeRow::getColumns()
{
    return columns;
}

void EmployeeRow::update(Employee *_employee)
{
    employee = _employee;

    setColumnText(FULL_NAME, employee->getFullName());
    makeColumnUneditable(FULL_NAME);

    setColumnText(SLACK_ID, employee->getSlackId());
    makeColumnUneditable(SLACK_ID);

    setColumnText(NICK_NAME, employee->getNickName());
    setColumnChecked(ADMIN, employee->isAdmin());
}

void EmployeeRow::setColumnText(int column, QString text)
{
    QTableWidgetItem *colItem = getColumn(column);
    colItem->setText(text);
}

void EmployeeRow::setColumnChecked(int column, bool checked)
{
    QTableWidgetItem *colItem = getColumn(column);
    colItem->setCheckState(checked ? Qt::Checked : Qt::Unchecked);
}

void EmployeeRow::makeColumnUneditable(int column)
{
    QTableWidgetItem *colItem = getColumn(column);
    colItem->setFlags(colItem->flags() & ~Qt::ItemIsEditable);
}

void EmployeeRow::validateColumnNumber(int column)
{
    if (column < 0 or column >= NUM_COLUMNS)
    {
        throw "Invalid Column Number provided: " + QString::number(column);
    }
}

EmployeeRow::~EmployeeRow()
{
    for (int i = 0; i < NUM_COLUMNS; i++)
    {
        delete columns[i];
    }
}
