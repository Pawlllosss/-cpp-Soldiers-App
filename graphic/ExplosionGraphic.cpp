#include "ExplosionGraphic.h"
#include <QGraphicsScene>
#include <QTimer>

const double ExplosionGraphic::fadingVelocity = 0.05;

ExplosionGraphic::ExplosionGraphic(double startX, double startY, QGraphicsItem *parent) : startX(startX), startY(startY),
                                                            QGraphicsPixmapItem(parent) {
    const QPixmap &pixmap = QPixmap(":/images/source/explosion.png");
    setPixmap(pixmap);
    setPos(startX, startY);

    auto *timer = new QTimer(this);
    timer->start(50);
    connect(timer, SIGNAL(timeout()), this, SLOT(fade()));
}

void ExplosionGraphic::fade() {
    if (checkIfFaded()) {
        cleanObject();
    } else {
        setOpacity(opacity() - fadingVelocity);
    }
}

bool ExplosionGraphic::checkIfFaded() {
    qreal d = opacity();
    return d <= 0.;
}

void ExplosionGraphic::cleanObject() {
    scene()->removeItem(this);
    delete this;
}
