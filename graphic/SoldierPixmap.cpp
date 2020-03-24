#include "SoldierPixmap.h"
#include <QTimer>

const double SoldierPixmap::PIXMAP_WIDTH = 50;

SoldierPixmap::SoldierPixmap(QGraphicsItem *parent) : QGraphicsPixmapItem(parent) {
    const QPixmap &qPixmap = QPixmap(":/images/source/soldier.png");
    setPixmap(qPixmap);

    auto *timer = new QTimer(this);
    timer->start(50);
    connect(timer,SIGNAL(timeout()),this,SLOT(moveToDestination()));
}

void SoldierPixmap::move(const double x, const double y, const double speed) {
    xDestination = x;
    yDestination = y;
    currentSpeed = speed;
}

void SoldierPixmap::moveToDestination() {
    double xDistance = x() - xDestination;
    double yDistance = y() - yDestination;

    if (checkIfMustMove(xDistance)) {
        const double xDistanceDifference = calculateDistanceDifference(xDistance);
        setPos(x() + xDistanceDifference, y());
    }
    if (checkIfMustMove(yDistance)) {
        const double yDistanceDifference = calculateDistanceDifference(yDistance);
        setPos(x(), y() + yDistanceDifference);
    }
}

bool SoldierPixmap::checkIfMustMove(double distance) const {
    return abs(distance) > 0.01;
}

const double SoldierPixmap::calculateDistanceDifference(double distance) const {
    return distance > 0 ? -currentSpeed : currentSpeed;
}
