#ifndef GAMEOVERSCENE_H
#define GAMEOVERSCENE_H

#include <QGraphicsScene>
#include <QPushButton>

class GameOverScene : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit GameOverScene(const QString& winnerText, QObject *parent = nullptr);

signals:
    void returnToMainMenu();
    void exitGame();

private:
    void createUI(const QString& winnerText);
};

#endif // GAMEOVERSCENE_H
