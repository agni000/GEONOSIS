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

    gameOverPic = new QPixmap(":/images/png/endd.png");
}

void Game::displayMainMenu() {
    //titulo
    QGraphicsTextItem *titleText = new QGraphicsTextItem(QString("Trabalho Final"));
    QFont titleFont("Calibri", 50);
    titleText->setFont(titleFont);
    titleText->setDefaultTextColor(Qt::darkCyan);
    int txPos = this->width()/2 - titleText->boundingRect().width()/2;
    int tyPos = 150;
    titleText->setPos(txPos, tyPos);
    scene->addItem(titleText);

    Button *playButton = new Button(QString("Jogar"));
    int bxPos = this->width()/2 - playButton->boundingRect().width()/2;
    int byPos = 275;
    playButton->setPos(bxPos, byPos);
    connect(playButton, SIGNAL(clicked()), this, SLOT(start()));
    scene->addItem(playButton);

    Button *quitButton = new Button(QString("Sair"));
    int qxPos = this->width()/2 - quitButton->boundingRect().width()/2;
    int qyPos = 350;
    quitButton->setPos(qxPos, qyPos);
    connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));
    scene->addItem(quitButton);
}

void Game::start() {
    scene->clear();

    ship = new Sprite();
    ship->setPos(200, 410);
    ship->setFlag(QGraphicsItem::ItemIsFocusable);
    ship->setFocus();
    ship->setScale(1.1);

    //adiciona o player no cenario
    // scene->addItem(player);
    scene->addItem(ship);

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

void Game::spawn() {
    // cria inimigo
    Enemy *enemy = new Enemy();
    WeakEnemy *enemy2 = new WeakEnemy();
    scene->addItem(enemy);
    scene->addItem(enemy2);
}

void Game::Game_Over() {
    timer->stop();
    for(size_t i = 0, n = scene->items().size(); i < n; i++) {
        scene->items().at(i)->setEnabled(false);
    }
    ship->setScale(1.5);

    displayGameOverWindow();
}

void Game::displayGameOverWindow() {
    //painel escurecido sobre o jogo
    drawPanel(0, 0, 800, 600, Qt::black, 0.25);

    //painel de fim de jogo
    drawPanel(200, 200, 400, 350, Qt::lightGray, 0.75);

    Button *restartBtn = new Button("Jogar novamente");
    restartBtn->setPos(300, 350);
    scene->addItem(restartBtn);
    connect(restartBtn, SIGNAL(clicked()), this, SLOT(start()));

    Button *closeBtn = new Button("Fechar jogo");
    closeBtn->setPos(300, 400);
    scene->addItem(closeBtn);
    connect(closeBtn, SIGNAL(clicked()), this, SLOT(close()));

    scene->addItem(score);
    score->setPos(330, 250);
}

void Game::drawPanel(int x, int y, int width, int height, QColor color, double opacity) {
    QGraphicsRectItem *panel = new QGraphicsRectItem(x, y, width, height);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(color);
    panel->setBrush(brush);
    panel->setOpacity(opacity);
    scene->addItem(panel);
    scene->addPixmap(*gameOverPic);
}
