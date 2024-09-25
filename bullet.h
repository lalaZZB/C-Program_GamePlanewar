#ifndef BULLET_H
#define BULLET_H
#include "config.h"
#include <QPixmap>

class bullet
{
public:
    bullet();
    void updatePosition();
public:
    QPixmap m_Bullet;//子弹资源对象
    int m_x;//子弹坐标
    int m_y;
    int m_Speed;//子弹速度
    bool m_Free;//子弹状态
    QRect m_Rect;//子弹边框
};

#endif // BULLET_H
