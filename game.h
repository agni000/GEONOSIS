#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>
#include "button.h"
#include "gameover.h"
#include "score.h"
#include "health.h"
#include "sprite.h"
#include <QGraphicsItem>
#include <QtMultimedia/QtMultimedia>

class Game : public QGraphicsView {
    Q_OBJECT
public:
    //construtor
    Game(QWidget *parent = nullptr);
    ~Game();

    //atributos
    QGraphicsScene *scene;
    Score *score;
    Health *health;
    Sprite *ship;
    QTimer *timer;
    GameOver *picture;
    Button *restartBtn;
    Button *closeBtn;
    Button *playButton;
    Button *quitButton;
    QMediaPlayer *music;
    QAudioOutput *audioOutput;

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
