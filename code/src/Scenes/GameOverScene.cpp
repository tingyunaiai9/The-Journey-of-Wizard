#include "GameOverScene.h"

#include <QGraphicsProxyWidget>


GameOverScene::GameOverScene(const QString& winnerText, QObject *parent)
    : QGraphicsScene(parent)
{
    createUI(winnerText);
}

void GameOverScene::createUI(const QString& winnerText)
{
    setSceneRect(0, 0, 1280, 720);

    // picture
    if (winnerText == "Player 1 Wins!")
    {
        m_pixmap = new QPixmap(":/Scenes/GameOverScene/gameover_player1_win.png");
    }
    else if (winnerText == "Player 2 Wins!")
    {
        m_pixmap = new QPixmap(":/Scenes/GameOverScene/gameover_player2_win.png");
    }
    else
    {
        m_pixmap = new QPixmap(":/Scenes/GameOverScene/gameover.png");
    }

    *m_pixmap = m_pixmap->scaled(sceneRect().size().toSize(), Qt::KeepAspectRatio);
    m_pixmapItem = new QGraphicsPixmapItem(*m_pixmap);
    addItem(m_pixmapItem);

    // button
    returnButton = new QPushButton("Main Menu");
    returnButton->setFixedSize(200, 50);
    returnButton->setStyleSheet("QPushButton {"
                                "background-color: rgba(255, 255, 255, 10);"
                                "border: 2px solid rgba(114, 165, 162, 100);"
                                "border-radius: 10px;"
                                "color: #72a5a2;"
                                "font-size: 30px;"
                                "}");
    QGraphicsProxyWidget *returnButtonProxy = this->addWidget(returnButton);
    returnButtonProxy->setPos(640 - returnButton->width() / 2, 360 - returnButton->height() / 2 + 50);
    returnButtonProxy->setZValue(1);
    connect(returnButton, &QPushButton::clicked, this, &GameOverScene::returnToMainMenu);

    exitButton = new QPushButton("Exit Game");
    exitButton->setFixedSize(200, 50);
    exitButton->setStyleSheet("QPushButton {"
                              "background-color: rgba(255, 255, 255, 10);"
                              "border: 2px solid rgba(114, 165, 162, 100);"
                              "border-radius: 10px;"
                              "color: #72a5a2;"
                              "font-size: 30px;"
                              "}");
    QGraphicsProxyWidget *exitButtonProxy = this->addWidget(exitButton);
    exitButtonProxy->setPos(640 - exitButton->width() / 2, 360 - exitButton->height() / 2 + 150);
    exitButtonProxy->setZValue(1);
    connect(exitButton, &QPushButton::clicked, this, &GameOverScene::exitGame);
}
