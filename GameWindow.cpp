#include "GameWindow.h"
#include "./ui_GameWindow.h"
#include "graphic/SoldierPixmap.h"
#include "graphic/BulletGraphic.h"
#include "graphic/GrenadeGraphic.h"
#include "graphic/ExplosionGraphic.h"
#include <QDebug>

GameWindow::GameWindow(const SoldierModel &soldierModel, const Map &map, QWidget *parent) : soldierModel(soldierModel),
                                                                                            map(map),
                                                                                            QDialog(parent),
                                                                                            ui(new Ui::GameWindow),
                                                                                            graphicsScene(new QGraphicsScene)
                                                                                            {
    ui->setupUi(this);
    ui->soldiersTable->setModel(&this->soldierModel);
    graphicsScene->setSceneRect(0, 0, 800, 600);
    ui->graphicsView->setScene(graphicsScene);
    pushButtonMinimumRankMapping = getPushButtonMinimumRankMapping();

    QItemSelectionModel *soldiersTableSelectionModel = ui->soldiersTable->selectionModel();
    connect(soldiersTableSelectionModel, &QItemSelectionModel::selectionChanged, this, &GameWindow::handleButtonsAvailability);
    connect(ui->shootButton, SIGNAL(clicked()), this, SLOT(shootBullets()));
    connect(ui->grenadeButton, SIGNAL(clicked()), this, SLOT(createGrenade()));
    connect(ui->jumpButton, SIGNAL(clicked()), this, SLOT(jumpSoldier()));
    connect(ui->saluteButton, SIGNAL(clicked()), this, SLOT(salute()));
    connect(ui->moveUpButton, SIGNAL(clicked()), this, SLOT(moveSoldierUp()));
    connect(ui->moveDownButton, SIGNAL(clicked()), this, SLOT(moveSoldierDown()));
    setBackgroundColor();
    createSoldiersVisual(soldierModel.getSoldiers());
    displaySoldiers();
}

GameWindow::~GameWindow() {
    delete ui;
    delete graphicsScene;
}

std::map<QPushButton *, Rank> GameWindow::getPushButtonMinimumRankMapping() {
    std::map<QPushButton *, Rank> pushButtonMinimumRankMapping;
    pushButtonMinimumRankMapping.insert(std::pair(ui->moveUpButton, PRIVATE));
    pushButtonMinimumRankMapping.insert(std::pair(ui->moveDownButton, PRIVATE));
    pushButtonMinimumRankMapping.insert(std::pair(ui->saluteButton, PRIVATE));
    pushButtonMinimumRankMapping.insert(std::pair(ui->shootButton, CORPORAL));
    pushButtonMinimumRankMapping.insert(std::pair(ui->grenadeButton, SERGEANT));
    pushButtonMinimumRankMapping.insert(std::pair(ui->jumpButton, LIEUTENANT));

    return pushButtonMinimumRankMapping;
}

void GameWindow::createSoldiersVisual(const std::vector<Soldier> &soldiers) {
    size_t numberOfSoldiers = soldiers.size();

    double xCenter = getHorizontalCenterPosition();
    double distanceBetweenSoldiers = SoldierPixmap::PIXMAP_WIDTH * 2;
    size_t distanceMultiplier = numberOfSoldiers / 2;
    size_t xSoldierPosition =
            xCenter - SoldierPixmap::PIXMAP_WIDTH / 2 - (distanceBetweenSoldiers * distanceMultiplier);
    size_t ySoldierPosition = getBottomPosition();

    for (auto soldier : soldiers) {
        long soldierId = soldier.getId();
        QString soldierName = soldier.getFirstName() + " " + soldier.getLastName();
        auto *soldierVisual = new SoldierVisual(soldierId, soldierName, xSoldierPosition, ySoldierPosition);
        soldiersVisual.push_back(soldierVisual);
        xSoldierPosition += distanceBetweenSoldiers;
    }
}

void GameWindow::displaySoldiers() {
    for (auto soldier : soldiersVisual) {
        SoldierPixmap *item = soldier->getSoldierPixmap();
        graphicsScene->addItem(soldier->getNameText());
        graphicsScene->addItem(item);
    }
}

