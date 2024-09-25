#ifndef ENEMYPLANE_H
#define ENEMYPLANE_H
#include <QPixmap>


class enemyplane
{
public:
    enemyplane();
    void updatePosition();//更新坐标
public:
    QPixmap m_enemy;
    int m_x;
    int m_y;
    QRect m_Rect;
    bool m_Free;
    int m_Speed;
    int attectedNum;
};

#endif // ENEMYPLANE_H
