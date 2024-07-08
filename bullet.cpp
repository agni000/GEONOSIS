#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QDebug>
#include <QList>
#include <QGraphicsItem>
#include "bullet.h"
#include "game.h"
#include "weakenemy.h"

extern Game *game;

Bullet::Bullet(QGraphicsItem *parent) : QObject(), QGraphicsItem(parent) {
    bulletSprite = new QPixmap(":/images/png/bullet.png");

    rows = 0;
    columns = 0;

    //dimensoes de cada imagem iterada
    width = 48;
    height = 48;

    // conectar o timer com o movimento
    timer = new QTimer();
    timer->start(30);
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    connect(timer, SIGNAL(timeout()), this, SLOT(Refresh()));
    connect(timer, SIGNAL(timeout()), this, SLOT(collision()));
}

Bullet::~Bullet() {
    delete bulletSprite;
    delete timer;
}

void Bullet::move() {
    setPos(x()+10, y());
    if(pos().x() > 700) {
        delete this;
    }
}

QRectF Bullet::boundingRect() const {
    return QRectF(-width/2, -height/2, width, height);
}

void Bullet::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->drawPixmap(-width/2, -height/2, *bulletSprite, columns, 0, width, height);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void Bullet::Refresh() {
    columns += 48;

    if (columns >= 144) {
        columns = 0;
    }
    this->update(-width/2, -height/2, width, height);
}

void Bullet::collision() {
    QList<QGraphicsItem*> colliding_item = collidingItems();
    for(int i = 0, n = colliding_item.size(); i < n; i++)
    {
        if(typeid(*(colliding_item[i])) == typeid(Enemy) || typeid(*(colliding_item[i])) == typeid(WeakEnemy))
        {
            game->score->increase();
            scene()->removeItem(colliding_item[i]);
            delete this;
            delete colliding_item[i];
            return;
        }
    }
}
