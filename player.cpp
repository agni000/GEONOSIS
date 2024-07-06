#include <QGraphicsScene>
#include <QObject>
#include <QTimer>
#include <QDebug>
#include <QKeyEvent>
#include "game.h"
#include "player.h"
#include "bullet.h"
#include "enemy.h"
#include "main.cpp"

extern Game *game;

Player::Player(QGraphicsItem *parent) : QGraphicsPixmapItem(parent) {
    QTimer *timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(colision()));
    timer->start(50);
}

void Player::keyPressEvent(QKeyEvent *event) {
    // mensagem informando que ocorreu uso do teclado
    //  qDebug() << "Key press detected";
    if (event->key() == Qt::Key_Left) {
        // limite para não sair da tela
        if (pos().x() > 0)
            setPos(x() - 10, y());
    } else if (event->key() == Qt::Key_Right) {
        // limite para não sair da tela
        if (pos().x() + 100 < 800)
            setPos(x() + 10, y());
    } else if (event->key() == Qt::Key_Up) {
        setPos(x(), y() - 10);
    } else if (event->key() == Qt::Key_Down) {
        setPos(x(), y() + 10);
    }

    // criar disparo
    if (event->key() == Qt::Key_Space) {
        Bullet *bullet = new Bullet();
        bullet->setPos(x() + 120, y() + 45);
        scene()->addItem(bullet);
    }
}

// void Player::spawn()
// {
//     // cria inimigo
//     Enemy *enemy = new Enemy();
//     Enemy *enemy2 = new Enemy();
//     scene()->addItem(enemy);
//     scene()->addItem(enemy2);
// }

// void Player::colision() {
//     QList<QGraphicsItem*> colliding_item = collidingItems();
//     for(int i = 0, n = colliding_item.size(); i < n; i++)
//     {
//         if(typeid(*(colliding_item[i]))== typeid(Enemy))
//         {
//             game->health->decrease();
//             scene()->removeItem(colliding_item[i]);
//             delete colliding_item[i];
//             qDebug() << "Colisao";
//             return;
//         }
//     }
// }
