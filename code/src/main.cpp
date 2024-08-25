#include <QApplication>
#include "MyGame.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MyGame myGame;
    myGame.show();
    return QApplication::exec();
}
