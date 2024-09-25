#include "enemyplane2.h"
#include "config.h"


enemyplane2::enemyplane2()
{
    m_enemy2.load(ENEMY_PATH2);//敌机资源
    m_x2 = 0;
    m_y2 = 0;
    m_Free2 = true;
    m_Speed2 = ENEMY_SPEED2;
    m_Rect2.setWidth(m_enemy2.width());
    m_Rect2.setHeight(m_enemy2.height());
    m_Rect2.moveTo(m_x2,m_y2);

}

void enemyplane2::updatePosition2()
{
    if(m_Free2)//敌机状态
    {
        return;
    }
    m_y2 += m_Speed2;
    m_Rect2.moveTo(m_x2,m_y2);
    if(m_y2>=GAME_HEIGHT)//超出屏幕
    {
        m_Free2 = true;
    }

}
