#ifndef SOLDIERAPP_SOLDIERVISUAL_H
#define SOLDIERAPP_SOLDIERVISUAL_H


static const int JUMP_INITIAL_SPEED = 8;

#include <QtWidgets/QLabel>
#include <QtCore/QTimer>
#include "SoldierPixmap.h"

class SoldierVisual: public QObject {
    Q_OBJECT

public:
    SoldierVisual(const long id, const QString &name, const double x, const double y);
    ~SoldierVisual();

    void jump();
    void move(double xDifference, double yDifference);
    void salute();
    long getId() const;
    SoldierPixmap *getSoldierPixmap() const;
    QGraphicsTextItem *getNameText() const;

    static const double GRAVITY_CONSTANT; // TODO: should be holded in other class
    static const double MOVE_SPEED;
    static const double JUMP_SPEED;
    static const double Y_TEXT_DISTANCE;

public slots:
    void processCompletedBlockingAction();

    void moveNameText();
signals:
    void jumpSoldierPixmap(const double x, const double y, const double speed);
    void moveSoldierPixmap(const double x, const double y, const double speed);
    void saluteSoldierPixmap();
private:
    SoldierPixmap *createSoldierPixmap(const double x, const double y);
    std::pair<double, double> calculateTextPosition(const QString &name, const double x, const double y) const;

    void initMovingNameText();
    long id;
    double x;
    double y;
    bool isPerformingBlockingAction = false;
    SoldierPixmap * soldierPixmap;
    QGraphicsTextItem * nameText;

    QTimer *timer;

    bool moveInX();

    bool moveInY();

    bool isPerformingLastStep(double xDistance) const;

    double calculatePositionDuringJump() const;

    bool isAboveGround(double currentY);

    const double calculateDistanceDifference(double distance) const;

    bool checkIfMustMove(double distance) const;
};


#endif //SOLDIERAPP_SOLDIERVISUAL_H
