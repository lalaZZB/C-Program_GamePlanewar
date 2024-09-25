#ifndef HEROPLANE_H
#define HEROPLANE_H
#include <QPixmap>
#include <QRect>
#include "bullet.h"

class HeroPlane
{
public:
    HeroPlane();
    void shoot();//射击
    void shoot2();//射击2
    void setPosition(int x,int y);//设置飞机位置
public:
    QPixmap m_Plane;//飞机资源
    int m_x;//飞机坐标
    int m_y;
    QRect m_Rect;//飞机判定范围
    bullet m_bullets[BULLET_NUM];//弹夹
    bullet m_bullets2[BULLET_NUM];//弹夹
    int m_recorder;//发射间隔记录
    int m_recorder2;//发射间隔记录2
};

#endif // HEROPLANE_H
