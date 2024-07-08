#include "score.h"
#include <QFont>

Score::Score(QGraphicsItem *parent) : QGraphicsTextItem(parent) {
    score = 0;
    setPlainText(QString("Score: ") + QString::number(score));
    setDefaultTextColor(Qt::cyan);
    setFont(QFont("Calibri", 18));
}

void Score::increase()
{
    score += 35;
    setPlainText(QString("Score: ") + QString::number(score));
    setDefaultTextColor(Qt::cyan);
    setFont(QFont("Calibri", 18));
}

int Score::getScore()
{
    return score;
}
