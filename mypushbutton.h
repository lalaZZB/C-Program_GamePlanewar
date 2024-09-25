#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>

class MyPushButton : public QPushButton
{
    Q_OBJECT
public:

    //参数一：正常路径；参数二：按下后图片路径
    MyPushButton(QString normalImg,QString pressImg = "");

    QString normalPath;
    QString pressPath;

    //向下跳跃
    void zoom1();

    //向上跳跃
    void zoom2();

    //鼠标按下事件
    void mousePressEvent(QMouseEvent *e);

    //鼠标释放事件
    void mouseReleaseEvent(QMouseEvent *e);


signals:

};

#endif // MYPUSHBUTTON_H
