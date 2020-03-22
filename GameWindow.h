#ifndef SOLDIERAPP_GAMEWINDOW_H
#define SOLDIERAPP_GAMEWINDOW_H

#include <QtCore/QtGlobal>
#include <QtCore/QArgument>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGraphicsScene>
#include "Soldier.h"
#include "Map.h"

QT_BEGIN_NAMESPACE
namespace Ui { class GameWindow; }
QT_END_NAMESPACE

class GameWindow : public QDialog
{
    Q_OBJECT

public:
    GameWindow(const std::vector<Soldier> &soldiers, const Map &map, QWidget *parent = nullptr);
    ~GameWindow();

signals:

private slots:

private:
    void displaySoldiers();
    void setBackgroundColor();

    Ui::GameWindow *ui;
    QGraphicsScene *graphicsScene;
    std::vector<Soldier> soldiers;
    Map map;
};

#endif //SOLDIERAPP_GAMEWINDOW_H
