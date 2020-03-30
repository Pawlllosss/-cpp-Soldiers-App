#ifndef SOLDIERAPP_BULLETGRAPHIC_H
#define SOLDIERAPP_BULLETGRAPHIC_H


#include <QtWidgets/QGraphicsPixmapItem>

/**
 * Pixmap representation of moving bullet
 */
class BulletGraphic: public QObject, public QGraphicsPixmapItem {
Q_OBJECT

public:
    BulletGraphic(QGraphicsItem *parent = 0);

private slots:
    void move();
};


#endif //SOLDIERAPP_BULLETGRAPHIC_H
