#ifndef SOLDIERAPP_SOLDIERPIXMAP_H
#define SOLDIERAPP_SOLDIERPIXMAP_H

#include <QtWidgets/QGraphicsRectItem>

class SoldierPixmap: public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    SoldierPixmap(QGraphicsItem *parent = 0);
    //TODO: add destructor

    const static double PIXMAP_WIDTH;

public slots:
    void jump(const double x, const double y, const double speed);
    void move(const double x, const double y, const double speed);
    void salute();

signals:
    void blockingActionCompleted();

private slots:
    void processJump();
    void processMove();
    void endSalute();

private:
    bool checkIfMustMove(double distance) const;
    const double calculateDistanceDifference(double distance) const;
    double calculatePositionDuringJump() const;
    bool isAboveGround(double currentY);
    bool moveInX();
    bool moveInY();
    bool isPerformingLastStep(double xDistance) const;

    QTimer *timer;
    QPixmap * standingSoldierPixmap;
    QPixmap * salutingSoldierPixmap;
    unsigned long jumpTime = 0;
    double xDestination;
    double yDestination;
    double movingSpeed;
    double currentJumpSpeed;
};


#endif //SOLDIERAPP_SOLDIERPIXMAP_H
