#include "MyGame.h"
#include "Scenes/BattleScene.h"
#include "Scenes/PvEBattleScene.h"

#define STARTSCENE // open this to use StartScene

MyGame::MyGame(QWidget *parent) : QMainWindow(parent)
{
#ifdef STARTSCENE
    startScene = new StartScene(this);

    view = new QGraphicsView(this);
    view->setScene(startScene);

    // Set the view's window size to 1280x720
    view->setFixedSize((int) view->scene()->width(), (int) view->scene()->height());
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    setCentralWidget(view);
    // Adjust the QMainWindow size to tightly wrap the QGraphicsView
    setFixedSize(view->sizeHint());

     // Connect the button click to start the battle scene after a delay
    connect(startScene->getPvPStartButton(), &QPushButton::clicked, this, [this]() {
        QTimer::singleShot(2000, this, &MyGame::startPvPBattleScene);
    });
    connect(startScene->getPvEStartButton(), &QPushButton::clicked, this, [this]() {
        QTimer::singleShot(2000, this, &MyGame::startPvEBattleScene);
    });

#else
    startScene = nullptr; // No StartScene in this case
    battleScene = new BattleScene(this);
    battleScene->initBattleScene();

    view = new QGraphicsView(this);
    view->setScene(battleScene);

    view->setFixedSize((int) view->scene()->width(), (int) view->scene()->height());
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    setCentralWidget(view);
    setFixedSize(view->sizeHint());

    battleScene->startLoop();

    connect(static_cast<BattleScene*>(battleScene), &BattleScene::gameOver, this, &MyGame::startGameOverScene);
#endif
}

void MyGame::startPvPBattleScene()
{
    // change to battle scene
    if (battleScene)
    {
        delete battleScene;
    }
    battleScene = new BattleScene(this);
    battleScene->initBattleScene();

    view->setScene(battleScene);
    battleScene->startLoop();

    connect(static_cast<BattleScene*>(battleScene), &BattleScene::gameOver, this, &MyGame::startGameOverScene);// connect game over signal
}

void MyGame::startPvEBattleScene() // AI battle scene
{
    if (battleScene)
    {
        delete battleScene;
    }
    battleScene = new PvEBattleScene(this);
    battleScene->initBattleScene();

    view->setScene(battleScene);
    battleScene->startLoop();

    connect(static_cast<BattleScene*>(battleScene), &BattleScene::gameOver, this, &MyGame::startGameOverScene);// connect game over signal
}

void MyGame::startGameOverScene(const QString& winnerText)
{
    if (gameOverScene)
    {
        delete gameOverScene;
    }
    gameOverScene = new GameOverScene(winnerText, this);

    view->setScene(gameOverScene);

    connect(gameOverScene, &GameOverScene::returnToMainMenu, this, &MyGame::handleReturnToMainMenu);
    connect(gameOverScene, &GameOverScene::exitGame, this, &MyGame::handleExitGame);
}

void MyGame::handleReturnToMainMenu() // back to main menu
{
    if (startScene)
    {
        startScene->resetStartScene();
    }
    else
    {
        startScene = new StartScene(this);
        connect(startScene->getPvPStartButton(), &QPushButton::clicked, this, [this]() {
            QTimer::singleShot(2000, this, &MyGame::startPvPBattleScene);
        });
        connect(startScene->getPvEStartButton(), &QPushButton::clicked, this, [this]() {
            QTimer::singleShot(2000, this, &MyGame::startPvEBattleScene);
        });
    }

    view->setScene(startScene);
}

void MyGame::handleExitGame()
{
    if (startScene)
    {
        delete startScene;
        startScene = nullptr;
    }
    if (battleScene)
    {
        delete battleScene;
        battleScene = nullptr;
    }
    if (gameOverScene)
    {
        delete gameOverScene;
        gameOverScene = nullptr;
    }

    close();  // exit game
}
