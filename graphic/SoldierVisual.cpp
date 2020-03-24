#include "SoldierVisual.h"
#include <QTimer>

const double SoldierVisual::SPEED = 4;

SoldierVisual::SoldierVisual(long id, const double x, const double y) : id(id), x(x), y(y),
                                                                        soldierPixmap(createSoldierPixmap(x, y)) {
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

void SoldierVisual::move(const double xDifference, const double yDifference) {
    x += xDifference;
    y += yDifference;
    emit moveSoldierPixmap(x + xDifference, y + yDifference, SPEED);
}

SoldierPixmap *SoldierVisual::createSoldierPixmap(const double x, const double y) {
    auto *soldierPixmap = new SoldierPixmap;
    soldierPixmap->setPos(x, y);

    return soldierPixmap;
}