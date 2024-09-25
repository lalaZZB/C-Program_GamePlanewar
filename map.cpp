#include "map.h"
#include "config.h"
map::map()
{
    //加载地图
    m_map1.load(MAP_PATH);
    m_map2.load(MAP_PATH);
    //Y轴
    m_map1_posY = -GAME_HEIGHT;
    m_map2_posY = 0;
    //滚动速度
    m_scroll_speed=MAP_SCROLL_SPEED;
}
void map::mapPosition()
{
    //第一张图片的滚动位置
    m_map1_posY += m_scroll_speed;
    if(m_map1_posY >= 0)
    {
        m_map1_posY = -GAME_HEIGHT;
    }
    m_map2_posY += m_scroll_speed;
    if(m_map2_posY >= GAME_HEIGHT)
    {
        m_map2_posY = 0;
    }
}
