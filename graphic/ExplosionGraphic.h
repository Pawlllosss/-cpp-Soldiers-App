#ifndef SOLDIERAPP_EXPLOSIONGRAPHIC_H
#define SOLDIERAPP_EXPLOSIONGRAPHIC_H

#include <QtWidgets/QGraphicsPixmapItem>

class ExplosionGraphic: public QObject, public QGraphicsPixmapItem {
Q_OBJECT

public:
    ExplosionGraphic(double startX, double startY, QGraphicsItem *parent = 0);

private slots:
    void fade();

private:
    static const double fadingVelocity;
    bool checkIfFaded();
    void cleanObject();

    double startX;
    double startY;
};


#endif //SOLDIERAPP_EXPLOSIONGRAPHIC_H
