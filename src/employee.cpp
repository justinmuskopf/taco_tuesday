#include <src/employee.h>
#include <QDebug>
#include <QJsonDocument>

Employee::Employee() {}

Employee::Employee(QString _fullName, QString _nickName, QString _slackId, bool _admin)
{
    fullName = _fullName;
    slackId = _slackId;
    nickName = _nickName;
    admin = _admin;
}

QString Employee::getFullName() { return fullName; }
void Employee::setFullName(QString _fullName) { fullName = _fullName; }

QString Employee::getNickName() { return nickName; }
void Employee::setNickName(QString _nickName) { nickName = _nickName; }

bool Employee::isAdmin() { return admin; }
void Employee::setAdmin(bool _admin) { admin = _admin; }

QString Employee::getSlackId() { return slackId; }
void Employee::setSlackId(QString _slackId) { slackId = _slackId; }

QString Employee::toString()
{
    QString s;
    s += "Full Name: " + fullName + ", ";
    s += "Nick Name: " + nickName + ", ";
    s += "Slack ID : " + slackId + ", ";
    s += "Admin: " + QString(admin ? "true" : "false");

    return s;
}

QByteArray Employee::json()
{
    QJsonObject o;
    o["fullName"] = fullName;
    o["slackId"] = slackId;
    o["nickName"] = nickName;
    o["admin"] = admin;

    return QJsonDocument(o).toJson();
}
