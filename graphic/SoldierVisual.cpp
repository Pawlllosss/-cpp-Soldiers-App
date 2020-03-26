#include "SoldierVisual.h"
#include <QTimer>

const double SoldierVisual::GRAVITY_CONSTANT = 0.5;
const double SoldierVisual::MOVE_SPEED = 4;
const double SoldierVisual::JUMP_SPEED = 8;
const double SoldierVisual::Y_TEXT_DISTANCE = -55;

SoldierVisual::SoldierVisual(const long id, const QString &name, const double x, const double y) : id(id), x(x), y(y),
                                                                                                   soldierPixmap(createSoldierPixmap(x, y)),
                                                                                                   nameText(new QGraphicsTextItem),
                                                                                                   timer(new QTimer){
    connect(this, &SoldierVisual::jumpSoldierPixmap, soldierPixmap, &SoldierPixmap::jump);
    connect(this, &SoldierVisual::moveSoldierPixmap, soldierPixmap, &SoldierPixmap::move);
    connect(soldierPixmap, &SoldierPixmap::blockingActionCompleted, this, &SoldierVisual::processCompletedBlockingAction);
    nameText->setPlainText(name);
    std::pair<double, double> nameTextPosition = calculateTextPosition(name, x, y);
    nameText->setPos(nameTextPosition.first, nameTextPosition.second);
    timer->start(50);
}

SoldierVisual::~SoldierVisual() {
    delete soldierPixmap;
}

long SoldierVisual::getId() const {
    return id;
}

QGraphicsTextItem *SoldierVisual::getNameText() const {
    return nameText;
}

SoldierPixmap *SoldierVisual::getSoldierPixmap() const {
    return soldierPixmap;
}

void SoldierVisual::processCompletedBlockingAction() {
    isPerformingBlockingAction = false;
}

void SoldierVisual::jump() {
    if (!isPerformingBlockingAction) {
        isPerformingBlockingAction = true;
        emit jumpSoldierPixmap(x, y, JUMP_SPEED);
    }
}

void SoldierVisual::move(const double xDifference, const double yDifference) {
    if (!isPerformingBlockingAction) {
        isPerformingBlockingAction = true;
        x += xDifference;
        y += yDifference;
        initMovingNameText();
        emit moveSoldierPixmap(x, y, MOVE_SPEED);
    }
}

SoldierPixmap *SoldierVisual::createSoldierPixmap(const double x, const double y) {
    auto *soldierPixmap = new SoldierPixmap;
    soldierPixmap->setPos(x, y);

    return soldierPixmap;
}

std::pair<double, double> SoldierVisual::calculateTextPosition(const QString &name, const double x, const double y) const {
    const double xCenter = x + SoldierPixmap::PIXMAP_WIDTH / 2;
    const double distanceMultiplier = name.size() / 2;
    const double letterDistance = 8;
    const double xTextPosition = xCenter - (letterDistance * distanceMultiplier);
    const double yTextPosition = y + Y_TEXT_DISTANCE;

    return std::pair<double, double>(xTextPosition, yTextPosition);
}

void SoldierVisual::initMovingNameText() {
    connect(timer, &QTimer::timeout,this, &SoldierVisual::moveNameText);
}

//TODO: refactor it to avoid duplicates (maybe some class wrapping SoldierPixmap and label (moveable graphic, etc.)
void SoldierVisual::moveNameText() {
    bool hasFinished = moveInY();

    if (hasFinished) {
        disconnect(timer, &QTimer::timeout,this, &SoldierVisual::moveNameText);
    }
}

bool SoldierVisual::moveInY() {
    double destination = y + Y_TEXT_DISTANCE;
    double yDistance = nameText->pos().y() - destination;
    bool hasFinished = true;

    if (checkIfMustMove(yDistance)) {
        const double yDistanceDifference = calculateDistanceDifference(yDistance);
        double distanceAfterMove;
        if (isPerformingLastStep(yDistance)) {
            distanceAfterMove = destination;
        } else {
            distanceAfterMove  = nameText->pos().y() + yDistanceDifference;
            hasFinished = false;
        }
        nameText->setPos(nameText->pos().x(), distanceAfterMove);
    }
    return hasFinished;
}

bool SoldierVisual::isPerformingLastStep(double xDistance) const { return abs(xDistance) <= MOVE_SPEED; }

const double SoldierVisual::calculateDistanceDifference(double distance) const {
    return distance > 0 ? -MOVE_SPEED : MOVE_SPEED;
}

bool SoldierVisual::checkIfMustMove(double distance) const {
    return abs(distance) > 0.01;
}
//TODO: refactor it!
