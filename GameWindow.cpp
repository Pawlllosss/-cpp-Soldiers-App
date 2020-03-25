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
                                                                                            graphicsScene(
                                                                                                    new QGraphicsScene) {
    ui->setupUi(this);
    ui->soldiersTable->setModel(&this->soldierModel);
    graphicsScene->setSceneRect(0, 0, 800, 600);
    ui->graphicsView->setScene(graphicsScene);
    connect(ui->shootButton, SIGNAL(clicked()), this, SLOT(shootBullets()));
    connect(ui->grenadeButton, SIGNAL(clicked()), this, SLOT(createGrenade()));
    connect(ui->jumpButton, SIGNAL(clicked()), this, SLOT(jumpSoldier()));
    connect(ui->moveUpButton, SIGNAL(clicked()), this, SLOT(moveSoldierUp()));
    connect(ui->moveDownButton, SIGNAL(clicked()), this, SLOT(moveSoldierDown()));
    setBackgroundColor();
    createSoldiersVisual(soldierModel.getSoldiers());
    displaySoldiers();
}

GameWindow::~GameWindow() {
    delete ui;
    delete graphicsScene;
    //TODO clean items from scene or is it done automatically?
}

void GameWindow::createSoldiersVisual(const std::vector<Soldier> &soldiers) {
    size_t numberOfSoldiers = soldiers.size();

    double xCenter = getHorizontalCenterPosition();
    double distanceBetweenSoldiers = SoldierPixmap::PIXMAP_WIDTH * 2;
    size_t distanceMultiplier = numberOfSoldiers / 2;
    size_t xSoldierPosition =
            xCenter - SoldierPixmap::PIXMAP_WIDTH / 2 - (distanceBetweenSoldiers * distanceMultiplier);
    size_t ySoldierPosition = getBottomPosition();

    foreach (auto soldier, soldiers) {
        long soldierId = soldier.getId();
        auto *soldierVisual = new SoldierVisual(soldierId, xSoldierPosition, ySoldierPosition);
        soldiersVisual.push_back(soldierVisual);
        xSoldierPosition += distanceBetweenSoldiers;
    }
}

void GameWindow::displaySoldiers() {
    foreach (auto soldier, soldiersVisual) {
        SoldierPixmap *item = soldier->getSoldierPixmap();
        graphicsScene->addItem(item);
    }
}

void GameWindow::setBackgroundColor() {
    QColor backgroundColor(map.red, map.green, map.blue);
    QBrush backgroundBrush(backgroundColor);
    graphicsScene->setBackgroundBrush(backgroundBrush);
}

std::vector<SoldierVisual *> GameWindow::getSelectedSoldiersVisual() {
    std::vector<long> soldiersId = getSelectedSoldiersId();
    std::vector<SoldierVisual *> selectedSoldiersVisual;

    foreach (auto *soldierVisual, soldiersVisual) {
        if (isSelected(soldierVisual ,soldiersId)) {
            selectedSoldiersVisual.push_back(soldierVisual);
        }
    }

    return selectedSoldiersVisual;
}

bool GameWindow::isSelected(SoldierVisual *soldierVisual, std::vector<long> ids) {
    long soldierId = soldierVisual->getId();

    foreach (auto id, ids) {
        if (soldierId == id) {
            return true;
        }
    }
    return false;
}

std::vector<long> GameWindow::getSelectedSoldiersId() {
    const QItemSelectionModel *selectionModel = ui->soldiersTable->selectionModel();
    const QModelIndexList &selectedRows = selectionModel->selectedRows();
    std::vector<long> ids;

    foreach (QModelIndex index, selectedRows) {
        const int row = index.row();
        const Soldier &soldier = soldierModel.getSoldierByRow(row);
        ids.push_back(soldier.getId());
    }

    return ids;
}

void GameWindow::shootBullets() {
    const std::vector<SoldierVisual *> &soldiersVisual = getSelectedSoldiersVisual();

    foreach (auto *soldierVisual, soldiersVisual) {
        SoldierPixmap *soldierPixmap = soldierVisual->getSoldierPixmap();
        auto bullet = new BulletGraphic();
        bullet->setPos(soldierPixmap->x() + SoldierPixmap::PIXMAP_WIDTH / 4, soldierPixmap->y());
        graphicsScene->addItem(bullet);
    }
}

void GameWindow::createGrenade() {
    const std::vector<SoldierVisual *> &soldiersVisual = getSelectedSoldiersVisual();

    foreach (auto *soldierVisual, soldiersVisual) {
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
    const std::vector<SoldierVisual *> &soldiersVisual = getSelectedSoldiersVisual();

    foreach (auto *soldierVisual, soldiersVisual) {
        soldierVisual->jump();
    }
}

void GameWindow::moveSoldierUp() {
    const std::vector<SoldierVisual *> &soldiersVisual = getSelectedSoldiersVisual();

    foreach (auto *soldierVisual, soldiersVisual) {
        soldierVisual->move(0, -50);
    }
}

void GameWindow::moveSoldierDown() {
    const std::vector<SoldierVisual *> &soldiersVisual = getSelectedSoldiersVisual();

    foreach (auto *soldierVisual, soldiersVisual) {
        soldierVisual->move(0, 50);
    }
}

double GameWindow::getHorizontalCenterPosition() const {
    return graphicsScene->sceneRect().width() / 2.0;
}

double GameWindow::getBottomPosition() const {
    return graphicsScene->sceneRect().height();
}
