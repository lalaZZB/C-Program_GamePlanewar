#include "playscene.h"
#include <QDebug>
#include <QMenuBar>
#include <QPainter>
#include <QPixmap>
#include "config.h"
#include <QIcon>
#include <QPainter>
#include <QMouseEvent>
#include <ctime>
#include <QSound>
#include <QObject>
#include <QPushButton>
#include "overscene.h"

PlayScene::PlayScene(int index)
{
    this->levelIndex = index;
    qDebug() << "已进入第"<<this->levelIndex<<"关";

    //设置固定尺寸
    this->setFixedSize(480,852);
    //设置标题
    this->setWindowTitle("选关场景");
    //设置图标
    this->setWindowIcon(QIcon(":/res/icon72x72.png"));
    //设置菜单
    QMenuBar * bar = menuBar();
    QMenu * startMenu = bar->addMenu("开始");
    QAction * quitAction = startMenu->addAction("退出");
    connect(quitAction,&QAction::triggered,[=](){
        this->close();
    });
    //创建结束场景
    this->oScene = new OverScene;

    initScene();//场景初始化
    palyGame();//开始游戏
    overplay();//结束游戏

}
PlayScene::~PlayScene()
{
}
void PlayScene::initScene()//初始化游戏数据
{
    setFixedSize(GAME_WIGHT,GAME_HEIGHT);//窗口大小
    setWindowTitle(GAME_TITLE);//窗口标题
    setWindowIcon(QIcon(":/res/icon72x72.png"));//图标
    m_Timer.setInterval(GAME_RATE);//定时器
    m_recorder = 0;//敌机计时器初始化
    m_recorder2 = 0;//敌机2计时器初始化
    srand((unsigned int)time(NULL));
}

void PlayScene::palyGame()
{

        m_Timer.start();//启动定时器
        BG->play();
        connect(&m_Timer , &QTimer::timeout , [=](){
            if(playpause)
            {
            enemyToScene();//敌机出场
            enemyToScene2();//敌机出场
            updatePosition();//更新坐标
            update();//绘制
            collisionDetection();//碰撞检测
            downDetection();//死亡检测
            }

    });

}

void PlayScene::updatePosition()
{
    m_map.mapPosition();//更新坐标
    m_hero.shoot();//发射子弹
    m_hero.shoot2();//发射子弹2
    for(int i=0;i<BULLET_NUM;i++)//子弹坐标更新
    {
        if(m_hero.m_bullets[i].m_Free==false)
        {
             m_hero.m_bullets[i].updatePosition();
        }
    }
    for(int i=0;i<BULLET_NUM;i++)//子弹2坐标更新
    {
        if(m_hero.m_bullets2[i].m_Free==false)
        {
             m_hero.m_bullets2[i].updatePosition();
        }
    }
    for(int i=0;i<ENEMY_NUM;i++)//敌机坐标更新
    {
        if(m_enemys[i].m_Free == false)
        {
            m_enemys[i].updatePosition();
        }
    }
    for(int i=0;i<ENEMY_NUM;i++)//敌机2坐标更新
    {
        if(m_enemys2[i].m_Free2 == false)
        {
            m_enemys2[i].updatePosition2();
        }
    }
    for(int i=0;i<BOMB_NUM;i++)//爆炸状态更新
    {
        if(m_bombs[i].m_Free==false)
        {
            m_bombs[i].updateInfo();
        }
    }

}

void PlayScene::paintEvent(QPaintEvent *)
{
     QPainter painter(this);//绘制地图
     painter.drawPixmap(0,m_map.m_map1_posY,m_map.m_map1);
     painter.drawPixmap(0,m_map.m_map2_posY,m_map.m_map2);
     painter.drawPixmap(m_hero.m_x,m_hero.m_y,m_hero.m_Plane);//绘制飞机
     for(int i=0;i<BULLET_NUM;i++)//绘制子弹
     {
         if(m_hero.m_bullets[i].m_Free==false)
         {
             painter.drawPixmap(m_hero.m_bullets[i].m_x,m_hero.m_bullets[i].m_y,m_hero.m_bullets[i].m_Bullet);
         }
     }
     for(int i=0;i<BULLET_NUM;i++)//绘制子弹2
     {
         if(m_hero.m_bullets2[i].m_Free==false)
         {
             painter.drawPixmap(m_hero.m_bullets2[i].m_x,m_hero.m_bullets2[i].m_y,m_hero.m_bullets2[i].m_Bullet);
         }
     }
     for(int i=0;i<ENEMY_NUM;i++)//绘制敌机
     {
         if(m_enemys[i].m_Free==false)
         {
             painter.drawPixmap(m_enemys[i].m_x,m_enemys[i].m_y,m_enemys->m_enemy);
         }
     }
     for(int i=0;i<ENEMY_NUM;i++)//绘制敌机2
     {
         if(m_enemys2[i].m_Free2==false)
         {
             painter.drawPixmap(m_enemys2[i].m_x2,m_enemys2[i].m_y2,m_enemys2->m_enemy2);
         }
     }
     for(int i=0;i<BOMB_NUM;i++)//绘制爆炸
     {
         if(m_bombs[i].m_Free==false)
         {
             painter.drawPixmap(m_bombs[i].m_x,m_bombs[i].m_y,m_bombs[i].m_pixarr[m_bombs[i].m_index]);
         }
     }
}

