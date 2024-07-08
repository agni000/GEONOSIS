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
#include <QPushButton>

// extern Game *game;

Game::Game(QWidget *parent) {
    //cria cenario
    scene = new QGraphicsScene();
    music = new QMediaPlayer(this);
    audioOutput = new QAudioOutput(this);
    music->setSource(QUrl("qrc:/music/nu11 - Running Out of Time.ogg"));
    music->setAudioOutput(audioOutput);
    audioOutput->setVolume(0.1);
    music->play();

    highScore = 0;
    score = NULL;
    health = NULL;
    picture = NULL;
    timer = NULL;
    ship = NULL;
    playButton = NULL;
    quitButton = NULL;
    restartBtn = NULL;
    closeBtn = NULL;

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
}

Game::~Game() {
    delete scene;
    delete score;
    delete health;
    delete ship;
    delete timer;
    delete picture;
    delete playButton;
    delete quitButton;
    delete restartBtn;
    delete closeBtn;
    delete music;
    delete audioOutput;
}

void Game::displayMainMenu() {
    //titulo
    QGraphicsTextItem *titleText = scene->addText(QString("GEONOSIS"));
    QFont titleFont("Calibri", 50);
    titleText->setFont(titleFont);
    titleText->setDefaultTextColor(Qt::darkCyan);
    int txPos = this->width()/2 - titleText->boundingRect().width()/2;
    int tyPos = 150;
    titleText->setPos(txPos, tyPos);

    playButton = new Button(QString("Play game"), this);
    int bxPos = this->width()/2 - playButton->boundingRect().width()/2;
    int byPos = 275;
    playButton->setPos(bxPos, byPos);
    connect(playButton, SIGNAL(clicked()), this, SLOT(start()));
    scene->addItem(playButton);

    quitButton = new Button(QString("Quit"), this);
    int qxPos = this->width()/2 - quitButton->boundingRect().width()/2;
    int qyPos = 350;
    quitButton->setPos(qxPos, qyPos);
    connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));
    scene->addItem(quitButton);
}

void Game::start() {
    if (score) {
        delete score;
    }

    if (picture) {
        delete picture;
    }

    if (!music->isPlaying()) {
        music->play();
    }

    //o restante sofre delete pelo clear
    scene->clear();

    ship = new Sprite();
    ship->setPos(200, 410);
    ship->setFlag(QGraphicsItem::ItemIsFocusable);
    ship->setFocus();
    ship->setScale(1.1);

    //adiciona a nave no cenario
    scene->addItem(ship);

    // spawn de inimigos
    timer = new QTimer(this);
    timer->start(2000);
    connect(timer, &QTimer::timeout, this, &Game::spawn);

    // score e vida
    score = new Score();
    health = new Health(this);
    health->setPos(400, 25);
    health->setScale(1.5);
    scene->addItem(health);

    show();
}

void Game::spawn() {
    // spawna os inimigos
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

    if (highScore < score->getScore()) {
        highScore = score->getScore();
    }

    restartBtn = new Button(QString("Play again"), this);
    restartBtn->setPos(300, 300);
    scene->addItem(restartBtn);
    connect(restartBtn, SIGNAL(clicked()), this, SLOT(start()));

    closeBtn = new Button(QString("Quit"), this);
    closeBtn->setPos(300, 350);
    scene->addItem(closeBtn);
    connect(closeBtn, SIGNAL(clicked()), this, SLOT(close()));

    scene->addItem(score);
    score->setPos(345, 410);
    picture = new GameOver();
    picture->setPos(400, 200);
    picture->setScale(.4);
    scene->addItem(picture);

    QString bestScore = QString("Best Score: %1").arg(highScore);
    QGraphicsTextItem *highScoreText = scene->addText(bestScore);
    QFont scoreFont("Calibri", 18);
    highScoreText->setFont(scoreFont);
    highScoreText->setDefaultTextColor(Qt::cyan);
    int sxPos = 325;
    int syPos = 440;
    highScoreText->setPos(sxPos, syPos);

    scene->removeItem(health);
}

void Game::drawPanel(int x, int y, int width, int height, QColor color, double opacity) {
    QGraphicsRectItem *panel = new QGraphicsRectItem(x, y, width, height);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(color);
    panel->setBrush(brush);
    panel->setOpacity(opacity);
    scene->addItem(panel);
}
