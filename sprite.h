#ifndef SPRITE_H
#define SPRITE_H

#include <QObject>
#include <QGraphicsItem>
#include <QTimer>
#include <QPixmap>
#include <QPainter>
#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include "enemy.h"

class Sprite : public QObject, public QGraphicsItem
{
    Q_OBJECT
protected:
    QTimer *timer;
    QPixmap *currentPixMap;
    QPixmap *deathSprite;
    float rows;
    float columns;
    float width;
    float height;
public:
    Sprite(QObject *parent = nullptr);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void CheckIdle(QKeyEvent *event);
    void Running(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    // void keyReleaseEvent(QKeyEvent *event);
signals:

public slots:
    void Refresh();
    void keyPressEvent(QKeyEvent *event);
    void collision();
};

#endif // SPRITE_H
