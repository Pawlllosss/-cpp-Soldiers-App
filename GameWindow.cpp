#include "GameWindow.h"
#include "./ui_GameWindow.h"
#include "graphic/SoldierGraphic.h"
#include "graphic/BulletGraphic.h"
#include "graphic/GrenadeGraphic.h"
#include "graphic/ExplosionGraphic.h"
#include <QDebug>

GameWindow::GameWindow(const SoldierModel &soldierModel, const Map &map, QWidget *parent) : soldierModel(soldierModel), map(map),
                                                                                    QDialog(parent),
                                                                                    ui(new Ui::GameWindow),
                                                                                    graphicsScene(new QGraphicsScene) {
    ui->setupUi(this);
    ui->soldiersTable->setModel(&this->soldierModel);
    graphicsScene->setSceneRect(0, 0, 800, 600);
    ui->graphicsView->setScene(graphicsScene);
    connect(ui->shootButton, SIGNAL(clicked()), this, SLOT(createBullet()));
    connect(ui->grenadeButton, SIGNAL(clicked()), this, SLOT(createGrenade()));
    setBackgroundColor();
    displaySoldiers();
}

GameWindow::~GameWindow() {
    delete ui;
    delete graphicsScene;
    //TODO clean items from scene or is it done automatically?
}
void GameWindow::displaySoldiers() {
    double x = getHorizontalCenterPosition();
    const std::vector<Soldier> &soldiers = soldierModel.getSoldiers();

    foreach (auto Soldier, soldiers) {
        auto *soldierGraphic = new SoldierGraphic;
        soldierGraphic->setPos(x, getBottomPosition());
        x += 80;
        graphicsScene->addItem(soldierGraphic);
    }
}

void GameWindow::setBackgroundColor() {
    QColor backgroundColor(map.red, map.green, map.blue);
    QBrush backgroundBrush(backgroundColor);
    graphicsScene->setBackgroundBrush(backgroundBrush);
}

void GameWindow::createBullet() {
    auto bullet = new BulletGraphic();
    bullet->setPos(getHorizontalCenterPosition(),getBottomPosition());
    graphicsScene->addItem(bullet);
}

void GameWindow::createGrenade() {
    auto grenade = new GrenadeGraphic(getHorizontalCenterPosition(), getBottomPosition());
    connect(grenade, &GrenadeGraphic::explode, this, &GameWindow::createExplosion);
    graphicsScene->addItem(grenade);
}

void GameWindow::createExplosion(double x, double y) {
    auto explosion = new ExplosionGraphic(x, y);
    graphicsScene->addItem(explosion);
}

double GameWindow::getHorizontalCenterPosition() const {
    return graphicsScene->sceneRect().width() / 2.0;
}

double GameWindow::getBottomPosition() const {
    return graphicsScene->sceneRect().height();
}
