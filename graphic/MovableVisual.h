#ifndef SOLDIERAPP_MOVABLEVISUAL_H
#define SOLDIERAPP_MOVABLEVISUAL_H


#include <QtWidgets/QGraphicsItem>

/**
 * Graphical representation (for example pixmap or text), which can move or jump.
 */
class MovableVisual: public QObject {
    Q_OBJECT
public:
    /**
     * Value of gravity constant used for jump
     */
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
    /**
     * inits jump (blocking action)
     * @param x destination
     * @param y destination
     */
    void jump(const double x, const double y);
    /**
     * inits move (blocking action)
     * @param x destination
     * @param y destination
     */
    void move(const double x, const double y);

signals:
    /**
     * Handles end of blocking action
     */
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
