#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include <QWidget>
#include <QTimer>
#include "map.h"
#include "heroplane.h"
#include "bullet.h"
#include "enemyplane.h"
#include "enemyplane2.h"
#include "bomb.h"
#include "overscene.h"
#include <QSound>

class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
    PlayScene(int index);//有参数构造，参数代表当前关卡号
    ~PlayScene();
    int levelIndex;//成员属性，用来记录关卡号

    void initScene();//初始化场景
    void palyGame();//启动游戏
    void updatePosition();//更新坐标
    void paintEvent(QPaintEvent *);//绘制事件
    void mouseMoveEvent(QMouseEvent *);//鼠标事件
    void enemyToScene();//敌机出场
    void enemyToScene2();//敌机出场
    void collisionDetection();//碰撞检测
    void downDetection();//死亡检测
    void overplay();
    enemyplane m_enemys[ENEMY_NUM];//敌机数量
    enemyplane2 m_enemys2[ENEMY_NUM];//敌机数量
    int m_recorder;//敌机计时器
    int m_recorder2;//敌机计时器
    map m_map;//地图对象
    HeroPlane m_hero;//飞机对象
    Bomb m_bombs[BOMB_NUM];//爆炸数量
    bool playpause = true;
    QTimer m_Timer;//定时器
    QSound * BG = new QSound(SOUND_BACKGROUNG);//背景音乐
    int m_score = 0;

    //维护第四个场景的指针
    OverScene * oScene;





signals:

};

#endif // PLAYSCENE_H
