#include <QtCore/QDebug>
#include <QtCore/QFile>
#include <QtWidgets/QMessageBox>
#include <QtCore/QJsonDocument>
#include "MainWindow.h"
#include "./ui_MainWindow.h"
#include "Map.h"
#include "GameConfiguration.h"
#include "AddSoldierDialog.h"
#include "GameWindow.h"

const QString MainWindow::SETTINGS_FILE_NAME = QString("settings.json");
long MainWindow::SOLDIER_ID_SEQUENCE = 1;
long MainWindow::MAX_SOLDIERS = 7;

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->soldiersTable->setModel(&soldierModel);
    addSoldierDialog.setAvailableRanks(rankRepository.getRanks());
    connect(ui->addSoldierButton, SIGNAL(clicked()), this, SLOT(showAddSoldierDialog()));
    connect(ui->deleteSoldierButton, SIGNAL(clicked()), this, SLOT(deleteSoldiers()));
    connect(ui->saveButton, SIGNAL(clicked()), this, SLOT(saveGameConfiguration()));
    connect(ui->loadButton, SIGNAL(clicked()), this, SLOT(loadGameConfiguration()));
    connect(ui->startButton, SIGNAL(clicked()), this, SLOT(startGame()));
    connect(&addSoldierDialog, &AddSoldierDialog::sendAddedSoldier, this, &MainWindow::addSoldier);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::showAddSoldierDialog() {
    if (!isEqualOrExceedsMaxSoldiersCount()) {
        addSoldierDialog.exec();
    } else {
        QMessageBox::warning(this, tr("Too many soldiers!"), "There can be at most " + QString::number(MAX_SOLDIERS) + " in the game!");
    }
}

bool MainWindow::isEqualOrExceedsMaxSoldiersCount() const {
    return soldierModel.rowCount() >= MAX_SOLDIERS;
}

void MainWindow::addSoldier(Soldier soldier) {
    soldier.setId(SOLDIER_ID_SEQUENCE);
    SOLDIER_ID_SEQUENCE++;
    soldierModel.addSoldier(soldier);
}

void MainWindow::deleteSoldiers() {
    const QItemSelectionModel *selectionModel = ui->soldiersTable->selectionModel();
    const QModelIndexList &selectedRows = selectionModel->selectedRows();

    deleteSelectedSoldiers(selectedRows);
}

void MainWindow::saveGameConfiguration() {
    QFile file(SETTINGS_FILE_NAME);

    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::information(this, tr("Unable to write to file"), file.errorString());
        return;
    }

    std::vector<Soldier> soldiers = soldierModel.getSoldiers();
    Map map = getMapFromSliders();
    GameConfiguration gameConfiguration(soldiers, map);
    QJsonObject gameConfigurationJson = gameConfiguration.convertToJson();
    QJsonDocument gameConfigurationJsonDocument(gameConfigurationJson);

    file.write(gameConfigurationJsonDocument.toJson());
}

void MainWindow::loadGameConfiguration() {
    QFile file(SETTINGS_FILE_NAME);

    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(this, tr("Unable to load file"), file.errorString());
        return;
    }

    GameConfiguration gameConfiguration = getGameConfigurationFromFile(file);
    setGameConfiguration(gameConfiguration);
}

void MainWindow::startGame() {
    if (soldierModel.rowCount() > MAX_SOLDIERS) {
        QMessageBox::warning(this, tr("Too many soldiers!"), "There can be at most " + QString::number(MAX_SOLDIERS) + " in the game!");
    } else if (!atLeastOneSoldierAdded()) {
        QMessageBox::warning(this, tr("No soldier added!"), "You must add at least one soldier to the game!");
    } else {
        hide();
        GameWindow gameWindow(soldierModel, getMapFromSliders());
        gameWindow.exec();
    }
}

bool MainWindow::atLeastOneSoldierAdded() {
    return soldierModel.rowCount() > 0;
}

Map MainWindow::getMapFromSliders() const {
    int redValue = getValueFromSlider(ui->redSlider);
    int greenValue = getValueFromSlider(ui->greenSlider);
    int blueValue = getValueFromSlider(ui->blueSlider);

    return Map(redValue, greenValue, blueValue);
}

int MainWindow::getValueFromSlider(QSlider *qSlider) const {
    return qSlider->value();
}

GameConfiguration MainWindow::getGameConfigurationFromFile(QFile &file) const {
    QByteArray byteArray = file.readAll();
    QJsonDocument gameConfigurationJsonDocument = QJsonDocument::fromJson(byteArray);
    QJsonObject gameConfigurationJson = gameConfigurationJsonDocument.object();

    return GameConfiguration::fromJson(gameConfigurationJson);
}

void MainWindow::setGameConfiguration(const GameConfiguration &configuration) {
    const Map &map = configuration.map;
    const std::vector<Soldier> & soldiers = configuration.soldiers;
    setMapSlidersValues(map);
    soldierModel.clear();

    for (auto soldier : soldiers) {
        addSoldier(soldier);
    }
}

void MainWindow::setMapSlidersValues(const Map &map) const {
    ui->redSlider->setValue(map.red);
    ui->greenSlider->setValue(map.green);
    ui->blueSlider->setValue(map.blue);
}

void MainWindow::deleteSelectedSoldiers(const QModelIndexList &selectedRows) {
    for (QModelIndex index : selectedRows) {
        const int row = index.row();
        soldierModel.deleteSoldier(row);
    }
}
