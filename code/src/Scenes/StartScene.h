#ifndef STARTSCENE_H
#define STARTSCENE_H

#include <QGraphicsScene>
#include <QPushButton>
#include <QGraphicsProxyWidget>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QStringList>

class StartScene : public QGraphicsScene {
    Q_OBJECT

public:
    explicit StartScene(QObject *parent = nullptr);

signals:
    void startGameClicked();

private slots:
    void startImageTransition();  // 开始图片过渡
    void updateImageOpacity();  // 更新图片的透明度，处理淡入淡出
    void fadeInButton();  // 按钮淡入显示

private:
    QPushButton *startButton;  // 开始游戏按钮
    QGraphicsPixmapItem *currentPixmapItem;  // 当前图片
    QGraphicsPixmapItem *nextPixmapItem;  // 下一张图片
    QTimer *imageTimer;  // 定时器用于切换图片
    QTimer *fadeTimer;  // 定时器用于图片淡入效果
    QStringList imagePaths;  // 存储图片文件路径列表
    int currentImageIndex;  // 当前显示的图片索引
    qreal opacity;  // 控制图片透明度
};

#endif // STARTSCENE_H
