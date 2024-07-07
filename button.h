#ifndef BUTTON_H
#define BUTTON_H

#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>

class Button : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
private:
    QGraphicsTextItem *text;
public:
    //construtor
    Button(QString name, QObject *parent = nullptr);
    ~Button();

    //eventos
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
signals:
    void clicked();
};

#endif // BUTTON_H
