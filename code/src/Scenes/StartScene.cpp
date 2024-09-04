#include "StartScene.h"
#include <QTimer>
#include <QPixmap>
#include <QGraphicsPixmapItem>

StartScene::StartScene(QObject *parent) : QGraphicsScene(parent), currentImageIndex(0)
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

    // 尝试加载第一张图片
    QPixmap pixmap(imagePaths[currentImageIndex]);
    if (pixmap.isNull()) {
        qWarning() << "Failed to load image:" << imagePaths[currentImageIndex];
    }

    // 显示第一张图片
    pixmapItem = new QGraphicsPixmapItem(pixmap);
    addItem(pixmapItem);
    pixmapItem->setPos(0, 0);  // 设置图片位置

    // 定时切换图片
    imageTimer = new QTimer(this);
    connect(imageTimer, &QTimer::timeout, this, &StartScene::showNextImage);
    imageTimer->start(500);

    // 创建按钮并设置其文本
    startButton = new QPushButton("Start Game");
    startButton->setVisible(false);  // 初始隐藏按钮

    // 将按钮添加到场景中
    QGraphicsProxyWidget *proxy = this->addWidget(startButton);
    proxy->setPos(640 - startButton->width() / 2, 360 - startButton->height() / 2);

    // 连接按钮点击信号
    connect(startButton, &QPushButton::clicked, this, &StartScene::startGameClicked);
}

void StartScene::showNextImage()
{
    // 切换到下一张图片
    currentImageIndex++;
    if (currentImageIndex < imagePaths.size()) {
        QPixmap pixmap(imagePaths[currentImageIndex]);
        if (pixmap.isNull()) {
            qWarning() << "Failed to load image:" << imagePaths[currentImageIndex];
            return;
        }

        pixmapItem->setPixmap(pixmap);
    } else {
        // 如果所有图片播放完毕，显示按钮并停止定时器
        imageTimer->stop();
        startButton->setVisible(true);  // 显示按钮
    }
}
