#ifndef QT_PROGRAMMING_2024_STARTSCENE_H
#define QT_PROGRAMMING_2024_STARTSCENE_H

#include <QGraphicsScene>
#include <QPushButton>
#include <QGraphicsProxyWidget>

class StartScene : public QGraphicsScene
{
Q_OBJECT

public:
    explicit StartScene(QObject *parent = nullptr);

signals:
    void startGameClicked();

private:
    QPushButton *startButton;
};

#endif //QT_PROGRAMMING_2024_STARTSCENE_H
