//
// Created by pawlllosss on 22.03.2020.
//

#include "SoldierGraphic.h"

SoldierGraphic::SoldierGraphic(QGraphicsItem *parent) : QGraphicsPixmapItem(parent) {
//    const QPixmap &qPixmap = QPixmap("/home/pawlllosss/CLionProjects/untitled/source/soldier.png");
    const QPixmap &qPixmap = QPixmap(":/images/source/soldier.png");
    qPixmap.scaledToWidth(50);
    setPixmap(qPixmap);
}
