#ifndef ENEMY_H
#define ENEMY_H
#include <QGraphicsItem>
#include <QObject>

class Enemy : public QObject, public QGraphicsItem
{
    Q_OBJECT
protected:
    QPixmap *enemySprite;
    QTimer *timer;
    float rows;
    float columns;
    float width;
    float height;
    int bulletFlag;
public:
    Enemy(QGraphicsItem *parent = nullptr);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

public slots:
    void move();
    void Refresh();
};

#endif // ENEMY_H
