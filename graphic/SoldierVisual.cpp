#include "SoldierVisual.h"
#include <QTimer>

const double SoldierVisual::GRAVITY_CONSTANT = 0.5;
const double SoldierVisual::SPEED = 4;

SoldierVisual::SoldierVisual(long id, const double x, const double y) : id(id), x(x), y(y),
                                                                        soldierPixmap(createSoldierPixmap(x, y)) {
    connect(this, &SoldierVisual::jumpSoldierPixmap, soldierPixmap, &SoldierPixmap::jump);
    connect(this, &SoldierVisual::moveSoldierPixmap, soldierPixmap, &SoldierPixmap::move);
}

SoldierVisual::~SoldierVisual() {
    delete soldierPixmap;
}

long SoldierVisual::getId() const {
    return id;
}

SoldierPixmap *SoldierVisual::getSoldierPixmap() const {
    return soldierPixmap;
}

void SoldierVisual::jump() {
    emit jumpSoldierPixmap(x, y, 11);
}

void SoldierVisual::move(const double xDifference, const double yDifference) {
    x += xDifference;
    y += yDifference;
    emit moveSoldierPixmap(x, y, SPEED);
}

SoldierPixmap *SoldierVisual::createSoldierPixmap(const double x, const double y) {
    auto *soldierPixmap = new SoldierPixmap;
    soldierPixmap->setPos(x, y);

    return soldierPixmap;
}
