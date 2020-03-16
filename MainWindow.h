#ifndef SOLDIER_APP_MAINWINDOW_H
#define SOLDIER_APP_MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets/QSlider>
#include <QFile>
#include "Map.h"
#include "GameConfiguration.h"

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
    void saveGameConfiguration();
    void loadGameConfiguration();

private:
    Map getMapFromSliders() const;
    int getValueFromSlider(QSlider *qSlider) const;

    static const QString SETTINGS_FILE_NAME;

    Ui::MainWindow *ui;

    GameConfiguration getGameConfigurationFromFile(QFile &file) const;

    void setGameConfiguration(const GameConfiguration &configuration);
};


#endif // SOLDIER_APP_MAINWINDOW_H
