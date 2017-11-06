//建立数据库存放用户和用来判断用户时候已经存在
#include "add.h"
#include "ui_add.h"

Add::Add(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Add)
{
    ui->setupUi(this);
    this->setWindowTitle("BusSever");
    //设置title
    ui->TitleEdit->setAlignment(Qt::AlignHCenter);
    ui->TitleEdit->setReadOnly(true);
   image.load(":/icons/bus.png");
   //

}

Add::~Add()
{
    delete ui;
}

//图片绘制
void Add::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter p(this);
    QRect tar(15,25,100,100);
    p.drawImage(tar,image);
}
//关闭事件函数
void Add::closeEvent(QCloseEvent *event)
{
    int res = QMessageBox::question(this,"是否退出","是否退出");
    if(res == QMessageBox::Yes){
        return;
    }else{
        event->ignore();//忽略
    }
}
//确认添加用户时
void Add::on_yesBtn_clicked()
{
    QString id,name,call,addr,money;
    id = ui->IdEdit->text();
    name = ui->nameEdit->text();
    call = ui->callEdit->text();
    addr = ui->addrEdit->text();
    money = ui->countEdit->text();
    if(id == ""||name == ""||call == ""||money.toInt() < 100){
        QMessageBox::warning(this,"警告","信息录入错误");
        return;
    }
    Protocol pro;
    QString head = "<addUser>";
    QString data = pro.packData(head,id,name,call,addr,money);//数据打包
    //数据录入前进行数据比对 进行data和数据库的的内容进型比较。
    qDebug() << "data = " << data;
    pro.translateData(data);
}
//取消按钮
void Add::on_noBtn_clicked()
{
    Add::close();
}
