#include <src/h/employee.h>

Employee::Employee(QString _fullName, QString _slackId, bool _admin = false)
{
    fullName = _fullName;
    slackId = _slackId;
    admin = _admin;
}
    
Employee::Employee(QString _fullName, QString _nickName, QString _slackId, bool _admin = false)
{
    Employee(_fullName, _slackId, _admin);
    nickName = _nickName;
}

QString Employee::getFullName() { return fullName; }
void Employee::setFullName(QString _fullName) { fullName = _fullName; }

QString Employee::getNickName() { return nickName; }
void Employee::setNickName(QString _nickName) { nickName = _nickName; }

bool Employee::isAdmin() { return admin; }
void Employee::setAdmin(bool _admin) { admin = _admin; }

QString Employee::getSlackId() { return slackId; }
void Employee::setSlackId(QString _slackId) { slackId = _slackId; }
