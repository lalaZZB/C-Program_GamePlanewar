#ifndef CHOOSELEVELSCENE_H
#define CHOOSELEVELSCENE_H

#include <QMainWindow>
#include "playscene.h"

namespace Ui {
class ChooseLevelScene;
}

class ChooseLevelScene : public QMainWindow
{
    Q_OBJECT

public:
    explicit ChooseLevelScene(QWidget *parent = nullptr);
    ~ChooseLevelScene();

    //绘图事件
    void paintEvent(QPaintEvent *);

    //维护第三个场景的指针
    PlayScene * pScene;

signals:
    //点击返回按钮触发的自定义信号
    void ChooseSceneBack();


private:
    Ui::ChooseLevelScene *ui;
};

#endif // CHOOSELEVELSCENE_H
