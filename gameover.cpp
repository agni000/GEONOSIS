#include "gameover.h"
#include "qpainter.h"

GameOver::GameOver(QGraphicsItem *parent): QGraphicsItem(parent)
{
    gameOverPic = new QPixmap(":/images/png/endd.png");
    rows = 0;
    columns = 0;
    width = 561;
    height = 386;
}

QRectF GameOver::boundingRect() const
{
    return QRectF(-width/2, -height/2, width, height);
}

void GameOver::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->drawPixmap(-width/2, -height/2, *gameOverPic, columns, rows, width, height);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}
