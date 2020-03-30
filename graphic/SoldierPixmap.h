#ifndef SOLDIERAPP_SOLDIERPIXMAP_H
#define SOLDIERAPP_SOLDIERPIXMAP_H

#include <QtWidgets/QGraphicsRectItem>

class SoldierPixmap: public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    const static double PIXMAP_WIDTH;
    SoldierPixmap(QGraphicsItem *parent = 0);

public slots:
    void salute();

signals:
    void blockingActionCompleted();

private slots:
    void endSalute();

private:
    QTimer *timer;
    QPixmap * standingSoldierPixmap;
    QPixmap * salutingSoldierPixmap;
    unsigned long jumpTime = 0;
    double xDestination;
    double yDestination;
    double moveSpeed;
    double jumpSpeed;
};


#endif //SOLDIERAPP_SOLDIERPIXMAP_H
