#include "MyGame.h"

#include <QApplication>
#include <QTime>


int main(int argc, char *argv[]) {
    // ensure the application’s adaptability and visual consistency across different resolution displays
    QGuiApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::Floor);

    QApplication a(argc, argv);
    // 设置随机数种子
    srand(static_cast<uint>(QTime::currentTime().msec()));

    MyGame myGame;
    myGame.show();
    return QApplication::exec();
}
