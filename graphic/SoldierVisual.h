#ifndef SOLDIERAPP_SOLDIERVISUAL_H
#define SOLDIERAPP_SOLDIERVISUAL_H


#include "SoldierPixmap.h"

class SoldierVisual: public QObject {
    Q_OBJECT

public:
    SoldierVisual(long id, const double x, const double y);
    ~SoldierVisual();

    void jump();
    void move(const double xDifference, const double yDifference);
    long getId() const;
    SoldierPixmap *getSoldierPixmap() const;

    static const double GRAVITY_CONSTANT; // TODO: should be holded in other class
    static const double SPEED;

public slots:
    void processCompletedBlockingAction();

signals:
    void jumpSoldierPixmap(const double x, const double y, const double speed);
    void moveSoldierPixmap(const double x, const double y, const double speed);

private:
    SoldierPixmap *createSoldierPixmap(const double x, const double y);

    long id;
    double x;
    double y;
    bool isPerformingBlockingAction = false;
    SoldierPixmap * soldierPixmap;
};


#endif //SOLDIERAPP_SOLDIERVISUAL_H