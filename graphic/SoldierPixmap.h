#ifndef SOLDIERAPP_SOLDIERPIXMAP_H
#define SOLDIERAPP_SOLDIERPIXMAP_H


#include <QtWidgets/QGraphicsRectItem>

class SoldierPixmap: public QGraphicsPixmapItem {
public:
    SoldierPixmap(QGraphicsItem *parent = 0);

    const static double PIXMAP_WIDTH;
};


#endif //SOLDIERAPP_SOLDIERPIXMAP_H
