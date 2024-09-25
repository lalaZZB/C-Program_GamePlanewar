#include "mainscene.h"
#include "ui_mainscene.h"
#include <QPainter>
#include <QPixmap>
#include <QDebug>
#include <QTimer>
#include "mypushbutton.h"
#include <QLabel>


mainscene::mainscene(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::mainscene)
{
    ui->setupUi(this);

    //点击退出菜单项，实现退出
    connect(ui->actionquit,&QAction::triggered,[=](){
        this->close();
    });

    //设置固定尺寸
    this->setFixedSize(480,852);
    //设置标题
    this->setWindowTitle("飞机大战主场景");
    //设置图标
    this->setWindowIcon(QIcon(":/res/icon72x72.png"));

    //创建第二场景
    this->chooseScene = new ChooseLevelScene;

    //创建开始按钮
    MyPushButton *startBtn = new MyPushButton(":/res/stratbutton.png");
    startBtn->setParent(this);
    startBtn->move(this->width()*0.5-startBtn->width()*0.5,this->height()*0.7);

//    //设置开始按钮的文本
//    QLabel * lable = new QLabel;
//    lable->setParent(this);
//    lable->move(this->width()*0.5-startBtn->width()*0.5,this->height()*0.7);
//    lable->setFixedSize(startBtn->width(),startBtn->height());//设置尺寸
//    lable->setText("开始游戏");//设置文本
//    lable->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
//    //设置鼠标穿透属性
//    lable->setAttribute(Qt::WA_TransparentForMouseEvents);

    connect(startBtn,&MyPushButton::clicked,[=](){
       // qDebug() << "进入选关场景";

        startBtn->zoom1();//向下跳跃
        startBtn->zoom2();//像上跳跃

        //延时进入第二场景
        QTimer::singleShot(500,this,[=](){
        this->chooseScene->show();//第二场景显示
        this->hide();//第一场景隐藏
            });
    });
    //监听第二场景返回按钮的信号
    connect(this->chooseScene,&ChooseLevelScene::ChooseSceneBack,[=](){
        //延时切回第一场景
        QTimer::singleShot(500,this,[=](){
        this->show();
        this->chooseScene->hide();
        });
    });
}

//绘图事件
void mainscene::paintEvent(QPaintEvent *)
{
    //创建画家对象
    QPainter painter(this);

    //创建QPixmao对象
    QPixmap pix;
    pix.load(":/res/sd.png");

    //绘制背景
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

//    //加载标题资源
//    pix.load(":/res/Title.png");

//    //缩放图片
//    pix = pix.scaled(pix.width()*0.5,pix.height()*0.5);

//    //绘制标题
//    painter.drawPixmap(10,30,pix);

}

mainscene::~mainscene()
{
    delete ui;
}

