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
    void showNextImage();  // 切换到下一张图片

private:
    QPushButton *startButton;  // 开始游戏按钮
    QGraphicsPixmapItem *pixmapItem;  // 用于显示图片的图元项
    QTimer *imageTimer;  // 定时器用于切换图片
    QStringList imagePaths;  // 存储图片文件路径列表
    int currentImageIndex;  // 当前显示的图片索引
};

#endif // STARTSCENE_H
