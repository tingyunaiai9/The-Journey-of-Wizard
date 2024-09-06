#ifndef QT_PROGRAMMING_2024_MYGAME_H
#define QT_PROGRAMMING_2024_MYGAME_H

#include "Scenes/Scene.h"
#include "Scenes/StartScene.h"
#include "Scenes/GameOverScene.h"

#include <QGraphicsView>
#include <QMainWindow>

class MyGame : public QMainWindow
{
Q_OBJECT

public:
    explicit MyGame(QWidget *parent = nullptr);

private slots:
    void startBattleScene(); // start battle scene
    void startGameOverScene(const QString& winnerText); // Start game over scene
    void handleReturnToMainMenu(); // Handle "Return to Main Menu"
    void handleExitGame(); // Handle "Exit Game"

private:
    Scene *battleScene = nullptr; // Battle scene for the game
    StartScene *startScene = nullptr; // Start scene for the game
    GameOverScene *gameOverScene = nullptr; // Game over scene for showing the winner and buttons
    QGraphicsView *view = nullptr; // Graphics view to display scenes
};


#endif //QT_PROGRAMMING_2024_MYGAME_H
