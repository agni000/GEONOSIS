#include "weakenemy.h"
#include "enemybullet.h"
#include "game.h"
#include "qgraphicsscene.h"
#include "qpainter.h"
#include <QTimer>

extern Game *game;

WeakEnemy::WeakEnemy(QGraphicsItem *parent) : QGraphicsItem(parent) {
    weakSprite = new QPixmap(":/images/png/enemy2.png");

    // posição aleatoria
    float random_number = rand() % 600;
    setScale(.6);
    setPos(850, random_number);

    bulletFlag = 0;

    rows = 0;
    columns = 0;

    width = 176;
    height = 125;

    //movimentação
    timer = new QTimer();
    timer->start(50);
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    connect(timer, SIGNAL(timeout()), this, SLOT(Refresh()));
}

WeakEnemy::~WeakEnemy() {
    if (weakSprite) {
        delete weakSprite;
    }

    if (timer) {
        delete timer;
    }
}

void WeakEnemy::move() {
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

QRectF WeakEnemy::boundingRect() const {
    return QRectF(-width/2, -height/2, width, height);
}

void WeakEnemy::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->drawPixmap(-width/2, -height/2, *weakSprite, columns, 0, width, height);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void WeakEnemy::Refresh() {
    columns += 176;
    bulletFlag++;
    if (columns >= 528) {
        columns = 0;
    }
    this->update(-width/2, -height/2, width, height);

    if (bulletFlag == 27) {
        EnemyBullet *WeakEnemyBullet = new EnemyBullet();
        WeakEnemyBullet->setPos(pos().x() - 45, pos().y() + 20);
        WeakEnemyBullet->setScale(.3);
        game->scene->addItem(WeakEnemyBullet);
        bulletFlag = 0;
    }
}
