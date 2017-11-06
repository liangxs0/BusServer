#include "bus.h"
#include "ui_bus.h"

Bus::Bus(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Bus)
{
   //开机动画
    splash = new QSplashScreen(this);
    QPixmap pixmap("E:/lxs/Bus/icons/bus.png");
    splash->setPixmap(pixmap);
    splash->show();
    for(int i =0;i<50000;i++){
         for(int j = 0;j< 10000;j++){

         }
     }

    splash->close();
//    splash->showMessage("Loaded");
//    qApp->processEvents();
//    splash->showMessage("Established connections");
//    qApp->processEvents();
//    for(int i =0;i<1000;i++){
//        i--;
//    }
//
    //网络初始化
    initServer();
  //
    initSql();
    creatUser();
    //
    this->setWindowIcon(QIcon(":/icons/bus.png"));
    ui->setupUi(this);
    this->setWindowTitle("BusSever");

    //设置title
    ui->TitleEdit->setAlignment(Qt::AlignHCenter);
    ui->TitleEdit->setReadOnly(true);
//    ui->TitleEdit->setFont(QFont("宋体",27,81,true));
    //图片加载
    image.load(":/icons/bus.png");
    image0.load(":/icons/1.png");
    image1.load(":/icons/2.png");
    image2.load(":/icons/3.png");   
//菜单栏函数
    createMenuBar();
 //时间显示
    QString timestr = QDateTime::currentDateTime().toString("yyyy-MM-dd dddd hh:mm:ss");
    ui->TimeEdit->setText(timestr);
    timer = new QTimer;
    //绑定定时器槽函数
    connect(timer,SIGNAL(timeout()),this,SLOT(timerSlots()));
    timer->start(10);//启动定时器
 //进度条
    ui->bus0Bar->setRange(0,100-1);
    ui->bus0Bar->setValue(0);
    ui->bus1Bar->setRange(0,200-1);
    ui->bus1Bar->setValue(0);
    ui->bus2Bar->setRange(0,300-1);
    ui->bus2Bar->setValue(0);
    //设置SeverEdit为只读
    ui->ServerEdit->setReadOnly(true);
}

Bus::~Bus()
{
    delete ui;
}
//创建菜单栏
void Bus::createMenuBar()
{
    menuBar = new QMenuBar(this);
    menuBar->setFixedHeight(25);
    menuBar->setStyleSheet("background:rgb(223, 223, 223)");
    ListMenu = menuBar->addMenu("快捷列表");
    ListMenu->setStyleSheet("color:#aa0000");
    HelpMenu = menuBar->addMenu("帮助");
    HelpMenu->setStyleSheet("color:#aa0000");
    //添加动作
    Btn0 = ListMenu->addAction(QIcon(":/icons/add.png"),"充值");
    Btn0->setShortcut(QKeySequence("Ctrl+M"));
    Btn1 = ListMenu->addAction(QIcon(":/icons/find.png"),"查询");
    Btn1->setShortcut(QKeySequence("Ctrl+F"));
    Btn2 = ListMenu->addAction(QIcon(":/icons/D.png"),"添加");
    Btn2->setShortcut(QKeySequence("Ctrl+D"));
    quit = ListMenu->addAction(QIcon(":/icons/quit.ico"),"退出");
    quit->setShortcut(QKeySequence("Esc"));
    about = HelpMenu->addAction(QIcon(":/icons/help.png"),"打开帮助");
    about->setShortcut(QKeySequence("Ctrl+H"));
    //差帮助
    connect(Btn0,SIGNAL(triggered(bool)),this,SLOT(on_addBtn_clicked()));
    connect(Btn1,SIGNAL(triggered(bool)),this,SLOT(on_findBtn_clicked()));
    connect(Btn2,SIGNAL(triggered(bool)),this,SLOT(on_tjBtn_clicked()));
    connect(quit,SIGNAL(triggered(bool)),this,SLOT(close()));
    connect(about,SIGNAL(triggered(bool)),this,SLOT(openFileSlots()));
}

