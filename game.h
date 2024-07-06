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
    Sprite *warrior;
    QTimer *timer;

    //metodos
    void displayMainMenu();

public slots:
    // void start();
    void spawn();
    void Game_Over();
};

#endif // GAME_H
