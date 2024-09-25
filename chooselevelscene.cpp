#include "chooselevelscene.h"
#include "ui_chooselevelscene.h"
#include <QPainter>
#include <QPixmap>
#include "mypushbutton.h"
#include "mainscene.h"
#include <QLabel>
#include <QDebug>


ChooseLevelScene::ChooseLevelScene(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ChooseLevelScene)
{
    ui->setupUi(this);

    //点击退出菜单项，实现退出
    connect(ui->actionquit,&QAction::triggered,[=](){
        this->close();
    });

    //设置固定尺寸
    this->setFixedSize(480,852);
    //设置标题
    this->setWindowTitle("翻飞机主场景");
    //设置图标
    this->setWindowIcon(QIcon(":/res/icon72x72.png"));

    //返回按钮
    MyPushButton * backBtn = new MyPushButton(":/res/backbutton_nor.png",":/res/backbutton_p.png");
    backBtn->setParent(this);
    backBtn->move(this->width()-backBtn->width(),this->height()-backBtn->height());

    connect(backBtn,&MyPushButton::clicked,[=](){
        //发送点击信号
        emit this->ChooseSceneBack();

    });

    pScene = NULL;
    //创建20个具体的关卡按钮
    for(int i=0;i<20;i++)
    {
        MyPushButton * menuBtn = new MyPushButton(":/res/LevelIcon.png");

        //关卡按钮文字添加（利用Qlable）
        QLabel * lable = new QLabel;
        lable->setParent(this);
        lable->move((i%4)*90+80,(i/4)*100+150);
        lable->setFixedSize(menuBtn->width(),menuBtn->height());//设置尺寸
        lable->setText(QString::number(i+1));//设置文本
        lable->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

        menuBtn->setParent(this);
        menuBtn->move((i%4)*90+80,(i/4)*100+150);


        //单个关卡的点击信号监听
        connect(menuBtn,&MyPushButton::clicked,[=](){

            //qDebug() <<"第"<<i+1<<"关";
            this->pScene = new PlayScene(i+1);
            this->pScene->show();
            this->hide();
        });
    }

}

ChooseLevelScene::~ChooseLevelScene()
{
    delete ui;
}
//绘制事件
void ChooseLevelScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/background.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    //加载标题
    pix.load(":/res/Title.png");
    painter.drawPixmap(this->width()*0.1,50,pix);


}
