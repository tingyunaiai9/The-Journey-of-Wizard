#ifndef QT_PROGRAMMING_2024_GAMEOVERSCENE_H
#define QT_PROGRAMMING_2024_GAMEOVERSCENE_H

#include <QGraphicsScene>
#include <QPushButton>
#include <QPixmap>
#include <QGraphicsPixmapItem>

class GameOverScene : public QGraphicsScene
{
    Q_OBJECT

private:
    QPushButton* returnButton = nullptr;
    QPushButton* exitButton = nullptr;

    QPixmap* m_pixmap = nullptr;
    QGraphicsPixmapItem* m_pixmapItem = nullptr;

public:
    explicit GameOverScene(const QString& winnerText, QObject *parent = nullptr);

signals:
    void returnToMainMenu();
    void exitGame();

private:
    void createUI(const QString& winnerText);
};

#endif // QT_PROGRAMMING_2024_GAMEOVERSCENE_H
