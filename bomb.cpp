#include "bomb.h"

Bomb::Bomb()
{
    for(int i=1;i<=BOMB_MAX;i++)//将爆炸pixmap放入数组中
    {
        QString str = QString(BOMB_PATH).arg(i);
        m_pixarr.push_back(QPixmap(str));
    }
    m_x=0;
    m_y=0;
    m_Free = true;
    m_index = 0;
    m_Recorder = 0;
}

void Bomb::updateInfo()
{
    if(m_Free)//检测爆炸状态
    {
        return;
    }
    m_Recorder++;
    if(m_Recorder<BOMB_INTERVAL)//检测间隔
    {
        return;
    }
    m_Recorder = 0;
    m_index++;
    if(m_index > BOMB_MAX-1)
    {
        m_index = 0;
        m_Free = true;
    }

}
