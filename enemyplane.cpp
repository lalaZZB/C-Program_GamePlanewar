#include "enemyplane.h"
#include "config.h"

enemyplane::enemyplane()
{
    m_enemy.load(ENEMY_PATH);//敌机资源
    m_x = 0;
    m_y = 0;
    m_Free = true;
    m_Speed = ENEMY_SPEED;
    m_Rect.setWidth(m_enemy.width());
    m_Rect.setHeight(m_enemy.height());
    m_Rect.moveTo(m_x,m_y);
    attectedNum = 0;
}

void enemyplane::updatePosition()
{
    if(m_Free)//敌机状态
    {
        return;
    }
    m_y += m_Speed;
    m_Rect.moveTo(m_x,m_y);
    if(m_y>=GAME_HEIGHT)//超出屏幕
    {
        m_Free = true;
    }

}