void GameWindow::setBackgroundColor() {
    QColor backgroundColor(map.red, map.green, map.blue);
    QBrush backgroundBrush(backgroundColor);
    graphicsScene->setBackgroundBrush(backgroundBrush);
}

std::vector<SoldierVisual *> GameWindow::getSelectedSoldiersVisualOfEligibleToPerformOrder() {
    const std::vector<Soldier> &selectedSoldiers = getSelectedSoldiers();
    const std::vector<Soldier> & eligibleSoldiers = getEligibleSoldierToPerformOrder(selectedSoldiers);
    const std::vector<long> &eligibleSoldiersIds = convertSoldiersToIds(eligibleSoldiers);

    return getSoldierVisualById(eligibleSoldiersIds);
}

std::vector<Soldier> GameWindow::getEligibleSoldierToPerformOrder(const std::vector<Soldier> &selectedSoldiers) {
    std::vector<Soldier> eligibleSoldiers;
    const Rank maxSelectedRank = getMaxRankOfSoldiers(selectedSoldiers);
    bool canOrderBiggestRank = ui->orderBiggestRankCheckbox->isChecked();
    bool canOrderLowerRank = ui->orderLowerRankCheckbox->isChecked();

    if (canOrderBiggestRank) {
        std::copy_if(selectedSoldiers.begin(), selectedSoldiers.end(), std::back_inserter(eligibleSoldiers),
                     [&maxSelectedRank](const Soldier &soldier) { return soldier.getRank().rank == maxSelectedRank; });
    }

    if (canOrderLowerRank) {
        std::copy_if(selectedSoldiers.begin(), selectedSoldiers.end(), std::back_inserter(eligibleSoldiers),
                     [&maxSelectedRank](const Soldier &soldier) { return soldier.getRank().rank < maxSelectedRank; });
    }

    return eligibleSoldiers;
}

std::vector<SoldierVisual *> GameWindow::getSoldierVisualById(const std::vector<long> &soldiersId) {
    std::vector<SoldierVisual *> soldiersVisualWithMatchingId;

    for (auto *soldierVisual : soldiersVisual) {
        if (idMatches(soldierVisual, soldiersId)) {
            soldiersVisualWithMatchingId.push_back(soldierVisual);
        }
    }

    return soldiersVisualWithMatchingId;
}

bool GameWindow::idMatches(SoldierVisual *soldierVisual, std::vector<long> ids) {
    long soldierId = soldierVisual->getId();

    for (auto id : ids) {
        if (soldierId == id) {
            return true;
        }
    }
    return false;
}

std::vector<long> GameWindow::convertSoldiersToIds(const std::vector<Soldier> &selectedSoldiers) const {
    std::vector<long> ids;

    for (auto soldier : selectedSoldiers) {
        long id = soldier.getId();
        ids.push_back(id);
    }

    return ids;
}

std::vector<Soldier> GameWindow::getSelectedSoldiers() const {
    const QItemSelectionModel *selectionModel = ui->soldiersTable->selectionModel();
    const QModelIndexList &selectedRows = selectionModel->selectedRows();
    std::vector<Soldier> selectedSoldiers;

    for (QModelIndex index : selectedRows) {
        const int row = index.row();
        const Soldier &soldier = soldierModel.getSoldierByRow(row);
        selectedSoldiers.push_back(soldier);
    }

    return selectedSoldiers;
}

void GameWindow::shootBullets() {
    const std::vector<SoldierVisual *> &soldiersVisual = getSelectedSoldiersVisualOfEligibleToPerformOrder();

    for (auto *soldierVisual : soldiersVisual) {
        SoldierPixmap *soldierPixmap = soldierVisual->getSoldierPixmap();
        auto bullet = new BulletGraphic();
        bullet->setPos(soldierPixmap->x() + SoldierPixmap::PIXMAP_WIDTH / 4, soldierPixmap->y());
        graphicsScene->addItem(bullet);
    }
}

