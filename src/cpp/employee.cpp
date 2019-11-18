#include <src/h/employee.h>

Employee::Employee()
{

}

QString Employee::getFullName() { return fullName; }
void Employee::setFullName(QString _fullName) { fullName = _fullName; }

QString Employee::getNickName() { return nickName; }
void Employee::setNickName(QString _nickName) { nickName = _nickName; }

bool Employee::isAdmin() { return admin; }
void Employee::setAdmin(bool _admin) { admin = _admin; }


QString Employee::getSlackId() { return slackId; }
void Employee::setSlackId(QString _slackId) { slackId = _slackId; }
