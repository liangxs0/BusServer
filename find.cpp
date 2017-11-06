#include "find.h"
#include "ui_find.h"

Find::Find(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Find)
{
    ui->setupUi(this);
    this->setWindowTitle("BusSever");
    //设置title
    ui->TitleEdit->setAlignment(Qt::AlignHCenter);
    ui->TitleEdit->setReadOnly(true);
   image.load(":/icons/bus.png");
}

Find::~Find()
{
    delete ui;
}

//图片绘制
void Find::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter p(this);
    QRect tar(15,25,100,100);
    p.drawImage(tar,image);
}
//关闭事件函数
void Find::closeEvent(QCloseEvent *event)
{
    int res = QMessageBox::question(this,"是否退出","是否退出");
    if(res == QMessageBox::Yes){
        return;
    }else{
        event->ignore();//忽略
    }
}
//用户查询
void Find::on_fyesBtn_clicked()
{
    QString id,name,null;
    ui->fmoneyEdit->setReadOnly(true);
    id = ui->fIDEdit->text();
    name = ui->fnameEdit->text();
    QSqlQuery query;
    QString cm = tr("select * from user where ID = '%1' ").arg(id);
    if(query.exec(cm)){
        if(query.next()){
            ui->fmoneyEdit->setText(query.value(4).toString());
        }else{
            QMessageBox::information(this,"提示","用户不存在");
        }
    }
}
//退出按钮
void Find::on_fnoBtn_clicked()
{
    Find::close();
}
