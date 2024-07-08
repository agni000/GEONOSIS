#ifndef GAMEOVER_H
#define GAMEOVER_H
#include <QObject>
#include "qgraphicsitem.h"
#include "qobject.h"


class GameOver : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    GameOver(QGraphicsItem *parent = nullptr);
    ~GameOver();
protected:
    QPixmap *gameOverPic;
    float rows;
    float columns;
    float width;
    float height;

    //metodos
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // GAMEOVER_H
