#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>
#include "score.h"
#include "health.h"
#include "sprite.h"
#include <QGraphicsItem>

class Game : public QGraphicsView {
    Q_OBJECT
public:
    //construtor
    Game(QWidget *parent = nullptr);

    //atributos
    QGraphicsScene *scene;
    Score *score;
    Health *health;
    Sprite *ship;
    QTimer *timer;
    QPixmap *gameOverPic;

    //metodos
    void drawPanel(int x, int y, int width, int height, QColor color, double opacity);
    void displayMainMenu();
    void displayGameOverWindow();

public slots:
    void start();
    void spawn();
    void Game_Over();
};

#endif // GAME_H
