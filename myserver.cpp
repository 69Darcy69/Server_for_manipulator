#include "myserver.h"

myserver::myserver(){}
myserver::~myserver(){}

void myserver::startServer() {
    if (this->listen(QHostAddress::Any, 502)){
        qDebug() << "Connected successfully";
    }
    else {
        qDebug() << "No connect";
    }
}

void myserver::incomingConnection(qintptr socketDescriptor) {
    socket = new QTcpSocket(this);
    socket->setSocketDescriptor(socketDescriptor);
    connect(socket, &QTcpSocket::readyRead, this, &myserver::sockReady);
    connect(socket, &QTcpSocket::disconnected, this, &myserver::sockDisc);
}

void myserver::sockReady() {
        socket->waitForReadyRead(500);
        Data = socket->readAll();
        doc = QJsonDocument::fromJson(Data, &docError);
        if (docError.error == QJsonParseError::NoError) {
            if (doc.isObject()) {
                QJsonObject json = doc.object();
                    if (json.contains("manipulator") && json.contains("x") && json.contains("y")) {
                        int manipulator = json["manipulator"].toInt();
                        double x = json["x"].toString().toDouble();
                        double y = json["y"].toString().toDouble();
                        qDebug() << manipulator << ":" << x << y;
                        json["x"] = x * 100 + 10 - 20;
                        json["y"] = y * 2 - 3 + 10;
                        QByteArray packadge = QJsonDocument(json).toJson();
                        socket->write(packadge);
                    }
                    else if (json.contains("manipulator") && json.contains("x1") && json.contains("y1") && json.contains("x2") && json.contains("y2")) {
                        int manipulator = json["manipulator"].toInt();
                        double x1 = json["x1"].toString().toDouble();
                        double y1 = json["y1"].toString().toDouble();
                        double x2 = json["x2"].toString().toDouble();
                        double y2 = json["y2"].toString().toDouble();
                        qDebug() << manipulator << ":" << x1 << y1 << x2 << y2;
                        json["x1"] = x1 * 100 + 10 - 20;
                        json["y1"] = y1 * 2 - 3 + 10;
                        json["x2"] = x2 * 100 + 10 - 20;
                        json["y2"] = y2 * 2 - 3 + 10;
                        QByteArray packadge = QJsonDocument(json).toJson();
                        socket->write(packadge);
                    }
                    else {
                        qDebug() << "JSON does not meet expectations";
                    }
            }
            else {
                qDebug() << "Not JSON object";
            }
        }
        else {
            qDebug() << "JSON error:" << docError.errorString();
        }
}

void myserver::sockDisc() {
    socket->deleteLater();
    qDebug() << "Disconnected";
}
