#ifndef SOLDIERAPP_SOLDIERVISUAL_H
#define SOLDIERAPP_SOLDIERVISUAL_H


#include "SoldierPixmap.h"

class SoldierVisual {
public:
    SoldierVisual(long id, SoldierPixmap *soldierPixmap);
    ~SoldierVisual();

    long getId() const;

    SoldierPixmap *getSoldierPixmap() const;

private:
    long id;
    SoldierPixmap * soldierPixmap;
};


#endif //SOLDIERAPP_SOLDIERVISUAL_H
