#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <QString>

class Employee
{
public:
    Employee();

    void setFullName(QString _fullName);
    QString getFullName();

    void setNickName(QString _nickName);
    QString getNickName();

    void setSlackId(QString _slackId);
    QString getSlackId();

    void setAdmin(bool _admin);
    bool isAdmin();

private:
    QString fullName;
    QString nickName;
    QString slackId;
    bool admin;
};

#endif // EMPLOYEE_H
