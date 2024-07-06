#ifndef ENEMYBULLET_H
#define ENEMYBULLET_H
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QTimer>

class EnemyBullet : public QObject, public QGraphicsItem
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
    EnemyBullet(QGraphicsItem *parent = nullptr);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

public slots:
    void move();
    void Refresh();
};

#endif // ENEMYBULLET_H
