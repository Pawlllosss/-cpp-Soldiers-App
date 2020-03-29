#include "MovableVisual.h"
#include <QTimer>

const double MovableVisual::GRAVITY_CONSTANT = 0.5;

MovableVisual::MovableVisual(QGraphicsItem *graphicsItem, double xOffset, double yOffset, double moveSpeed,
                             double jumpSpeed) : graphicsItem(graphicsItem), xOffset(xOffset), yOffset(yOffset),
                                                 moveSpeed(moveSpeed), jumpSpeed(jumpSpeed), timer(new QTimer) {
}

MovableVisual::MovableVisual(const MovableVisual &movableVisual) : graphicsItem(movableVisual.graphicsItem),
                                                                   xOffset(movableVisual.xOffset),
                                                                   yOffset(movableVisual.yOffset),
                                                                   moveSpeed(movableVisual.moveSpeed),
                                                                   jumpSpeed(movableVisual.jumpSpeed),
                                                                   timer(new QTimer) {
}

MovableVisual::~MovableVisual() {
    delete timer;
}

void MovableVisual::jump(const double x, const double y) {
    timer->start(50);
    jumpTime = 1;
    xDestination = x + xOffset;
    yDestination = y + yOffset;
    connect(timer, SIGNAL(timeout()), this, SLOT(processJump()));
}

void MovableVisual::move(const double x, const double y) {
    timer->start(50);
    xDestination = x + xOffset;
    yDestination = y + yOffset;
    connect(timer, SIGNAL(timeout()), this, SLOT(processMove()));
}

void MovableVisual::processJump() {
    double yPosition = calculatePositionDuringJump();

    if (isAboveGround(yPosition)) {
        graphicsItem->setPos(graphicsItem->x(), yPosition);
        ++jumpTime;
    } else {
        graphicsItem->setPos(graphicsItem->x(), yDestination);
        disconnect(timer, SIGNAL(timeout()), this, SLOT(processJump()));
        emit blockingActionCompleted();
    }
}

void MovableVisual::processMove() {
    bool xFinished = moveInX();
    bool yFinished = moveInY();
    bool hasFinished = xFinished && yFinished;

    if (hasFinished) {
        disconnect(timer, SIGNAL(timeout()), this, SLOT(processMove()));
        emit blockingActionCompleted();
    }
}

bool MovableVisual::moveInX() {
    double xDistance = graphicsItem->x() - xDestination;
    bool hasFinished = true;

    if (checkIfMustMove(xDistance)) {
        const double xDistanceDifference = calculateDistanceDifference(xDistance);
        double distanceAfterMove;
        if (isPerformingLastStep(xDistance)) {
            distanceAfterMove = xDestination;
        } else {
            distanceAfterMove = graphicsItem->x() + xDistanceDifference;
            hasFinished = false;
        }
        graphicsItem->setPos(distanceAfterMove, graphicsItem->y());
    }
    return hasFinished;
}

bool MovableVisual::moveInY() {
    double yDistance = graphicsItem->y() - yDestination;
    bool hasFinished = true;

    if (checkIfMustMove(yDistance)) {
        const double yDistanceDifference = calculateDistanceDifference(yDistance);
        double distanceAfterMove;
        if (isPerformingLastStep(yDistance)) {
            distanceAfterMove = yDestination;
        } else {
            distanceAfterMove = graphicsItem->y() + yDistanceDifference;
            hasFinished = false;
        }
        graphicsItem->setPos(graphicsItem->x(), distanceAfterMove);
    }
    return hasFinished;
}

bool MovableVisual::isPerformingLastStep(double xDistance) const { return abs(xDistance) <= moveSpeed; }

double MovableVisual::calculatePositionDuringJump() const {
    return yDestination - jumpSpeed * jumpTime + MovableVisual::GRAVITY_CONSTANT * jumpTime * jumpTime;
}

bool MovableVisual::isAboveGround(double currentY) {
    return currentY < yDestination;
}

const double MovableVisual::calculateDistanceDifference(double distance) const {
    return distance > 0 ? -moveSpeed : moveSpeed;
}

bool MovableVisual::checkIfMustMove(double distance) const {
    return abs(distance) > 0.01;
}

double MovableVisual::getXOffset() const {
    return xOffset;
}

void MovableVisual::setXOffset(double xOffset) {
    MovableVisual::xOffset = xOffset;
}

double MovableVisual::getYOffset() const {
    return yOffset;
}

void MovableVisual::setYOffset(double yOffset) {
    MovableVisual::yOffset = yOffset;
}

double MovableVisual::getMoveSpeed() const {
    return moveSpeed;
}

void MovableVisual::setMoveSpeed(double moveSpeed) {
    MovableVisual::moveSpeed = moveSpeed;
}

double MovableVisual::getJumpSpeed() const {
    return jumpSpeed;
}

void MovableVisual::setJumpSpeed(double jumpSpeed) {
    MovableVisual::jumpSpeed = jumpSpeed;
}
