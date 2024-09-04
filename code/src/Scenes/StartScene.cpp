#include "StartScene.h"
#include <QTimer>
#include <QPixmap>
#include <QGraphicsPixmapItem>

StartScene::StartScene(QObject *parent) : QGraphicsScene(parent), currentImageIndex(0), opacity(0.0)
{
    setSceneRect(0, 0, 1280, 720);

    // 创建图片序列
    imagePaths << ":/Scenes/StartScene/background_1.png"  // 替换为实际的图片路径
               << ":/Scenes/StartScene/background_2.png"
               << ":/Scenes/StartScene/background_3.png"
               << ":/Scenes/StartScene/background_4.png"
               << ":/Scenes/StartScene/background_5.png"
               << ":/Scenes/StartScene/background_6.png"
               << ":/Scenes/StartScene/background_7.png"
               << ":/Scenes/StartScene/background_8.png";

    // 立即显示第一张图片（不淡入）
    QPixmap firstPixmap(imagePaths[currentImageIndex]);
    if (!firstPixmap.isNull()) {
        currentPixmapItem = new QGraphicsPixmapItem(firstPixmap);
        addItem(currentPixmapItem);
        currentPixmapItem->setPos(0, 0);
        currentPixmapItem->setOpacity(1.0);  // 第一张图片直接显示
        currentPixmapItem->setZValue(0);
    }

    // 定时器控制图片淡入
    fadeTimer = new QTimer(this);
    connect(fadeTimer, &QTimer::timeout, this, &StartScene::updateImageOpacity);

    // 调整为更快的图片切换间隔，例如每1.1秒切换一张图片
    imageTimer = new QTimer(this);
    connect(imageTimer, &QTimer::timeout, this, &StartScene::startImageTransition);
    imageTimer->start(800);  // 从第二张图片开始的切换时间

    // 创建按钮并设置其文本
    startButton = new QPushButton("Start Game");
    startButton->setVisible(false);  // 初始隐藏按钮

    // 将按钮添加到场景中，并将其 Z 值设置为 1，确保按钮在图片上方
    QGraphicsProxyWidget *proxy = this->addWidget(startButton);
    proxy->setPos(640 - startButton->width() / 2, 360 - startButton->height() / 2);
    proxy->setZValue(1);  // 设置按钮的 Z 值为 1

    // 连接按钮点击信号
    connect(startButton, &QPushButton::clicked, this, &StartScene::startGameClicked);
}

void StartScene::startImageTransition()
{
    // 当加载新的图片时，首先停止任何进行中的淡入效果
    fadeTimer->stop();
    opacity = 0.0;  // 重置淡入透明度

    // 检查是否有更多图片
    if (currentImageIndex < imagePaths.size() - 1) {
        currentImageIndex++;  // 切换到下一张图片
        QPixmap nextPixmap(imagePaths[currentImageIndex]);
        if (nextPixmap.isNull()) {
            qWarning() << "Failed to load image:" << imagePaths[currentImageIndex];
            return;
        }

        // 创建一个新的 QGraphicsPixmapItem 并将其添加到场景中
        currentPixmapItem = new QGraphicsPixmapItem(nextPixmap);
        addItem(currentPixmapItem);
        currentPixmapItem->setPos(0, 0);
        currentPixmapItem->setZValue(0);

        // 从第二张图片开始淡入
        currentPixmapItem->setOpacity(opacity);  // 设置初始透明度为 0
        fadeTimer->start(35);  // 每 50 毫秒更新一次透明度
    } else {
        // 如果所有图片播放完毕，立即显示按钮并停止定时器
        imageTimer->stop();
        fadeInButton();  // 显示按钮
    }
}

void StartScene::updateImageOpacity()
{
    if (opacity < 1.0) {
        opacity += 0.05;  // 每次增加透明度
        currentPixmapItem->setOpacity(opacity);  // 调整图片的透明度
    } else {
        // 达到完全不透明时停止淡入
        fadeTimer->stop();
    }
}

void StartScene::fadeInButton()
{
    startButton->setVisible(true);  // 立即显示按钮
}