void PlayScene::mouseMoveEvent(QMouseEvent * event)
{
    int x = event->x() - m_hero.m_Rect.width()*0.5;
    int y = event->y() - m_hero.m_Rect.height()*0.5;;

    if( x <= 0)//边界检测
    {
        x = 0;
    }
    if(x>=GAME_WIGHT-m_hero.m_Rect.width())
    {
        x=GAME_WIGHT-m_hero.m_Rect.width();
    }
    if( y <= 0)
    {
        y = 0;
    }
    if(y>=GAME_HEIGHT-m_hero.m_Rect.height())
    {
        y=GAME_HEIGHT-m_hero.m_Rect.height();
    }
    m_hero.setPosition(x,y);

}

void PlayScene::enemyToScene()
{
    m_recorder++;
    if(m_recorder<ENEMY_INITERVAL)//未达到出场间隔
    {
        return;
    }
    m_recorder = 0;
    for(int i=0;i<ENEMY_NUM;i++)//空闲敌机出场
    {
        if(m_enemys[i].m_Free)
        {
            m_enemys[i].m_Free = false;
            m_enemys[i].m_x = rand()%(GAME_WIGHT - m_enemys[i].m_Rect.width());
            m_enemys[i].m_y = -m_enemys[i].m_Rect.height();
            break;
        }
    }

}
void PlayScene::enemyToScene2()
{
    m_recorder2++;
    if(m_recorder2<ENEMY_INITERVAL2)//未达到出场间隔
    {
        return;
    }
    m_recorder2 = 0;
    for(int i=0;i<ENEMY_NUM;i++)//空闲敌机出场
    {
        if(m_enemys2[i].m_Free2)
        {
            m_enemys2[i].m_Free2 = false;
            m_enemys2[i].m_x2 = rand()%(GAME_WIGHT - m_enemys2[i].m_Rect2.width());
            m_enemys2[i].m_y2 = -m_enemys2[i].m_Rect2.height();
            break;
        }
    }

}

