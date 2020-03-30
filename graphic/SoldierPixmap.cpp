#include "SoldierPixmap.h"
#include "SoldierVisual.h"
#include <QTimer>

const double SoldierPixmap::PIXMAP_WIDTH = 50;

SoldierPixmap::SoldierPixmap(QGraphicsItem *parent) : timer(new QTimer(this)), QGraphicsPixmapItem(parent) {
    standingSoldierPixmap = new QPixmap(":/images/source/soldier.png");
    salutingSoldierPixmap = new QPixmap(":/images/source/soldierSalute.png");
    setPixmap(*standingSoldierPixmap);
}

void SoldierPixmap::salute() {
    timer->start(3000);
    setPixmap(*salutingSoldierPixmap);
    connect(timer, SIGNAL(timeout()),this, SLOT(endSalute()));
}

void SoldierPixmap::endSalute() {
    setPixmap(*standingSoldierPixmap);
    disconnect(timer, SIGNAL(timeout()),this, SLOT(endSalute()));
    emit blockingActionCompleted();
}

