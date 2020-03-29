#ifndef SOLDIERAPP_GAMEWINDOW_H
#define SOLDIERAPP_GAMEWINDOW_H

#include <QtCore/QtGlobal>
#include <QtCore/QArgument>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGraphicsScene>
#include <QtCore/QItemSelection>
#include <set>
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
    void jumpSoldier();
    void salute();
    void moveSoldierUp();
    void moveSoldierDown();
    void handleButtonsAvailability(const QItemSelection& selected, const QItemSelection& deselected);

private:
    std::set<QPushButton*> getPushButtonsSet();
    std::map<QPushButton*, Rank> getPushButtonMinimumRankMapping();
    void createSoldiersVisual(const std::vector<Soldier> &soldiers);
    void displaySoldiers();
    void setBackgroundColor();
    std::vector<long> getSelectedSoldiersId();
    std::vector<SoldierVisual*> getSelectedSoldiersVisual();
    bool idMatches(SoldierVisual *soldierVisual, std::vector<long> ids);
    double inline getHorizontalCenterPosition() const;
    double inline getBottomPosition() const;

    Ui::GameWindow *ui;
    QGraphicsScene *graphicsScene;
    SoldierModel soldierModel;
    std::vector<SoldierVisual*> soldiersVisual;
    std::set<QPushButton*> pushButtons;
    std::map<QPushButton*, Rank> pushButtonMinimumRankMapping;
    Map map;

    std::vector<Soldier> getSelectedSoldiers() const;

    Rank getMaxRankOfSoldiers(const std::vector<Soldier> &soldiers);

    std::vector<SoldierVisual *> getSelectedSoldiersVisualOfEligibleToPerformOrder();

    std::vector<Soldier> getEligibleSoldierToPerformOrder(const std::vector<Soldier> &selectedSoldiers);

    std::vector<SoldierVisual *> getSoldierVisualById(const std::vector<long> &soldiersId);

    std::vector<long> convertSoldiersToIds(const std::vector<Soldier> &selectedSoldiers) const;
};

#endif //SOLDIERAPP_GAMEWINDOW_H
