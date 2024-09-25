#ifndef ENEMYPLANE2_H
#define ENEMYPLANE2_H
#include <QPixmap>

class enemyplane2
{
public:
    enemyplane2();
    void updatePosition2();//更新坐标
public:
    QPixmap m_enemy2;
    int m_x2;
    int m_y2;
    QRect m_Rect2;
    bool m_Free2;
    int m_Speed2;
};

#endif // ENEMYPLANE2_H