//图片绘制
void Bus::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter p(this);
    QRect tar(15,25,100,100);
    p.drawImage(tar,image);
    QRect tar0(15,125,50,50);
    p.drawImage(tar0,image0);
    QRect tar1(15,210,50,50);
    p.drawImage(tar1,image1);
    QRect tar2(15,300,50,50);
    p.drawImage(tar2,image2);

}
//关闭事件函数
void Bus::closeEvent(QCloseEvent *event)
{
    int res = QMessageBox::question(this,"是否退出","是否退出");
    if(res == QMessageBox::Yes){
        return;
    }else{
        event->ignore();//忽略
    }
}


//网络初始化
void Bus::initServer()
{
    server = new QTcpServer;
    server->listen(QHostAddress::AnyIPv4,8080);//端口号
    connect(server,SIGNAL(newConnection()),this,SLOT(connectSlot()));
}
//数据库初始化
void Bus::initSql()
{
    QSqlDatabase db;//加载驱动
    db = QSqlDatabase::addDatabase("QSQLITE");
    //指定数据库
    db.setDatabaseName("User.db");
    //打开数据库
    if(db.open()){
        qDebug() << "open susscess";
    }else{
        qDebug() << "open fail";
        return;
    }
}
//建立用户表
void Bus::creatUser()
{
    //构造对象
    QSqlQuery query;
    //准备SQL命令
    QString cmd = "create table user if not exists(ID vachar(12) primary key,Name vachar(12) not null,Call vachar(13),Addr vachar(10),Money vachar(10) not null); ";
    if(query.exec(cmd)){
        qDebug()<<"create table success";
    }else{
        qDebug() << "create fail";
    }
    query.exec("insert into user values('123','123','123','123','1232');");
    query.exec("SELECT * FROM user;");
    while(query.next()){
        qDebug()<<query.value(0);
    }
}

//读取客户端数据
void Bus::readySlot()
{
    QByteArray data;
    QTcpSocket *s = (QTcpSocket*)sender();
    while(s->bytesAvailable()){
        data.append(s->readAll());
    }
    //解析数据。。。。以后添加
    ui->ServerEdit->append(data);
}
//新客户连接
//需要在服务端建立哈希表，确定使用卡的用户
void Bus::connectSlot()
{
    QTcpSocket *socket;
    //给客户端分配套接字
    socket = server->nextPendingConnection();
    QString ip = socket->peerAddress().toString();
    ui->ServerEdit->append("["+ip+"]:上线");
    connect(socket,SIGNAL(readyRead()),this,SLOT(readySlot()));
}
//定时器槽函数
void Bus::timerSlots()
{
  QString timestr = QDateTime::currentDateTime().toString("yyyy-MM-dd dddd hh:mm:ss");
  ui->TimeEdit->setText(timestr);
  ui->TimeEdit->setAlignment(Qt::AlignHCenter);
  ui->TimeEdit->setReadOnly(true);
  i = i+1;
//  qDebug() << i;
  if(i <= 100){
      ui->bus0Bar->setValue(i);
      ui->bus1Bar->setValue(i);
      ui->bus2Bar->setValue(i);
  }else if (i > 100 && i <=200){
      ui->bus1Bar->setValue(i);
      ui->bus2Bar->setValue(i);
  }else if(i > 200 && i <300){
      ui->bus2Bar->setValue(i);
  }else if(i == 300){
      i = 0;
  }
}
//打开文件.帮助文档
void Bus::openFileSlots()
{
    QString runPath = QCoreApplication::applicationDirPath();       //获取exe路劲。
    QString helpName = "help.txt";
    QString helpPath = QString("%1/%2").arg(runPath).arg(helpName);
    QFile bfilePath(helpPath);
    if(!bfilePath.exists()){
        return;
    }
    QString filePath = "file:///" + helpPath;   //打开文件夹用filse:
    QDesktopServices::openUrl(QUrl::fromLocalFile(filePath));
}
void Bus::keyPressEvent(QKeyEvent *event)
{
    Q_UNUSED(event);
}
//添加用户
void Bus::on_tjBtn_clicked()
{
    add = new Add;
    add->setWindowModality(Qt::ApplicationModal);
    add->show();
}

void Bus::on_addBtn_clicked()
{
    money = new Money;
    money->setWindowModality(Qt::ApplicationModal);
    money->show();
    //this->setEnabled(false);
}

void Bus::on_findBtn_clicked()
{
    find = new Find;
    find->setWindowModality(Qt::ApplicationModal);
    find->show();
}
