#ifndef BULLET_H
#define BULLET_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QTimer>

class Bullet : public QObject, public QGraphicsItem
{
    Q_OBJECT
protected:
    QPixmap *bulletSprite;
    QTimer *timer;
    float rows;
    float columns;
    float width;
    float height;
public:
    Bullet(QGraphicsItem *parent = nullptr);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

public slots:
    void move();
    void Refresh();
    void collision();
};

#endif // BULLET_H
