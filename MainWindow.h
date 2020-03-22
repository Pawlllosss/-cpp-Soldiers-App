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
    void addSoldier(const Soldier &soldier);
    void deleteSoldiers();
    void saveGameConfiguration();
    void loadGameConfiguration();

private:
    Map getMapFromSliders() const;
    int getValueFromSlider(QSlider *qSlider) const;
    std::vector<Soldier> getSoldiersFromModel();
    void setGameConfiguration(const GameConfiguration &configuration);
    GameConfiguration getGameConfigurationFromFile(QFile &file) const;
    void deleteSelectedSoldiers(const QModelIndexList &selectedRows);

    static const QString SETTINGS_FILE_NAME;
    Ui::MainWindow *ui;
    AddSoldierDialog addSoldierDialog;
    SoldierModel soldierModel;

    RankRepository rankRepository;
};

#endif // SOLDIER_APP_MAINWINDOW_H
