#ifndef SOLDIERAPP_SOLDIERVISUAL_H
#define SOLDIERAPP_SOLDIERVISUAL_H



#include <QtWidgets/QLabel>
#include <QtCore/QTimer>
#include "SoldierPixmap.h"
#include "MovableVisual.h"

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

    static const double MOVE_SPEED;
    static const double JUMP_SPEED;
    static const double Y_NAME_TEXT_OFFSET;
    static const double X_TEXT_OFFSET;

public slots:
    void processCompletedBlockingAction();

signals:
    void saluteSoldierPixmap();

private:
    std::vector<MovableVisual> createMovableVisuals();
    void connectBlockingActionCompletedOfMovableVisuals();
    SoldierPixmap *createSoldierPixmap(const double x, const double y);
    std::pair<double, double> calculateTextPosition(const QString &name, const double x, const double y) const;

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