void GameWindow::createGrenade() {
    const std::vector<SoldierVisual *> &soldiersVisual = getSelectedSoldiersVisualOfEligibleToPerformOrder();

    for (auto *soldierVisual : soldiersVisual) {
        SoldierPixmap *soldierPixmap = soldierVisual->getSoldierPixmap();
        auto grenade = new GrenadeGraphic(soldierPixmap->x() + SoldierPixmap::PIXMAP_WIDTH / 4, soldierPixmap->y());
        connect(grenade, &GrenadeGraphic::explode, this, &GameWindow::createExplosion);
        graphicsScene->addItem(grenade);
    }
}

void GameWindow::createExplosion(double x, double y) {
    auto explosion = new ExplosionGraphic(x, y);
    graphicsScene->addItem(explosion);
}

void GameWindow::jumpSoldier() {
    const std::vector<SoldierVisual *> &soldiersVisual = getSelectedSoldiersVisualOfEligibleToPerformOrder();

    for (auto *soldierVisual : soldiersVisual) {
        soldierVisual->jump();
    }
}

void GameWindow::salute() {
    const std::vector<SoldierVisual *> &soldiersVisual = getSelectedSoldiersVisualOfEligibleToPerformOrder();
    for (auto *soldierVisual : soldiersVisual) {
        soldierVisual->salute();
    }
}

void GameWindow::moveSoldierUp() {
    const std::vector<Soldier> &selectedSoldiers = getSelectedSoldiers();
    const std::vector<Soldier> & eligibleSoldiers = getEligibleSoldierToPerformOrder(selectedSoldiers);
    std::vector<SoldierVisual *> soldierVisuals;

    for (auto &soldier : eligibleSoldiers) {
        Rank rank = soldier.getRank().rank;
        double yDiff = moveDistanceBasedOnRank(rank);
        SoldierVisual *soldierVisual = getSoldierVisual(soldier);

        soldierVisual->move(0, -yDiff);
    }
}

SoldierVisual *GameWindow::getSoldierVisual(const Soldier &soldier) {
    std::vector<long> soldierId;
    soldierId.push_back(soldier.getId());

    std::vector<SoldierVisual *> vector = getSoldierVisualById(soldierId);
    SoldierVisual *&soldierVisual = vector.at(0);
    return soldierVisual;
}

double GameWindow::moveDistanceBasedOnRank(Rank rank) {
    switch (rank) {
        case PRIVATE:
        case CORPORAL:
            return 10;
        case SERGEANT:
            return 20;
        case LIEUTENANT:
        case CAPTAIN:
            return 30;
        default:
            return 10;
    }
}

void GameWindow::moveSoldierDown() {
    const std::vector<Soldier> &selectedSoldiers = getSelectedSoldiers();
    const std::vector<Soldier> & eligibleSoldiers = getEligibleSoldierToPerformOrder(selectedSoldiers);
    std::vector<SoldierVisual *> soldierVisuals;

    for (auto &soldier : eligibleSoldiers) {
        Rank rank = soldier.getRank().rank;
        double yDiff = moveDistanceBasedOnRank(rank);
        SoldierVisual *soldierVisual = getSoldierVisual(soldier);

        soldierVisual->move(0, yDiff);
    }
}

void GameWindow::handleButtonsAvailability(const QItemSelection& selected, const QItemSelection& deselected) {
    const std::vector<Soldier> selectedSoldiers = getSelectedSoldiers();
    const Rank maxSelectedRank = getMaxRankOfSoldiers(selectedSoldiers);

    for (auto mapping : pushButtonMinimumRankMapping) {
        Rank buttonMinimumRank = mapping.second;
        QPushButton *button = mapping.first;

        if (buttonMinimumRank <= maxSelectedRank) {
            button->setEnabled(true);
        } else {
            button->setEnabled(false);
        }
    }
}

Rank GameWindow::getMaxRankOfSoldiers(const std::vector<Soldier> &soldiers) {
    Rank maxRank = PRIVATE;

    for (auto soldier : soldiers) {
        Rank soldierRank = soldier.getRank().rank;
        maxRank = soldierRank > maxRank ? soldierRank : maxRank;
    }

    return maxRank;
}

double GameWindow::getHorizontalCenterPosition() const {
    return graphicsScene->sceneRect().width() / 2.0;
}

double GameWindow::getBottomPosition() const {
    return graphicsScene->sceneRect().height();
}
