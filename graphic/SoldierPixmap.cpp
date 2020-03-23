#include "SoldierPixmap.h"
#include <QTimer>

const double SoldierPixmap::PIXMAP_WIDTH = 50;

SoldierPixmap::SoldierPixmap(QGraphicsItem *parent) : QGraphicsPixmapItem(parent) {
    const QPixmap &qPixmap = QPixmap(":/images/source/soldier.png");
    setPixmap(qPixmap);
}
