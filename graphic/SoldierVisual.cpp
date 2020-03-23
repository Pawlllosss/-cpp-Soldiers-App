#include "SoldierVisual.h"

SoldierVisual::SoldierVisual(long id, SoldierPixmap *soldierPixmap) : id(id), soldierPixmap(soldierPixmap) {}

SoldierVisual::~SoldierVisual() {
    delete soldierPixmap;
}

long SoldierVisual::getId() const {
    return id;
}

SoldierPixmap *SoldierVisual::getSoldierPixmap() const {
    return soldierPixmap;
}
