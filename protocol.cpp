#include "protocol.h"
Protocol::Protocol(QObject *parent) : QObject(parent)
{
    end = "<end>";
    flag = "<$^$>";
}
//打包函数
QString Protocol::packData(QString head, QString data1, QString data2, QString data3, QString data4, QString data5)
{
    QString temp;
    temp.append(head);
    temp.append(flag);
    temp.append(data1);
    temp.append(flag);
    temp.append(data2);
    temp.append(flag);
    temp.append(data3);
    temp.append(flag);
    temp.append(data4);
    temp.append(flag);
    temp.append(data5);
    temp.append(flag);
    temp.append(end);

    return temp;
}
//解包函数。协议解析
void Protocol::parseData(QByteArray temp,QString &data1, QString &data2, QString &data3, QString &data4, QString &data5)
{
    //1.先删除数据头部
    temp.remove(0,temp.indexOf(flag)+flag.size());
    //2.提取数据
    data1 = temp.mid(0,temp.indexOf(flag));
    //3.删除提取过的数据
    temp.remove(0,temp.indexOf(flag)+flag.size());
    //4.提取数据
    data2 = temp.mid(0,temp.indexOf(flag));
    //5.删除提取过的数据
    temp.remove(0,temp.indexOf(flag)+flag.size());
    //7.提取数据
    data3 = temp.mid(0,temp.indexOf(flag));
    //8.删除提取过的数据
    temp.remove(0,temp.indexOf(flag)+flag.size());
    //9.提取数据
    data4 = temp.mid(0,temp.indexOf(flag));
    //10.删除提取过的数据
    temp.remove(0,temp.indexOf(flag)+flag.size());
    //11.提取数据
    data5 = temp.mid(0,temp.indexOf(flag));
    //12.删除提取过的数据
    temp.remove(0,temp.indexOf(flag)+flag.size());
}
//数据处理
void Protocol::translateData(QString data)
{
    qDebug() << "dataA = " << data;
    QString id,name,call,addr,money;
    QByteArray temp;
    temp = data.toLocal8Bit();//转换数据

    qDebug() << "tempA = " << temp;
    QSqlQuery query;
    //从数据库中拿取数据
    Protocol::parseData(temp,id,name,call,addr,money);//数据解包
    QString cmd = tr("select * from user where ID = '%1' ").arg(id);
    //注册用户时数据处理部分
    if(data.contains("<addUser>")){
        qDebug() << temp;
        qDebug() << id << " "<< name << " "<<" "<< call <<" " <<  addr<<" " << money;
        //数据比对操作
        if(query.exec(cmd)){
            //ID 存在
            if(query.next())
            {
                QMessageBox::warning(NULL,"警告","ID已经存在");
                return;
            }else{
                //ID不存在
                //存入新用户
                QString cm = tr("insert into user values('%1','%2','%3','%4','%5' );").arg(id).arg(name).arg(call).arg(addr).arg(money);
                query.clear();
                query.next();
              //QMessageBox::warning(NULL,"警告","D");
                if(query.exec(cm)){
                    //数据存储成功
                    //QMessageBox::warning(NULL,"警告","D");
                    QMessageBox::information(NULL,"提示","成功注册");

                }
            }
        }
    }
    //充值操作
    if(data.contains("<addMoney>")){
        if(query.exec(cmd)){
        if(query.next()){
            qDebug() << "4 " << query.value(4);
            qDebug()<< "add money" << data;
            qDebug()<< "id = " << id;
            qDebug() << "name = " << name;
            qDebug() << "money= " << money;
            money = QString::number(query.value(4).toInt()+money.toInt());
            qDebug() << "money+ " << money;
            QString cm = tr("update user set Money = '%1' where ID = '%2' ;").arg(money).arg(id);
            query.exec(cm);
            QMessageBox::information(NULL,"提示","充值成功");
         }else{
            QMessageBox::information(NULL,"提示","请先注册");
        }
       }
    }
}
