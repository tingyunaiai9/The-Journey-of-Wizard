#include <QDateTime>
#include "Scene.h"

Scene::Scene(QObject *parent) :
    QGraphicsScene(parent), timer(new QTimer(this))
{
    connect(timer, &QTimer::timeout, this, &Scene::update);
}

void Scene::update()
{
    auto currentTime = QDateTime::currentDateTime().toMSecsSinceEpoch();
    if (lastTime == -1) // first frame
    {
        deltaTime = 0;
    }
    else
    {
        deltaTime = currentTime - lastTime;
        // qDebug() << "deltaTime: " << deltaTime;
    }
    lastTime = currentTime;
}

void Scene::startLoop()
{
    timer->start(1000 / 90); // 90FPS
}
