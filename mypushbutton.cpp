#include "mypushbutton.h"
#include <QDebug>
#include <QPropertyAnimation>

MyPushButton::MyPushButton(QString normalImg,QString pressImg)
{
    this->normalPath = normalImg;
    this->pressPath = pressImg;

    //创建QPixmap的对象
    QPixmap pix;
    bool ret = pix.load(this->normalPath);
    if(!ret)
    {
        QString str = QString("图片加载失败，失败的路径是：%1！").arg(this->normalPath);
        qDebug() << str ;
    }
    //设置按钮固定尺寸
    this->setFixedSize(pix.width(),pix.height());
    //设置不规则样式
    this->setStyleSheet("QPushButton{border:0px;}");
    //设置图标
    this->setIcon(pix);
    //设置图标的大小
    this->setIconSize(QSize(pix.width(),pix.height()));

}
//向下跳跃
void MyPushButton::zoom1()
{
    //创建动画对象
    QPropertyAnimation * animation = new QPropertyAnimation(this,"geometry");

    //创建动画间隔
    animation->setDuration(200);

    //创建起始位置
    animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));

    //创建结束位置
    animation->setEndValue(QRect(this->x(),this->y()+10,this->width(),this->height()));

    //创建动画曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);

    //执行动画
    animation->start(QAbstractAnimation::DeleteWhenStopped);

}
void MyPushButton::zoom2()
{
    //创建动画对象
    QPropertyAnimation * animation = new QPropertyAnimation(this,"geometry");

    //创建动画间隔
    animation->setDuration(200);

    //创建起始位置
    animation->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height()));

    //创建结束位置
    animation->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));

    //创建动画曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);

    //执行动画
    animation->start(QAbstractAnimation::DeleteWhenStopped);

}

void MyPushButton::mousePressEvent(QMouseEvent *e)
{
    //若路径不为空，则切换图片
    if(this->pressPath!="")
    {
        //创建QPixmap的对象
        QPixmap pix;
        bool ret = pix.load(this->pressPath);
        if(!ret)
        {
            QString str = QString("图片加载失败，失败的路径是：%1！").arg(this->pressPath);
            qDebug() << str ;
        }
        //设置按钮固定尺寸
        this->setFixedSize(pix.width(),pix.height());
        //设置不规则样式
        this->setStyleSheet("QPushButton{border:0px;}");
        //设置图标
        this->setIcon(pix);
        //设置图标的大小
        this->setIconSize(QSize(pix.width(),pix.height()));
    }

    //其他事情交给父类处理
    QPushButton::mousePressEvent(e);

}

void MyPushButton::mouseReleaseEvent(QMouseEvent *e)
{
    //若路径不为空，则还原图片
    if(this->pressPath!="")
    {
        //创建QPixmap的对象
        QPixmap pix;
        bool ret = pix.load(this->normalPath);
        if(!ret)
        {
            QString str = QString("图片加载失败，失败的路径是：%1！").arg(this->normalPath);
            qDebug() << str ;
        }
        //设置按钮固定尺寸
        this->setFixedSize(pix.width(),pix.height());
        //设置不规则样式
        this->setStyleSheet("QPushButton{border:0px;}");
        //设置图标
        this->setIcon(pix);
        //设置图标的大小
        this->setIconSize(QSize(pix.width(),pix.height()));
    }

    //其他事情交给父类处理
    QPushButton::mouseReleaseEvent(e);

}

