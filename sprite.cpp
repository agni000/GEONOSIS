#include "sprite.h"
#include "enemybullet.h"
#include "game.h"
#include "QKeyEvent"
#include <QGraphicsItem>
#include <QGraphicsView>
#include "bullet.h"
#include "weakenemy.h"

extern Game *game;

Sprite::Sprite(QObject *parent) : QObject(parent) {
    timer = new QTimer();
    currentPixMap = new QPixmap(":/images/png/spritesheet.png");
    deathSprite = new QPixmap(":/images/png/gameover.png");
    rows = 0;
    columns = 0;

    //dimensoes de cada imagem iterada
    width = 176;
    height = 96;

    timer->start(50);
    connect(timer, &QTimer::timeout, this, &Sprite::Refresh);
    connect(timer, &QTimer::timeout, this, &Sprite::collision);
}

void Sprite::Refresh() {
    columns += 176;

    if (columns >= 528) {
        columns = 0;
    }
    this->update(-width/2, -height/2, width, height);
}

QRectF Sprite::boundingRect() const {
    return QRectF(-width/2, -height/2, width, height);
}

void Sprite::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->drawPixmap(-width/2, -height/2, *currentPixMap, columns, 0, width, height);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void Sprite::keyPressEvent(QKeyEvent *event) {
    float x = game->ship->x();
    float y = game->ship->y();
    Bullet *bullet = new Bullet();

    switch(event->key()) {
    case Qt::Key_Right:
        if (x < 750) {
            game->ship->setPos(x + 5, y);
        }
        break;
    case Qt::Key_Left:
        if (x > 5) {
            game->ship->setPos(x - 5, y);
        }
        break;
    case Qt::Key_Space:
        bullet->setPos(x, y + 20);
        game->scene->addItem(bullet);
        break;
    case Qt::Key_Up:
        if (y > 20) {
            game->ship->setPos(x, y - 15);
        }
        break;
    case Qt::Key_Down:
        if (y < 580) {
            game->ship->setPos(x, y + 15);
        }
        break;
    }
}

void Sprite::collision() {
    QList<QGraphicsItem*> colliding_item = collidingItems();
    for(int i = 0, n = colliding_item.size(); i < n; i++)
    {
        if(typeid(*(colliding_item[i])) == typeid(Enemy))
        {
            game->health->decrease();
            scene()->removeItem(colliding_item[i]);
            delete colliding_item[i];
            qDebug() << "Colisao";
            if (game->health->getHealth() == -1) {
                currentPixMap = deathSprite;
                update();
            }
            return;
        }
    }

    QList<QGraphicsItem*> colliding_weakEnemy = collidingItems();
    for(int i = 0, n = colliding_weakEnemy.size(); i < n; i++)
    {
        if(typeid(*(colliding_weakEnemy[i])) == typeid(WeakEnemy))
        {
            game->health->decrease();
            scene()->removeItem(colliding_weakEnemy[i]);
            delete colliding_weakEnemy[i];
            qDebug() << "Colisao";
            if (game->health->getHealth() == -1) {
                currentPixMap = deathSprite;
                update();
            }
            return;
        }
    }

    QList<QGraphicsItem*> colliding_EnemyBullet = collidingItems();
    for(int i = 0, n = colliding_EnemyBullet.size(); i < n; i++)
    {
        if(typeid(*(colliding_EnemyBullet[i])) == typeid(EnemyBullet))
        {
            game->health->decrease();
            scene()->removeItem(colliding_EnemyBullet[i]);
            delete colliding_EnemyBullet[i];
            qDebug() << "Colisao";
            if (game->health->getHealth() == -1) {
                currentPixMap = deathSprite;
                update();
            }
            return;
        }
    }
}

