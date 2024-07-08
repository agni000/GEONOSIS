#ifndef HEALTH_H
#define HEALTH_H

#include <QGraphicsTextItem>

class Health : public QObject, public QGraphicsItem
{
    Q_OBJECT
protected:
    QPixmap *healthSprite;
    float rows;
    float columns;
    float width;
    float height;
    int m_health;
public:
    Health(QObject *parent = nullptr);
    ~Health();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void decrease();
    void Refresh();
    int getHealth() {return m_health;}
};

#endif // HEALTH_H
