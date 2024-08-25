#include <QApplication>
#include "MyGame.h"

int main(int argc, char *argv[]) {
    // ensure the application’s adaptability and visual consistency across different resolution displays
    QGuiApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::Floor);

    QApplication a(argc, argv);
    MyGame myGame;
    myGame.show();
    return QApplication::exec();
}
