//网络构建部分
#ifndef NETWORK_H
#define NETWORK_H

#include <QObject>

class NetWork : public QObject
{
    Q_OBJECT
public:
    explicit NetWork(QObject *parent = 0);
    void initnet();
signals:

public slots:
};

#endif // NETWORK_H
