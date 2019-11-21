#ifndef EMPLOYEEROW_H
#define EMPLOYEEROW_H

#include "employee.h"

#include <QTableWidget>

class EmployeeRow
{
public:
    EmployeeRow(int _row, Employee *_employee);
    void update(Employee *_employee);

    QTableWidgetItem *getColumn(int column);
    QList<QTableWidgetItem *> getColumns();
    void modify(QTableWidgetItem *modifiedColumn);
    bool isModified();
    int rowIndex();
    Employee *save();

    ~EmployeeRow();

    static const int NUM_COLUMNS;
    static const QStringList ColumnLabels;
private:
    void setColumnText(int column, QString text);
    void setColumnChecked(int column, bool checked);
    void makeColumnUneditable(int column);
    void validateColumnNumber(int column);

    enum ColumnIndexes {
        FULL_NAME,
        SLACK_ID,
        NICK_NAME,
        ADMIN
    };

    Employee *employee;
    QList<QTableWidgetItem *> columns;
    QSet<int> modifiedColumns;
    int row;
    bool modified;
};

#endif // EMPLOYEEROW_H
