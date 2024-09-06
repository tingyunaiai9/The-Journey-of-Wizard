#include "StartScene.h"
#include <QTimer>
#include <QPixmap>
#include <QGraphicsPixmapItem>

StartScene::StartScene(QObject *parent) : QGraphicsScene(parent), currentImageIndex(0), opacity(0.0)
{
    setSceneRect(0, 0, 1280, 720); // important

    imagePaths << ":/Scenes/StartScene/background_1.png"
               << ":/Scenes/StartScene/background_2.png"
               << ":/Scenes/StartScene/background_3.png"
               << ":/Scenes/StartScene/background_4.png"
               << ":/Scenes/StartScene/background_5.png"
               << ":/Scenes/StartScene/background_6.png"
               << ":/Scenes/StartScene/background_7.png"
               << ":/Scenes/StartScene/background_8.png"
               << ":/Scenes/StartScene/title.png";

    // show the first image directly
    QPixmap firstPixmap(imagePaths[currentImageIndex]);
    if (!firstPixmap.isNull())
    {
        // modify the image size
        firstPixmap = firstPixmap.scaled(sceneRect().size().toSize(), Qt::KeepAspectRatio);

        currentPixmapItem = new QGraphicsPixmapItem(firstPixmap);
        addItem(currentPixmapItem);
        allPixmapItems.append(currentPixmapItem);  // Add to array for future reference

        // set the image in the center of the scene
        currentPixmapItem->setPos((sceneRect().width() - currentPixmapItem->pixmap().width()) / 2,
                              (sceneRect().height() - currentPixmapItem->pixmap().height()) / 2);
        currentPixmapItem->setOpacity(1.0);
        currentPixmapItem->setZValue(0);
    }

    // set up the timer for image transition
    fadeTimer = new QTimer(this);
    connect(fadeTimer, &QTimer::timeout, this, &StartScene::updateImageOpacity);

    imageTimer = new QTimer(this);
    connect(imageTimer, &QTimer::timeout, this, &StartScene::startImageTransition);
    imageTimer->start(800);  // every 800 milliseconds switch to the next image

    // button
    startButton = new QPushButton("Start Game");
    startButton->setFixedSize(200, 50);
    startButton->setStyleSheet("QPushButton {"
                            "background-color: rgba(255, 255, 255, 10);"  // alpha: opacity 0-255
                            "border: 2px solid rgba(114, 165, 162, 100);"
                            "border-radius: 10px;"
                            "color: #72a5a2;"
                            "font-size: 30px;"
                            "}");
    startButton->setVisible(false);  // hide the button

    QGraphicsProxyWidget *proxy = this->addWidget(startButton);
    proxy->setPos(640 - startButton->width() / 2, 360 - startButton->height() / 2 + 100);
    proxy->setZValue(1);  // set z above the image

    connect(startButton, &QPushButton::clicked, this, &StartScene::fadeOutLastFourImages);
    connect(startButton, &QPushButton::clicked, this, &StartScene::fadeOutButton);
}

void StartScene::startImageTransition()
{
    // stop the fade timer if it is running
    fadeTimer->stop();
    opacity = 0.0;  // reset the opacity

    if (currentImageIndex < imagePaths.size() - 1)
    {
        currentImageIndex++;  // change to the next image
        QPixmap nextPixmap(imagePaths[currentImageIndex]);
        if (nextPixmap.isNull())
        {
            qWarning() << "Failed to load image:" << imagePaths[currentImageIndex];
            return;
        }

        // modify the image size
        nextPixmap = nextPixmap.scaled(sceneRect().size().toSize(), Qt::KeepAspectRatio);

        currentPixmapItem = new QGraphicsPixmapItem(nextPixmap);
        addItem(currentPixmapItem);
        allPixmapItems.append(currentPixmapItem);  // Add to array for future reference
        // set the image in the center of the scene
        currentPixmapItem->setPos((sceneRect().width() - currentPixmapItem->pixmap().width()) / 2,
                                  (sceneRect().height() - currentPixmapItem->pixmap().height()) / 2);
        currentPixmapItem->setZValue(0);

        currentPixmapItem->setOpacity(opacity);  // set the opacity to 0
        fadeTimer->start(35);  // start the fade in timer
    }
    else
    {
        // stop the image timer if all images have been shown
        if (imageTimer)
        {
            imageTimer->stop();
            delete imageTimer;
            imageTimer = nullptr;
        }
        if (fadeTimer)
        {
            fadeTimer->stop();
            delete fadeTimer;
            fadeTimer = nullptr;
        }

        fadeInButton();  // show the start button
    }
}

void StartScene::updateImageOpacity()
{
    if (opacity < 1.0)
    {
        opacity += 0.05;
        currentPixmapItem->setOpacity(opacity);
    }
    else
    {
        fadeTimer->stop();
    }
}

// show button
void StartScene::fadeInButton()
{
    startButton->setVisible(true);
}

void StartScene::fadeOutButton()
{
    startButton->setVisible(false);
}

void StartScene::fadeOutLastFourImages()
{
    if (currentImageIndex >= 5)
    {
        // Get the current image based on the index
        currentPixmapItem = allPixmapItems[currentImageIndex];
        opacity = 1.0;

        // Create or reuse the fade timer to control opacity
        if (!fadeTimer)
        {
            fadeTimer = new QTimer(this);
            connect(fadeTimer, &QTimer::timeout, this, &StartScene::updateFadeOutOpacity);
        }
        fadeTimer->start(35);  // Start the fade out process
    }
    else
    {
        if (fadeTimer)
        {
            fadeTimer->stop();
            delete fadeTimer;
            fadeTimer = nullptr;
        }
        // Emit signal when all images have faded out
        emit imagesFadedOut();
    }
}

void StartScene::updateFadeOutOpacity()
{
    if (opacity > 0.0)
    {
        // Decrease opacity gradually
        opacity -= 0.1;
        currentPixmapItem->setOpacity(opacity);
    }
    else
    {
        fadeTimer->stop();
        // Set opacity to 0, effectively hiding the image
        currentPixmapItem->setOpacity(0.0);

        // Move to the next image in reverse order
        currentImageIndex--;

        // Continue fading out the next image in reverse order
        fadeOutLastFourImages();
    }
}

void StartScene::resetStartScene()
{
    if (imageTimer)
    {
        imageTimer->stop();
        delete imageTimer;
        imageTimer = nullptr;
    }
    if (fadeTimer)
    {
        fadeTimer->stop();
        delete fadeTimer;
        fadeTimer = nullptr;
    }

    for(auto item : allPixmapItems)
    {
        item->setOpacity(1.0);
    }
    currentImageIndex = allPixmapItems.size() - 1;

    if (startButton)
    {
        startButton->setVisible(true);
    }
}
