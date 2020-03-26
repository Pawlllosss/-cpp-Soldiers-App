#include "SoldierPixmap.h"
#include "SoldierVisual.h"
#include <QTimer>

const double SoldierPixmap::PIXMAP_WIDTH = 50;

SoldierPixmap::SoldierPixmap(QGraphicsItem *parent) : timer(new QTimer(this)), QGraphicsPixmapItem(parent) {
    const QPixmap &qPixmap = QPixmap(":/images/source/soldier.png");
    setPixmap(qPixmap);
    timer->start(50);
}

void SoldierPixmap::jump(const double x, const double y, const double speed) {
    isPerformingAction = true;
    jumpTime = 1;
    xDestination = x;
    yDestination = y;
    currentJumpSpeed = speed;
    connect(timer,SIGNAL(timeout()),this, SLOT(processJump()));
}

void SoldierPixmap::move(const double x, const double y, const double speed) {
    isPerformingAction = true;
    xDestination = x;
    yDestination = y;
    movingSpeed = speed;
    connect(timer,SIGNAL(timeout()),this, SLOT(processMove()));
}

void SoldierPixmap::processJump() {
    double yPosition = calculatePositionDuringJump();

    if (isAboveGround(yPosition)) {
        setPos(x(), yPosition);
        ++jumpTime;
    } else {
        setPos(x(), yDestination);
        disconnect(timer,SIGNAL(timeout()),this, SLOT(processJump()));
        emit blockingActionCompleted();
    }
}

void SoldierPixmap::processMove() {
    bool hasFinished = moveInX() && moveInY();

    if (hasFinished) {
        disconnect(timer, SIGNAL(timeout()),this, SLOT(processMove()));
        emit blockingActionCompleted();
    }
}

bool SoldierPixmap::moveInX() {
    double xDistance = x() - xDestination;
    bool hasFinished = true;

    if (checkIfMustMove(xDistance)) {
        const double xDistanceDifference = calculateDistanceDifference(xDistance);
        double distanceAfterMove;
        if (isPerformingLastStep(xDistance)) {
            distanceAfterMove = xDestination;
        } else {
            distanceAfterMove  = x() + xDistanceDifference;
            hasFinished = false;
        }
        setPos(distanceAfterMove, y());
    }
    return hasFinished;
}

bool SoldierPixmap::moveInY() {
    double yDistance = y() - yDestination;
    bool hasFinished = true;

    if (checkIfMustMove(yDistance)) {
        const double yDistanceDifference = calculateDistanceDifference(yDistance);
        double distanceAfterMove;
        if (isPerformingLastStep(yDistance)) {
            distanceAfterMove = yDestination;
        } else {
            distanceAfterMove  = y() + yDistanceDifference;
            hasFinished = false;
        }
        setPos(x(), distanceAfterMove);
    }
    return hasFinished;
}

bool SoldierPixmap::isPerformingLastStep(double xDistance) const { return abs(xDistance) <= movingSpeed; }

double SoldierPixmap::calculatePositionDuringJump() const {
    return yDestination - currentJumpSpeed * jumpTime + SoldierVisual::GRAVITY_CONSTANT * jumpTime * jumpTime; }

bool SoldierPixmap::isAboveGround(double currentY) {
    return currentY < yDestination;
}

const double SoldierPixmap::calculateDistanceDifference(double distance) const {
    return distance > 0 ? -movingSpeed : movingSpeed;
}

bool SoldierPixmap::checkIfMustMove(double distance) const {
    return abs(distance) > 0.01;
}
