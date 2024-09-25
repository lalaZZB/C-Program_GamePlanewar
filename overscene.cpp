#include "overscene.h"
#include "ui_overscene.h"
#include <QPushButton>
#include "playscene.h"

OverScene::OverScene(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OverScene)
{
    ui->setupUi(this);

    //设置固定尺寸
    this->setFixedSize(400,400);
    //设置标题
    this->setWindowTitle("结束场景");
    //设置图标
    this->setWindowIcon(QIcon(":/res/icon72x72.png"));

    //设置分数
    this->ui->score->setNum(177);

    //退出按钮的设置
    connect(ui->quit,&QPushButton::clicked,[=](){
        emit this->QuitAll();
        this->close();
    });


}

OverScene::~OverScene()
{
    delete ui;
}
