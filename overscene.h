#ifndef OVERSCENE_H
#define OVERSCENE_H

#include <QWidget>

namespace Ui {
class OverScene;
}

class OverScene : public QWidget
{
    Q_OBJECT

public:
    explicit OverScene(QWidget *parent = nullptr);
    ~OverScene();
signals:
    //点击退出按钮触发的自定义信号
    void QuitAll();
private:
    Ui::OverScene *ui;
};

#endif // OVERSCENE_H
