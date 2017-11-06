#ifndef FIND_H
#define FIND_H

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
class Find;
}

class Find : public QWidget
{
    Q_OBJECT

public:
    explicit Find(QWidget *parent = 0);
    ~Find();

protected:
    virtual void paintEvent(QPaintEvent *event);
    void closeEvent(QCloseEvent *event);
private slots:
    void on_fyesBtn_clicked();

    void on_fnoBtn_clicked();

private:
    Ui::Find *ui;
    QImage image;
};

#endif // FIND_H
