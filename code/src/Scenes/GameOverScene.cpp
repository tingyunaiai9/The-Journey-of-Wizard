#include "GameOverScene.h"
#include <QGraphicsTextItem>
#include <QFont>
#include <QColor>

GameOverScene::GameOverScene(const QString& winnerText, QObject *parent)
    : QGraphicsScene(parent)
{
    createUI(winnerText);
}

void GameOverScene::createUI(const QString& winnerText)
{
    // 设置场景大小
    setSceneRect(0, 0, 1280, 720);

    // 胜利者文本
    QGraphicsTextItem* victoryText = new QGraphicsTextItem(winnerText);
    QFont font;
    font.setPointSize(32);  // 设置字体大小
    font.setBold(true);     // 设置粗体
    victoryText->setFont(font);
    victoryText->setDefaultTextColor(QColor("#72a5a2"));  // 设置文本颜色
    victoryText->setPos(400, 200);  // 设置文本的位置
    addItem(victoryText);

    // 返回主菜单按钮
    QPushButton* returnButton = new QPushButton("返回主菜单");
    returnButton->setGeometry(500, 350, 200, 50);
    connect(returnButton, &QPushButton::clicked, this, &GameOverScene::returnToMainMenu);
    addWidget(returnButton);

    // 退出游戏按钮
    QPushButton* exitButton = new QPushButton("退出游戏");
    exitButton->setGeometry(500, 450, 200, 50);
    connect(exitButton, &QPushButton::clicked, this, &GameOverScene::exitGame);
    addWidget(exitButton);
}
