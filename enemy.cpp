#include <QTimer>
#include <QGraphicsScene>
#include <QDebug>
#include "enemy.h"
#include "game.h"
#include "enemybullet.h"

extern Game *game;

Enemy::Enemy(QGraphicsItem *parent) : QGraphicsItem(parent) {
    enemySprite = new QPixmap(":/images/png/enemys.png");

    // posição aleatoria
    float random_number = rand() % 600;
    setScale(.6);
    setPos(850, random_number);
    bulletFlag = 0;
    rows = 0;
    columns = 0;

    width = 329;
    height = 160;

    //movimentação
    timer = new QTimer();
    timer->start(50);
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    connect(timer, SIGNAL(timeout()), this, SLOT(Refresh()));
}

Enemy::~Enemy() {
    if (enemySprite) {
        delete enemySprite;
    }

    if (timer) {
        delete timer;
    }
}

void Enemy::move() {
    setPos(x()-5,y());

    if (game->ship->isAlive()) {
        if(pos().x() < 25) {
            scene()->removeItem(this);
            delete this;
        }
    } else {
        scene()->removeItem(this);
        delete this;
    }
}

QRectF Enemy::boundingRect() const {
    return QRectF(-width/2, -height/2, width, height);
}

void Enemy::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->drawPixmap(-width/2, -height/2, *enemySprite, columns, 0, width, height);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void Enemy::Refresh() {
    columns += 329;
    bulletFlag++;
    if (columns >= 987) {
        columns = 0;
    }
    this->update(-width/2, -height/2, width, height);

    if (bulletFlag == 60) {
        EnemyBullet *EnmyBullet = new EnemyBullet();
        EnmyBullet->setPos(pos().x() - 45, pos().y() + 20);
        EnmyBullet->setScale(.6);
        game->scene->addItem(EnmyBullet);
        bulletFlag = 0;
    }
}
