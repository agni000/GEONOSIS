#ifndef WEAKENEMY_H
#define WEAKENEMY_H

#include <QGraphicsItem>
#include <QObject>

class WeakEnemy : public QObject, public QGraphicsItem
{
    Q_OBJECT
protected:
    QPixmap *weakSprite;
    QTimer *timer;
    float rows;
    float columns;
    float width;
    float height;
    int bulletFlag;
public:
    WeakEnemy(QGraphicsItem *parent = nullptr);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

public slots:
    void move();
    void Refresh();
};


#endif // WEAKENEMY_H
