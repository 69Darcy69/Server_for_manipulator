#ifndef MYSERVER_H
#define MYSERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QObject>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>

class myserver: public QTcpServer {
    Q_OBJECT
public:
    myserver();
    ~myserver();
    QTcpSocket* socket;
    QByteArray Data;

    QJsonDocument doc;
    QJsonParseError docError;

public slots:
    void startServer();
    void incomingConnection(qintptr socketDescriptor) override;
    void sockReady();
    void sockDisc();


};

#endif // MYSERVER_H
