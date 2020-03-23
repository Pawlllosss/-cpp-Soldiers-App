#ifndef SOLDIERAPP_GRENADEGRAPHIC_H
#define SOLDIERAPP_GRENADEGRAPHIC_H

#include <QtWidgets/QGraphicsPixmapItem>

//TODO: could use something for base class (isOutsideScreen)
//TODO: as well as for time unit (50ms)
//TODO: and for clean object
class GrenadeGraphic: public QObject, public QGraphicsPixmapItem {
    Q_OBJECT

public:
    GrenadeGraphic(double startX, double startY, QGraphicsItem *parent = 0);

signals:
    void explode(const double x, const double y);

private slots:
    void move();

private:
    static const double velocity;
    static const double rotationVelocity;
    static const double explosionVerticalDistance;
    double startX;
    double startY;

    bool checkIfExplode();
    bool isOutsideScreen() const;
    void cleanObject();
};

#endif //SOLDIERAPP_GRENADEGRAPHIC_H
