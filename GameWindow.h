#ifndef SOLDIERAPP_GAMEWINDOW_H
#define SOLDIERAPP_GAMEWINDOW_H

#include <QtCore/QtGlobal>
#include <QtCore/QArgument>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGraphicsScene>
#include "Soldier.h"
#include "Map.h"
#include "SoldierModel.h"

QT_BEGIN_NAMESPACE
namespace Ui { class GameWindow; }
QT_END_NAMESPACE

class GameWindow : public QDialog
{
    Q_OBJECT

public:
    GameWindow(const SoldierModel &soldierModel, const Map &map, QWidget *parent = nullptr);
    ~GameWindow();

private slots:
    void createBullet();
    void createGrenade();
    void createExplosion(const double x, const double y);

private:
    void displaySoldiers();
    void setBackgroundColor();
    double inline getHorizontalCenterPosition() const;
    double inline getBottomPosition() const;

    Ui::GameWindow *ui;
    QGraphicsScene *graphicsScene;
    SoldierModel soldierModel;
    Map map;
};

#endif //SOLDIERAPP_GAMEWINDOW_H
