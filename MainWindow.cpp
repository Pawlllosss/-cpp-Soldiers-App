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
long MainWindow::SOLDER_ID_SEQUENCE = 1;

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
    addSoldierDialog.exec();
}

void MainWindow::addSoldier(Soldier soldier) {
    soldier.setId(SOLDER_ID_SEQUENCE);
    SOLDER_ID_SEQUENCE++;
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
    //TODO: block it when no soldiers added
    hide();
    GameWindow gameWindow(soldierModel, getMapFromSliders());
    gameWindow.exec();
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

    foreach (auto soldier, soldiers) {
        addSoldier(soldier);
    }
}

void MainWindow::setMapSlidersValues(const Map &map) const {
    ui->redSlider->setValue(map.red);
    ui->greenSlider->setValue(map.green);
    ui->blueSlider->setValue(map.blue);
}

void MainWindow::deleteSelectedSoldiers(const QModelIndexList &selectedRows) {
    foreach (QModelIndex index, selectedRows) {
        const int row = index.row();
        soldierModel.deleteSoldier(row);
    }
}
