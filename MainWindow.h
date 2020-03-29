#ifndef SOLDIER_APP_MAINWINDOW_H
#define SOLDIER_APP_MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets/QSlider>
#include <QFile>
#include "Map.h"
#include "GameConfiguration.h"
#include "AddSoldierDialog.h"
#include "SoldierModel.h"
#include "RankRepository.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void showAddSoldierDialog();
    void addSoldier(Soldier soldier);
    void deleteSoldiers();
    void saveGameConfiguration();
    void loadGameConfiguration();
    void startGame();

private:
    static long SOLDIER_ID_SEQUENCE;
    static long MAX_SOLDIERS;
    static const QString SETTINGS_FILE_NAME;
    Map getMapFromSliders() const;
    int getValueFromSlider(QSlider *qSlider) const;
    void setGameConfiguration(const GameConfiguration &configuration);
    GameConfiguration getGameConfigurationFromFile(QFile &file) const;
    void deleteSelectedSoldiers(const QModelIndexList &selectedRows);
    void setMapSlidersValues(const Map &map) const;
    bool atLeastOneSoldierAdded();
    bool isEqualOrExceedsMaxSoldiersCount() const;

    Ui::MainWindow *ui;
    AddSoldierDialog addSoldierDialog;
    SoldierModel soldierModel;
    RankRepository rankRepository;
};

#endif // SOLDIER_APP_MAINWINDOW_H
