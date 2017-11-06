#ifndef BUS_H
#define BUS_H

#include <QWidget>
#include <QTimer> //定时器
#include <QDateTime> //时间获取
#include <QLineEdit>
#include <QImage> //图片加载器
#include <QPainter> //绘画类
#include <QPaintEvent> //绘制事件
#include <QMenuBar> //菜单栏
#include <QMenu>    //菜单
#include <QDebug>
#include <QMessageBox>
#include <QCloseEvent>
#include <QKeyEvent>
#include <QProgressBar> //使用进度条
#include <QFile>    //文件操作
#include <QFileDialog>
#include <QDir>
#include <QTextStream>
#include <QLabel>
//#include <QProcess>
#include <QDesktopServices>

#include <QTcpServer>
#include <QTcpSocket>
#include <QList>
//开始画面
#include <QPixmap>
#include <QSplashScreen>


#include "add.h"
#include "money.h"
#include "find.h"
namespace Ui {
class Bus;
}

class Bus : public QWidget
{
    Q_OBJECT

public:
    explicit Bus(QWidget *parent = 0);
    ~Bus();
    //创建菜单栏
    void createMenuBar();
    //初始化网络
    void initServer();

    void initSql();//初始化数据库
    void creatUser();//建立数据库
protected:
    virtual void paintEvent(QPaintEvent *event);
    void closeEvent(QCloseEvent *event);
    void keyPressEvent(QKeyEvent *event);
public slots:
    void readySlot();
    void connectSlot();
private slots:
    void timerSlots();
    void openFileSlots();//打开存在的文件
    void on_tjBtn_clicked();

    void on_addBtn_clicked();

    void on_findBtn_clicked();

private:
    Ui::Bus *ui;
    QTimer *timer;
    QImage image;
    QImage image0;
    QImage image1;
    QImage image2;
    //菜单
    QMenuBar *menuBar;
    QMenu *ListMenu;
    QMenu *HelpMenu;
    QAction *Btn0;
    QAction *Btn1;
    QAction *Btn2;
    QAction *quit;
    QAction *about;
    int i = 0;

    QTcpServer *server;
    QList<QTcpSocket*> list;
    //聚合其他类
    Add *add;
    Money *money;
    Find *find;
    QSplashScreen *splash;
};

#endif // BUS_H
