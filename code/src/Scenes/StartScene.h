#ifndef QT_PROGRAMMING_2024_STARTSCENE_H
#define QT_PROGRAMMING_2024_STARTSCENE_H

#include <QGraphicsScene>
#include <QPushButton>
#include <QGraphicsProxyWidget>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QStringList>

class StartScene : public QGraphicsScene
{
    Q_OBJECT

private:
    QPushButton *startButton;  // the start button
    QGraphicsPixmapItem *currentPixmapItem;
    QTimer *imageTimer;  // timer for image transition
    QTimer *fadeTimer;  // timer for image fade in
    QStringList imagePaths;  // image paths
    int currentImageIndex;
    qreal opacity;  // image opacity

    QList<QGraphicsPixmapItem*> lastFourPixmapItems;  // store the last three images

public:
    explicit StartScene(QObject *parent = nullptr);

signals:
    void startGameClicked();  // button click signal
    void imagesFadedOut();  // signal when images fade out is completed

private slots:
    void startImageTransition(); // switch to the next image (fade in)
    void updateImageOpacity(); // update the image opacity (fade in)
    void fadeInButton();  // show the start button

    //slots for fade-out functionality
    void fadeOutLastThreeImages();  // start fading out the last three images
    void updateFadeOutOpacity();  // update the opacity for fading out images
};

#endif //QT_PROGRAMMING_2024_STARTSCENE_H
