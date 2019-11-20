#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <QJsonObject>
#include <QString>

class Employee
{
public:
    Employee();
    Employee(QString _fullName, QString _slackId, QString _nickName = "", bool _admin = false);

    void setFullName(QString _fullName);
    QString getFullName();

    void setNickName(QString _nickName);
    QString getNickName();

    void setSlackId(QString _slackId);
    QString getSlackId();

    void setAdmin(bool _admin);
    bool isAdmin();

    QString toString();
    QJsonObject json();

private:
    QString fullName;
    QString nickName;
    QString slackId;
    bool admin;
};

#endif // EMPLOYEE_H
