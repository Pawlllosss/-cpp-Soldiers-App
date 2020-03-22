#include "GameWindow.h"
#include "./ui_GameWindow.h"
#include "SoldierGraphic.h"

GameWindow::GameWindow(const std::vector<Soldier> &soldiers, const Map &map, QWidget *parent) : soldiers(soldiers), map(map),
                                                                                    QDialog(parent),
                                                                                    ui(new Ui::GameWindow),
                                                                                    graphicsScene(new QGraphicsScene) {
    ui->setupUi(this);
    ui->graphicsView->setScene(graphicsScene);
    setBackgroundColor();
    displaySoldiers();
}

GameWindow::~GameWindow() {
    delete ui;
    delete graphicsScene;
    //TODO clean items from scene or is it done automatically?
}

void GameWindow::displaySoldiers() {
    int x = 0;

    foreach (auto Soldier, soldiers) {
        auto *soldierGraphic = new SoldierGraphic;
        soldierGraphic->setPos(x, -200);
        x += 80;
        graphicsScene->addItem(soldierGraphic);
    }
}
void GameWindow::setBackgroundColor() {
    QColor backgroundColor(map.red, map.green, map.blue);
    QBrush backgroundBrush(backgroundColor);
    graphicsScene->setBackgroundBrush(backgroundBrush);
}