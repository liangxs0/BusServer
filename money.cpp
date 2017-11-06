#include "money.h"
#include "ui_money.h"

Money::Money(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Money)
{
    ui->setupUi(this);
    this->setWindowTitle("BusSever");
    //设置title
    ui->TitleEdit->setAlignment(Qt::AlignHCenter);
    ui->TitleEdit->setReadOnly(true);
    image.load(":/icons/bus.png");
}
Money::~Money()
{
    delete ui;
}
//图片绘制
void Money::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter p(this);
    QRect tar(15,25,100,100);
    p.drawImage(tar,image);
}
//关闭事件函数
void Money::closeEvent(QCloseEvent *event)
{
    int res = QMessageBox::question(this,"是否退出","是否退出");
    if(res == QMessageBox::Yes){
        return;
    }else{
        event->ignore();//忽略
    }
}
//充值确定按钮
void Money::on_myesBtn_clicked()
{
   QString  id,name,money,null;
   id = ui->mIDEdit->text();
   name = ui->mnameEdit->text();
   money = ui->mmoneyEdit->text();
   if(id == ""||name == ""||money == ""){
       QMessageBox::information(this,"提示","请输入正确完整的信息");
       return;
   }
   Protocol pro;
   QString head = "<addMoney>";
   QString data;
   data = pro.packData(head,id,name,null,null,money);
   //数据处理部分
   pro.translateData(data);
}

void Money::on_mnoBtn_clicked()
{
    Money::close();
}
