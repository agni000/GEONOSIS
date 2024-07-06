#include "enemy2.h"
#include "game.h"
#include <QTimer>

extern Game *game;

Enemy2::Enemy2(QGraphicsItem *parent) : QGraphicsItem(parent) {
    enemy2Sprite = new QPixmap(":/images/png/enemy2.png");

    // posição aleatoria
    float random_number = rand() % 600;
    setScale(.6);
    setPos(850, random_number);

    rows = 0;
    columns = 0;

    width = 176;
    height = 125;

    //movimentação
    QTimer *timer = new QTimer();
    timer->start(50);
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    connect(timer, SIGNAL(timeout()), this, SLOT(Refresh()));
}

void Enemy2::move() {
    setPos(x()-5,y());
    if(pos().y() > 700)
    {
        scene()->removeItem(this);
        delete this;
        qDebug()<<"Enemy removed";
    }
}

QRectF Enemy2::boundingRect() const {
    return QRectF(-width/2, -height/2, width, height);
}

void Enemy2::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->drawPixmap(-width/2, -height/2, *enemy2Sprite, columns, 0, width, height);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void Enemy2::Refresh() {
    columns += 176;

    if (columns >= 528) {
        columns = 0;
    }
    this->update(-width/2, -height/2, width, height);
}
