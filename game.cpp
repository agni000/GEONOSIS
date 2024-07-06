#include <QGraphicsTextItem>
#include <QTimer>
#include <QImage>
#include <QBrush>
#include <QGraphicsView>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>
#include "game.h"
#include "button.h"
#include "weakenemy.h"
#include <QGraphicsItem>

// extern Game *game;

Game::Game(QWidget *parent) {
    //cria cenario
    // game->setRenderHint(QPainter::Antialiasing);
    scene = new QGraphicsScene();

    //define o tamanho do cenario
    scene->setSceneRect(0, 0, 800, 600);
    scene->setBackgroundBrush(QBrush(QImage(":/images/png/backg.jpg")));

    //visualizar o objeto scene
    setScene(scene);

    //desabilitar scroll
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //fixar o tamanho da janela
    setFixedSize(800,600);

    warrior = new Sprite();
    warrior->setPos(200, 410);
    warrior->setFlag(QGraphicsItem::ItemIsFocusable);
    warrior->setFocus();
    warrior->setScale(1.1);

    //adiciona o player no cenario
    // scene->addItem(player);
    scene->addItem(warrior);

    // criar inimigos
    timer = new QTimer();
    timer->start(2000);
    connect(timer, &QTimer::timeout, this, &Game::spawn);

    // adicionar contagem de pontos e vida do jogador
    score = new Score();
    health = new Health();
    health->setPos(400, 25);
    health->setScale(1.5);
    scene->addItem(health);

    show();
}

void Game::displayMainMenu() {
    //titulo
    QGraphicsTextItem *titleText = new QGraphicsTextItem(QString("Trabalho Final"));
    QFont titleFont("Calibri", 50);
    titleText->setFont(titleFont);
    int txPos = this->width()/2 - titleText->boundingRect().width()/2;
    int tyPos = 150;
    titleText->setPos(txPos, tyPos);
    scene->addItem(titleText);

    Button *playButton = new Button(QString("Play"));
    int bxPos = this->width()/2 - titleText->boundingRect().width()/2;
    int byPos = 275;
    playButton->setPos(bxPos, byPos);
    connect(playButton, SIGNAL(clicked()), this, SLOT(start()));
    scene->addItem(playButton);

    Button *quitButton = new Button(QString("Quit"));
    int qxPos = this->width()/2 - titleText->boundingRect().width()/2;
    int qyPos = 350;
    playButton->setPos(qxPos, qyPos);
    connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));
    scene->addItem(quitButton);

}

void Game::spawn() {
    // cria inimigo
    Enemy *enemy = new Enemy();
    WeakEnemy *enemy2 = new WeakEnemy();
    scene->addItem(enemy);
    scene->addItem(enemy2);
}

void Game::Game_Over() {
    timer->stop();
    scene->addItem(score);
    // scene->addItem(gameover);
    warrior->setPos(400, 300);
    warrior->setScale(1.5);
}
