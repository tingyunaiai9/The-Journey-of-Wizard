#include <QDateTime>
#include "Scene.h"

Scene::Scene(QObject *parent) : QGraphicsScene(parent), timer(new QTimer(this)) {
    connect(timer, &QTimer::timeout, this, &Scene::update);
}

void Scene::update() {
    auto currentTime = QDateTime::currentDateTime().toMSecsSinceEpoch();
    if (lastTime == -1) { // first frame
        deltaTime = 0;
    } else {
        deltaTime = currentTime - lastTime;
    }
    lastTime = currentTime;

    processInput();
    processMovement();
    processPicking();

    // add for hero handle fps by self
    process_fps(deltaTime);
}

void Scene::startLoop() {
    timer->start(1000 / 90); // 90FPS
}

void Scene::processInput() {

}

void Scene::processMovement() {

}

void Scene::processPicking() {

}

void Scene::processAttacking() {

}

void Scene::process_fps(qint64 deltaTime) {

}
