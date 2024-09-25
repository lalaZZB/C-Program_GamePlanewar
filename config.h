#ifndef CONFIG_H
#define CONFIG_H

//游戏配置数据
#define GAME_WIGHT 480
#define GAME_HEIGHT 852
#define GAME_TITLE "飞机大战 v10.0"
#define GAME_RES_PATH "./plane.rcc"
#define MAP_PATH ":/res/background.png"
#define MAP_SCROLL_SPEED 10//滚动速度
#define GAME_RATE 10//刷新率
#define HERO_PATH ":/res/hero1.png"
#define BULLET_PATH ":/res/bullet1.png"
#define BULLET_SPEED 10//子弹速度
#define BULLET_NUM 50//子弹数量
#define BULLET_INTERVAL 10//子弹间隔
#define ENEMY_PATH ":/res/enemy1.png"
#define ENEMY_PATH2 ":/res/enemy0.png"
#define ENEMY_SPEED 7//敌机速度
#define ENEMY_SPEED2 10//敌机速度
#define ENEMY_NUM 70//敌机数量
#define ENEMY_INITERVAL 20//敌机出场间隔
#define ENEMY_INITERVAL2 40//敌机出场间隔
#define BOMB_PATH ":/res/enemy1_down%1.png"
#define BOMB_NUM 30//爆炸数量
#define BOMB_MAX 4//爆炸资源数量
#define BOMB_INTERVAL 10//最短爆炸间隔
#define SOUND_BACKGROUNG ":/res/game_music.wav"//背景音效
#define SOUND_BULLET ":/res/bullet.wav"//子弹音效
#define SOUND_ENEMYDOWN ":/res/enemy2_down.wav"//敌机爆炸音效

#endif // CONFIG_H
