#include "GrenadeGraphic.h"
#include <QGraphicsScene>
#include <QTimer>

const double GrenadeGraphic::velocity = 5.;
const double GrenadeGraphic::rotationVelocity = 2.;
const double GrenadeGraphic::explosionVerticalDistance = 150.;

GrenadeGraphic::GrenadeGraphic(double startX, double startY, QGraphicsItem *parent) : startX(startX), startY(startY),
                                                                                      QGraphicsPixmapItem(parent) {
    const QPixmap &pixmap = QPixmap(":/images/source/grenade.png");
    setPixmap(pixmap);
    setPos(startX, startY);

    auto *timer = new QTimer(this);
    timer->start(50);
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));

}

void GrenadeGraphic::move() {
    if (checkIfExplode()) {
        emit explode(x(), y());
        cleanObject();
    } else if (isOutsideScreen()) {
        cleanObject();
    } else {
        setRotation(rotation() + rotationVelocity);
        setPos(x(), y() - velocity);
    }
}

void GrenadeGraphic::cleanObject() {
    scene()->removeItem(this);
    delete this;
}

bool GrenadeGraphic::checkIfExplode() {
    return startY - y() > explosionVerticalDistance;
}

bool GrenadeGraphic::isOutsideScreen() const { return pos().y() < 0; }
