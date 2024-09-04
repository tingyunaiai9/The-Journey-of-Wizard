#include "StartScene.h"

StartScene::StartScene(QObject *parent) : QGraphicsScene(parent)
{
    setSceneRect(0, 0, 1280, 720);

    // 创建按钮并设置其文本
    startButton = new QPushButton("Start Game");

    // 将按钮添加到场景中
    QGraphicsProxyWidget *proxy = this->addWidget(startButton);

    // 设置按钮位置
    proxy->setPos(640 - startButton->width() / 2, 360 - startButton->height() / 2);

    // 连接按钮点击信号
    connect(startButton, &QPushButton::clicked, this, &StartScene::startGameClicked);
}
