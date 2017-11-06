//协议类
#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <QObject>
#include <QByteArray>
#include <QTcpSocket>
#include <QTcpServer>
#include <QMessageBox>
#include <QDebug>
#include "find.h"

#include <QSqlDatabase>
#include <QSqlQuery>
class Protocol : public QObject
{
    Q_OBJECT
public:
    explicit Protocol(QObject *parent = 0);
    QString packData(QString head,QString data1="",QString data2="",QString data3="",QString data4="",QString data5="");
    void parseData(QByteArray temp,QString &data1,QString &data2,QString &data3,QString &data4,QString &data5);
    void translateData(QString data);
signals:

public slots:
private:
    QString end;
    QString flag;
};

#endif // PROTOCOL_H
