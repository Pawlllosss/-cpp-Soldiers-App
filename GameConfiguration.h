#ifndef SOLDIERAPP_GAMECONFIGURATION_H
#define SOLDIERAPP_GAMECONFIGURATION_H


#include <list>
#include <QtCore/QJsonObject>
#include "Map.h"
#include "Soldier.h"

struct GameConfiguration {
    static GameConfiguration fromJson(const QJsonObject& jsonGameConfiguration);

    GameConfiguration(const std::vector<Soldier>& soldiers, const Map& map);

    QJsonObject convertToJson();
    QJsonArray convertSoldiersToJsonArray();

    std::vector<Soldier> soldiers;
    Map map;
};

#endif //SOLDIERAPP_GAMECONFIGURATION_H
