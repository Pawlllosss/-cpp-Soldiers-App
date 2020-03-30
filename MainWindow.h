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

/**
 * Class that renders main window shown after application start. Is responsible for preparing widgets
 * for game configuration: map color sliders, soldiers names/ranks table, invoking dialog for adding new soldiers and
 * loading/saving game configuration from/to settings.json file.
 */
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
    bool isEqualOrExceedsMaxSoldiersCount() const;
    bool atLeastOneSoldierAdded();
    Map getMapFromSliders() const;
    int getValueFromSlider(QSlider *qSlider) const;
    GameConfiguration getGameConfigurationFromFile(QFile &file) const;
    void setGameConfiguration(const GameConfiguration &configuration);
    void setMapSlidersValues(const Map &map) const;
    void deleteSelectedSoldiers(const QModelIndexList &selectedRows);

    Ui::MainWindow *ui;
    AddSoldierDialog addSoldierDialog;
    SoldierModel soldierModel;
    RankRepository rankRepository;
};

#endif // SOLDIER_APP_MAINWINDOW_H
