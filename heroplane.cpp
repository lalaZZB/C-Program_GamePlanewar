#include "heroplane.h"
#include "config.h"
#include <QSound>

HeroPlane::HeroPlane()
{
    m_Plane.load(HERO_PATH);//加载资源
    m_x = (GAME_WIGHT - m_Plane.width())*0.5;//初始化飞机坐标
    m_y = GAME_HEIGHT - m_Plane.height();
    m_Rect.setWidth(m_Plane.width()-30);
    m_Rect.setHeight(m_Plane.height()-30);
    m_Rect.moveTo(m_x,m_y);
}

void HeroPlane::shoot()//发射子弹
{
    m_recorder++;//计时器累加
    if(m_recorder<BULLET_INTERVAL)
    {
        return;
    }
    m_recorder = 0;
    for(int i=0;i<BULLET_NUM;i++)
    {
        if(m_bullets[i].m_Free)
        {
             m_bullets[i].m_Free = false;
             m_bullets[i].m_x = m_x + 5;
             m_bullets[i].m_y = m_y - 45;
             QSound::play(SOUND_BULLET);
             break;
        }
    }
}
void HeroPlane::shoot2()//发射子弹
{
    m_recorder2++;//计时器累加
    if(m_recorder2<BULLET_INTERVAL)
    {
        return;
    }
    m_recorder2 = 0;
    for(int i=0;i<BULLET_NUM;i++)
    {
        if(m_bullets2[i].m_Free)
        {
             m_bullets2[i].m_Free = false;
             m_bullets2[i].m_x = m_x + 85;
             m_bullets2[i].m_y = m_y - 45;
             QSound::play(SOUND_BULLET);
             break;
        }
    }
}

void HeroPlane::setPosition(int x, int y)
{
    m_x = x;
    m_y = y;
    m_Rect.moveTo(m_x,m_y);
}
