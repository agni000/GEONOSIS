#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QDebug>
#include <QList>
#include <QGraphicsItem>
#include "enemybullet.h"
#include "game.h"

// declaração da variavel do tipo extern
// indica que essa variavel já foi declarada em algum outro arquivo do projeto
extern Game *game;

EnemyBullet::EnemyBullet(QGraphicsItem *parent) : QObject(), QGraphicsItem(parent) {
    bulletSprite = new QPixmap(":/images/png/enemybullet.png");

    rows = 0;
    columns = 0;

    //dimensoes de cada imagem iterada
    width = 81;
    height = 58;

    // conectar o timer com o movimento
    timer = new QTimer();
    timer->start(30);
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    connect(timer, SIGNAL(timeout()), this, SLOT(Refresh()));
}

EnemyBullet::~EnemyBullet() {
    delete bulletSprite;
    delete timer;
}

void EnemyBullet::move() {
    setPos(x()-10, y());
    if(pos().x() < 50) {
        scene()->removeItem(this);
        delete this;
    }
}

QRectF EnemyBullet::boundingRect() const {
    return QRectF(-width/2, -height/2, width, height);
}

void EnemyBullet::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->drawPixmap(-width/2, -height/2, *bulletSprite, columns, 0, width, height);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void EnemyBullet::Refresh() {
    columns += 81;

    if (columns >= 243) {
        columns = 0;
    }
    this->update(-width/2, -height/2, width, height);
}

