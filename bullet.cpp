#include "bullet.h"

bullet::bullet()
{
    m_Bullet.load(BULLET_PATH);//加载资源
    m_x = GAME_WIGHT*0.5 - m_Bullet.width()*0.5;//子弹坐标
    m_y = GAME_HEIGHT;
    m_Free = true;//子弹状态
    m_Speed = BULLET_SPEED;//子弹速度
    m_Rect.setWidth(m_Bullet.width());
    m_Rect.setHeight(m_Bullet.height());
    m_Rect.moveTo(m_x,m_y);

}

void bullet::updatePosition()
{
    if(m_Free)//空闲状态
    {
        return;
    }
    m_y -= m_Speed;
    m_Rect.moveTo(m_x,m_y);

    if(m_y<=-m_Rect.height())//子弹超出屏幕
    {
        m_Free = true;
    }
}
