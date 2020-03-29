#include "SoldierVisual.h"
#include <QTimer>

const double SoldierVisual::MOVE_SPEED = 4;
const double SoldierVisual::JUMP_SPEED = 8;
const double SoldierVisual::Y_NAME_TEXT_OFFSET = -35;
const double SoldierVisual::X_TEXT_OFFSET = -15;

SoldierVisual::SoldierVisual(const long id, const QString &name, const double x, const double y) : id(id), x(x), y(y),
                                                                                                   soldierPixmap(createSoldierPixmap(x, y)),
                                                                                                   nameText(new QGraphicsTextItem),
                                                                                                   timer(new QTimer) {
    connect(this, &SoldierVisual::saluteSoldierPixmap, soldierPixmap, &SoldierPixmap::salute);
    connect(soldierPixmap, &SoldierPixmap::blockingActionCompleted, this, &SoldierVisual::processCompletedBlockingAction);
    movableVisuals = createMovableVisuals();
    connectBlockingActionCompletedOfMovableVisuals();
    nameText->setPlainText(name);
    std::pair<double, double> nameTextPosition = calculateTextPosition(name, x, y);
    nameText->setPos(nameTextPosition.first, nameTextPosition.second);
    timer->start(50);
}

SoldierVisual::~SoldierVisual() {
    delete soldierPixmap;
    delete nameText;
    delete timer;
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

        for (auto &visual : movableVisuals) {
            visual.jump(x, y);
        }
    }
}

void SoldierVisual::move(const double xDifference, const double yDifference) {
    if (!isPerformingBlockingAction) {
        isPerformingBlockingAction = true;
        x += xDifference;
        y += yDifference;

        for (auto &visual : movableVisuals) {
            visual.move(x, y);
        }
    }
}

void SoldierVisual::salute() {
    if (!isPerformingBlockingAction) {
        isPerformingBlockingAction = true;
        emit saluteSoldierPixmap();
    }
}

std::vector<MovableVisual> SoldierVisual::createMovableVisuals() {
    std::vector<MovableVisual> visuals;
    visuals.emplace_back(MovableVisual(soldierPixmap, 0, 0, SoldierVisual::MOVE_SPEED, SoldierVisual::JUMP_SPEED));
    visuals.emplace_back(MovableVisual(nameText, X_TEXT_OFFSET, Y_NAME_TEXT_OFFSET, SoldierVisual::MOVE_SPEED, SoldierVisual::JUMP_SPEED));

    return visuals;
}

void SoldierVisual::connectBlockingActionCompletedOfMovableVisuals() {
    for (const auto &visual : movableVisuals) {
        connect(&visual, &MovableVisual::blockingActionCompleted, this, &SoldierVisual::processCompletedBlockingAction);
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
    const double yTextPosition = y + Y_NAME_TEXT_OFFSET;

    return std::pair<double, double>(xTextPosition, yTextPosition);
}
