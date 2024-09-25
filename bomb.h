#ifndef BOMB_H
#define BOMB_H
#include "config.h"
#include <QPixmap>
#include <QVector>

class Bomb
{
public:
    Bomb();
    void updateInfo();//更新信息
public:
    QVector<QPixmap> m_pixarr;//爆炸资源数组
    int m_x;//爆炸位置
    int m_y;
    bool m_Free;//爆炸状态
    int m_Recorder;//爆炸时间间隔
    int m_index;//爆炸下标

};

#endif // BOMB_H
