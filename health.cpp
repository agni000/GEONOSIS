#include <QFont>
#include <QGraphicsTextItem>
#include "health.h"
#include "game.h"
#include "qpainter.h"

extern Game *game;

Health::Health(QGraphicsItem *parent) : QGraphicsItem(parent) {
    m_health = 6;
    healthSprite = new QPixmap(":/images/png/HealthUI.png");

    rows = 0;
    columns = 0;

    width = 33;
    height = 11;
}

void Health::decrease()
{
    m_health--;
    Refresh();

    if (m_health == -1) {
        game->Game_Over();
    }
}

QRectF Health::boundingRect() const {
    return QRectF(-width/2, -height/2, width, height);
}

void Health::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->drawPixmap(-width/2, -height/2, *healthSprite, 0, rows, width, height);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void Health::Refresh() {
    rows += 11;
    if (rows >= 77) {
        rows = 0;
    }
    this->update(-width/2, -height/2, width, height);
}