void PlayScene::collisionDetection()//碰撞检测
{
    for(int i=0;i<ENEMY_NUM;i++)//检测飞机状态
    {
        if(m_enemys[i].m_Free)
        {
            continue;
        }
        for(int j=0;j<BULLET_NUM;j++)//检测子弹状态
        {
            if(m_hero.m_bullets[j].m_Free)
            {
                continue;
            }
            if(m_enemys[i].m_Rect.intersects(m_hero.m_bullets[j].m_Rect))
            {
                if(m_enemys[i].attectedNum<4)
                {
                m_enemys[i].attectedNum++;
                }
                else
                {
                m_enemys[i].attectedNum = 0;
                m_enemys[i].m_Free = true;
                m_hero.m_bullets[j].m_Free = true;
                QSound::play(SOUND_ENEMYDOWN);
                for(int k=0;k<BOMB_NUM;k++)
                {
                    if(m_bombs[k].m_Free)
                    {
                        m_bombs[k].m_Free=false;
                        m_bombs[k].m_x = m_enemys[i].m_x;
                        m_bombs[k].m_y = m_enemys[i].m_y;
                        break;
                    }
                }
                }
            }
        }


    }
    for(int i=0;i<ENEMY_NUM;i++)//检测飞机状态
    {
        if(m_enemys[i].m_Free)
        {
            continue;
        }
        for(int j=0;j<BULLET_NUM;j++)//检测子弹状态
        {
            if(m_hero.m_bullets2[j].m_Free)
            {
                continue;
            }
            if(m_enemys[i].m_Rect.intersects(m_hero.m_bullets2[j].m_Rect))
            {
                if(m_enemys[i].attectedNum<4)
                {
                m_enemys[i].attectedNum++;
                }
                else
                {
                m_enemys[i].attectedNum = 0;
                m_enemys[i].m_Free = true;
                m_hero.m_bullets2[j].m_Free = true;
                QSound::play(SOUND_ENEMYDOWN);
                for(int k=0;k<BOMB_NUM;k++)
                {
                    if(m_bombs[k].m_Free)
                    {
                        m_bombs[k].m_Free=false;
                        m_bombs[k].m_x = m_enemys[i].m_x;
                        m_bombs[k].m_y = m_enemys[i].m_y;
                        break;
                    }
                }
                }
            }
        }


    }

    for(int i=0;i<ENEMY_NUM;i++)//检测飞机状态
    {
        if(m_enemys2[i].m_Free2)
        {
            continue;
        }
        for(int j=0;j<BULLET_NUM;j++)//检测子弹状态
        {
            if(m_hero.m_bullets[j].m_Free)
            {
                continue;
            }
            if(m_enemys2[i].m_Rect2.intersects(m_hero.m_bullets[j].m_Rect))
            {
                m_enemys2[i].m_Free2 = true;
                m_hero.m_bullets[j].m_Free = true;
                QSound::play(SOUND_ENEMYDOWN);
                for(int k=0;k<BOMB_NUM;k++)
                {
                    if(m_bombs[k].m_Free)
                    {
                        m_bombs[k].m_Free=false;
                        m_bombs[k].m_x = m_enemys2[i].m_x2;
                        m_bombs[k].m_y = m_enemys2[i].m_y2;
                        break;
                    }
                }
            }
        }


    }
    for(int i=0;i<ENEMY_NUM;i++)//检测飞机状态
    {
        if(m_enemys2[i].m_Free2)
        {
            continue;
        }
        for(int j=0;j<BULLET_NUM;j++)//检测子弹状态
        {
            if(m_hero.m_bullets2[j].m_Free)
            {
                continue;
            }
            if(m_enemys2[i].m_Rect2.intersects(m_hero.m_bullets2[j].m_Rect))
            {
                m_enemys2[i].m_Free2 = true;
                m_hero.m_bullets2[j].m_Free = true;
                QSound::play(SOUND_ENEMYDOWN);
                for(int k=0;k<BOMB_NUM;k++)
                {
                    if(m_bombs[k].m_Free)
                    {
                        m_bombs[k].m_Free=false;
                        m_bombs[k].m_x = m_enemys2[i].m_x2;
                        m_bombs[k].m_y = m_enemys2[i].m_y2;
                        break;
                    }
                }
            }
        }


    }

}

void PlayScene::downDetection()
{

    for(int i=0;i<ENEMY_NUM;i++)//检测飞机状态
    {
        if(m_enemys[i].m_Free)
        {
            continue;
        }
        if(m_enemys[i].m_Rect.intersects(m_hero.m_Rect))
        {

            QSound::play(SOUND_ENEMYDOWN);
            for(int k=0;k<BOMB_NUM;k++)
            {
                if(m_bombs[k].m_Free)
                {
                    m_bombs[k].m_Free=false;
                    m_bombs[k].m_x = m_hero.m_x;
                    m_bombs[k].m_y = m_hero.m_y;
                    break;
                }
            }
            //暂停游戏
            playpause = false;
            this->BG->stop();

            //显示结束场景
            this->oScene->show();
        }
    }
    for(int i=0;i<ENEMY_NUM;i++)//检测飞机状态
    {
        if(m_enemys2[i].m_Free2)
        {
            continue;
        }
        if(m_enemys2[i].m_Rect2.intersects(m_hero.m_Rect))
        {
            QSound::play(SOUND_ENEMYDOWN);
            for(int k=0;k<BOMB_NUM;k++)
            {
                if(m_bombs[k].m_Free)
                {
                    m_bombs[k].m_Free=false;
                    m_bombs[k].m_x = m_hero.m_x;
                    m_bombs[k].m_y = m_hero.m_y;
                    break;
                }
            }
            //暂停游戏
            playpause = false;
            this->BG->stop();

            //显示结束场景
            this->oScene->show();
        }
    }
}

void PlayScene::overplay()
{
    //监听结束场景退出按钮的信号
    connect(this->oScene,&OverScene::QuitAll,[=](){
        this->close();
    });
}



