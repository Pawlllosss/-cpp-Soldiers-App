#ifndef SOLDIERAPP_GAMEWINDOW_H
#define SOLDIERAPP_GAMEWINDOW_H

#include <QtCore/QtGlobal>
#include <QtCore/QArgument>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGraphicsScene>
#include "Soldier.h"
#include "Map.h"
#include "SoldierModel.h"
#include "graphic/SoldierVisual.h"

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
    void shootBullets();
    void createGrenade();
    void createExplosion(const double x, const double y);
    void moveSoldierUp();
    void moveSoldierDown();

private:
    void createSoldiersVisual(const std::vector<Soldier> &soldiers);
    void displaySoldiers();
    void setBackgroundColor();
    std::vector<long> getSelectedSoldiersId();
    SoldierPixmap *createSoldierPixmap(const size_t numberOfSoldiers);
    std::vector<SoldierVisual*> getSelectedSoldiersVisual();
    bool isSelected(SoldierVisual *soldierVisual, std::vector<long> ids);
    double inline getHorizontalCenterPosition() const;
    double inline getBottomPosition() const;

    Ui::GameWindow *ui;
    QGraphicsScene *graphicsScene;
    SoldierModel soldierModel;
    std::vector<SoldierVisual*> soldiersVisual;
    Map map;
};

#endif //SOLDIERAPP_GAMEWINDOW_H
