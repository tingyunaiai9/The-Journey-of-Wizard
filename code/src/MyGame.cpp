#include "MyGame.h"
#include "Scenes/BattleScene.h"

MyGame::MyGame(QWidget *parent) : QMainWindow(parent)
{
    startScene = new StartScene(this);
    battleScene = nullptr; // important!!!

    view = new QGraphicsView(this);
    view->setScene(startScene);

    // Set the view's window size to 1280x720
    view->setFixedSize((int) view->scene()->width(), (int) view->scene()->height());
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    setCentralWidget(view);
    // Adjust the QMainWindow size to tightly wrap the QGraphicsView
    setFixedSize(view->sizeHint());

    connect(startScene, &StartScene::startGameClicked, this, &MyGame::startBattleScene);
}

void MyGame::startBattleScene()
{
    // change to battle scene
    if (battleScene)
    {
        delete battleScene;
    }
    battleScene = new BattleScene(this);

    view->setScene(battleScene);
    battleScene->startLoop();
}
