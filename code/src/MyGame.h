#ifndef QT_PROGRAMMING_2024_MYGAME_H
#define QT_PROGRAMMING_2024_MYGAME_H

#include "Scenes/Scene.h"
#include "Scenes/StartScene.h"

#include <QGraphicsView>
#include <QMainWindow>

class MyGame : public QMainWindow
{
Q_OBJECT

public:
    explicit MyGame(QWidget *parent = nullptr);

private slots:
    void startBattleScene();  // start battle scene

private:
    Scene *battleScene;
    StartScene *startScene;
    QGraphicsView *view;
};


#endif //QT_PROGRAMMING_2024_MYGAME_H
