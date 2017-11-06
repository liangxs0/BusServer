#ifndef MONEY_H
#define MONEY_H

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

#include <QSqlDatabase>
#include <QSqlQuery>

#include "protocol.h"
namespace Ui {
class Money;
}

class Money : public QWidget
{
    Q_OBJECT

public:
    explicit Money(QWidget *parent = 0);
    ~Money();
protected:
    virtual void paintEvent(QPaintEvent *event);
    void closeEvent(QCloseEvent *event);
private slots:
    void on_myesBtn_clicked();

    void on_mnoBtn_clicked();

private:
    Ui::Money *ui;
    QImage image;
};

#endif // MONEY_H
