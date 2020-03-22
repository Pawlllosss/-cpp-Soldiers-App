#ifndef SOLDIERAPP_GAMECONFIGURATION_H
#define SOLDIERAPP_GAMECONFIGURATION_H


#include <list>
#include <QtCore/QJsonObject>
#include "Map.h"
#include "Soldier.h"

struct GameConfiguration {
    GameConfiguration(const std::vector<Soldier>& soldiers, const Map& map);
    GameConfiguration(const QJsonObject& jsonGameConfiguration);

    std::vector<Soldier> soldiers;
    Map map;

    QJsonObject convertToJson();

    QJsonArray convertSoldiersToJsonArray();
};

#endif //SOLDIERAPP_GAMECONFIGURATION_H
