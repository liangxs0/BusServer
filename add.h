#ifndef ADD_H
#define ADD_H

#include <QWidget>

#include <QLineEdit>
#include <QImage> //图片加载器
#include <QPainter> //绘画类
#include <QPaintEvent> //绘制事件
#include <QMenuBar> //菜单栏
#include <QMenu>    //菜单
#include <QDebug>
#include <QMessageBox>
#include <QCloseEvent>
//添加数据库
#include <QSqlDatabase>
#include <QSqlQuery>
//
#include "protocol.h"
namespace Ui {
class Add;
}

class Add : public QWidget
{
    Q_OBJECT

public:
    explicit Add(QWidget *parent = 0);
    ~Add();

protected:
    virtual void paintEvent(QPaintEvent *event);
    void closeEvent(QCloseEvent *event);
private slots:
    void on_yesBtn_clicked();

    void on_noBtn_clicked();

private:
    Ui::Add *ui;
    QImage image;
};

#endif // ADD_H
