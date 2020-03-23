#include "BulletGraphic.h"
#include <QGraphicsScene>
#include <QTimer>

BulletGraphic::BulletGraphic(QGraphicsItem *parent) : QGraphicsPixmapItem(parent) {
    const QPixmap &pixmap = QPixmap(":/images/source/bullet.png");
    setPixmap(pixmap);

    auto *timer = new QTimer(this);
    timer->start(50);
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));
}

void BulletGraphic::move() {
    setPos(x(),y() - 10);

    if (pos().y() < 0) {
        scene()->removeItem(this);
        delete this;
    }
}
