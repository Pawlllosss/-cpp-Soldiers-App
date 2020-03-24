#ifndef SOLDIERAPP_SOLDIERPIXMAP_H
#define SOLDIERAPP_SOLDIERPIXMAP_H


#include <QtWidgets/QGraphicsRectItem>

class SoldierPixmap: public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    SoldierPixmap(QGraphicsItem *parent = 0);

    const static double PIXMAP_WIDTH;

public slots:
    void move(const double x, const double y, const double speed);

private slots:
    void moveToDestination();

private:
    bool checkIfMustMove(double distance) const;
    const double calculateDistanceDifference(double distance) const;

    double xDestination;
    double yDestination;
    double currentSpeed;
};


#endif //SOLDIERAPP_SOLDIERPIXMAP_H
