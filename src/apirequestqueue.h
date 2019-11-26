#ifndef APIREQUESTQUEUE_H
#define APIREQUESTQUEUE_H

#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QObject>
#include <QQueue>

class ApiRequestQueue : public QObject
{
    Q_OBJECT
public:
    explicit ApiRequestQueue(QObject *parent = nullptr); //QList<DomainObject *> (JsonParser::*jpMethod)(QString)
    //void enqueue(QNetworkRequest r, QNetworkReply * (QNetworkAccessManager::*reply)(QNetworkRequest));
signals:
    //void ready(QNetworkRequest r, QNetworkReply * (QNetworkAccessManager::*reply)(QNetworkRequest));
public slots:
    void requestFinished();

private:
    QQueue<QNetworkRequest> queue;
};

#endif // APIREQUESTQUEUE_H
