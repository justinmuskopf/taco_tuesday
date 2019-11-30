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
        columns.append(new QTableWidgetItem());
    }

    modified = false;

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

    modified = false;
    modifiedColumns.clear();
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
        throw QString("Invalid Column Number provided: %1").arg(column);
    }
}

void EmployeeRow::modify(QTableWidgetItem *modifiedColumn)
{
    int column = modifiedColumn->column();
    validateColumnNumber(column);

    modified = true;
    modifiedColumns.insert(column);
}

bool EmployeeRow::isModified()
{
    return modified;
}

int EmployeeRow::rowIndex()
{
    return row;
}

Employee *EmployeeRow::save()
{
    if (!modified)
    {
        return employee;
    }

    foreach (int colIdx, modifiedColumns)
    {
        QTableWidgetItem *column = columns[colIdx];
        switch (colIdx)
        {
        case FULL_NAME:
            employee->setFullName(column->text());
            break;
        case SLACK_ID:
            employee->setSlackId(column->text());
            break;
        case NICK_NAME:
            employee->setNickName(column->text());
            break;
        case ADMIN:
            employee->setAdmin(column->checkState() == Qt::CheckState::Checked);
            break;
        }
    }

    modified = false;
    modifiedColumns.clear();

    return employee;
}

EmployeeRow::~EmployeeRow()
{
    for (int i = 0; i < NUM_COLUMNS; i++)
    {
        delete columns[i];
    }
}
