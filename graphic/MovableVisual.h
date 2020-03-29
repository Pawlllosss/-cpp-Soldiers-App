#ifndef SOLDIERAPP_MOVABLEVISUAL_H
#define SOLDIERAPP_MOVABLEVISUAL_H


#include <QtWidgets/QGraphicsItem>

class MovableVisual: public QObject {
    Q_OBJECT
public:
    static const double GRAVITY_CONSTANT;

    MovableVisual(QGraphicsItem *graphicsItem, double xOffset, double yOffset, double moveSpeed, double jumpSpeed);
    MovableVisual(const MovableVisual & movableVisual);
    ~MovableVisual();

    double getXOffset() const;
    void setXOffset(double xOffset);
    double getYOffset() const;
    void setYOffset(double yOffset);
    double getMoveSpeed() const;
    void setMoveSpeed(double moveSpeed);
    double getJumpSpeed() const;
    void setJumpSpeed(double jumpSpeed);

public slots:
    void jump(const double x, const double y);
    void move(const double x, const double y);

signals:
    void blockingActionCompleted();

private slots:
    void processJump();
    void processMove();

private:
    bool checkIfMustMove(double distance) const;
    const double calculateDistanceDifference(double distance) const;
    double calculatePositionDuringJump() const;
    bool isAboveGround(double currentY);
    bool moveInX();
    bool moveInY();
    bool isPerformingLastStep(double xDistance) const;

    QTimer *timer;
    QGraphicsItem *graphicsItem;
    double xOffset;
    double yOffset;
    double xDestination;
    double yDestination;
    double moveSpeed;
    double jumpSpeed;
    unsigned long jumpTime = 0;
};


#endif //SOLDIERAPP_MOVABLEVISUAL_H
