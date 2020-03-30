#ifndef SOLDIERAPP_SOLDIERVISUAL_H
#define SOLDIERAPP_SOLDIERVISUAL_H

#include <QtWidgets/QLabel>
#include <QtCore/QTimer>
#include "SoldierPixmap.h"
#include "MovableVisual.h"

/**
 * Represent soldier in graphical form with pixmap and text representing name, which can perform actions such as jump,
 * shoot, throw grenade, move.
 */
class SoldierVisual: public QObject {
    Q_OBJECT

public:
    SoldierVisual(long id, const QString &name, double x, double y);
    ~SoldierVisual();

    /**
     * Performs jump action (blocking action)
     */
    void jump();
    /**
    * Performs move action (blocking action)
    */
    void move(double xDifference, double yDifference);
    /**
    * Performs salute action (blocking action)
    */
    void salute();
    long getId() const;
    SoldierPixmap *getSoldierPixmap() const;
    QGraphicsTextItem *getNameText() const;

public slots:
    /**
     * Handles end of blocking action
     */
    void processCompletedBlockingAction();

signals:
    /**
     * Signal that starts salute (blocking action)
     */
    void saluteSoldierPixmap();

private:
    static const double MOVE_SPEED;
    static const double JUMP_SPEED;
    static const double Y_NAME_TEXT_OFFSET;
    static const double X_TEXT_OFFSET;
    std::vector<MovableVisual> createMovableVisuals();
    void connectBlockingActionCompletedOfMovableVisuals();
    SoldierPixmap *createSoldierPixmap(double x, double y);
    std::pair<double, double> calculateTextPosition(const QString &name, double x, double y) const;

    QTimer *timer;
    long id;
    double x;
    double y;
    bool isPerformingBlockingAction = false;
    SoldierPixmap * soldierPixmap;
    QGraphicsTextItem * nameText;
    std::vector<MovableVisual> movableVisuals;
};


#endif //SOLDIERAPP_SOLDIERVISUAL_H
