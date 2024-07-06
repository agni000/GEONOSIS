#include <QApplication>
#include "game.h"

Game *game; //variavel global

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    game = new Game();
    game->show();
    game->displayMainMenu();
    return a.exec();
}
