#include "SoldierGraphic.h"
#include <QTimer>

SoldierGraphic::SoldierGraphic(QGraphicsItem *parent) : QGraphicsPixmapItem(parent) {
    const QPixmap &qPixmap = QPixmap(":/images/source/soldier.png");
    setPixmap(qPixmap);
}
