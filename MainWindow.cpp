#include <QtCore/QDebug>
#include <QtCore/QFile>
#include <QtWidgets/QMessageBox>
#include <QtCore/QJsonDocument>
#include "MainWindow.h"
#include "./ui_MainWindow.h"
#include "Map.h"
#include "GameConfiguration.h"
#include "AddSoldierDialog.h"

const QString MainWindow::SETTINGS_FILE_NAME = QString("settings.json");

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    connect(ui->addSoldierButton, SIGNAL(clicked()), this, SLOT(showAddSoldierDialog()));
    connect(ui->saveButton, SIGNAL(clicked()), this, SLOT(saveGameConfiguration()));
    connect(ui->loadButton, SIGNAL(clicked()), this, SLOT(loadGameConfiguration()));
    connect(&addSoldierDialog, &AddSoldierDialog::sendAddedSoldier, this, &MainWindow::addNewSoldier);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::showAddSoldierDialog() {
    addSoldierDialog.exec();
}

void MainWindow::addNewSoldier(const Soldier &soldier) {
    qDebug() << soldier.getFirstName();
    qDebug() << soldier.getLastName();
}

void MainWindow::saveGameConfiguration() {
    QFile file(SETTINGS_FILE_NAME);

    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::information(this, tr("Unable to write to file"), file.errorString());
        return;
    }

    Map map = getMapFromSliders();
    GameConfiguration gameConfiguration(map);
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

    return GameConfiguration(gameConfigurationJson);
}

void MainWindow::setGameConfiguration(const GameConfiguration &configuration) {
    const Map &map = configuration.map;
    ui->redSlider->setValue(map.red);
    ui->greenSlider->setValue(map.green);
    ui->blueSlider->setValue(map.blue);
}
