#include "score.h"
#include <QFont>

Score::Score(QGraphicsItem *parent) : QGraphicsTextItem(parent) {
    score = 0;
    setPlainText(QString("Pontuação: ") + QString::number(score));
    setDefaultTextColor(Qt::blue);
    setFont(QFont("Calibri", 16));
}

void Score::increase()
{
    score += 35;
    setPlainText(QString("Pontuação: ") + QString::number(score));
    setDefaultTextColor(Qt::blue);
    setFont(QFont("Calibri", 16));
}

int Score::getScore()
{
    return score;
}
