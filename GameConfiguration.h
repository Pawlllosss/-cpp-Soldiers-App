#ifndef SOLDIERAPP_GAMECONFIGURATION_H
#define SOLDIERAPP_GAMECONFIGURATION_H


#include <list>
#include <QtCore/QJsonObject>
#include "Map.h"

struct GameConfiguration {
    //TODO: soldiers will be implemented later
//    GameConfiguration(const std::list<Soldier>& soldiers, const Map& map);
    GameConfiguration(const Map &map);
    GameConfiguration(const QJsonObject& jsonGameConfiguration);

    //TODO: soldiers will be implemented later
//    std::list<Soldier> soldiers;
    Map map;

    QJsonObject convertToJson();
};


#endif //SOLDIERAPP_GAMECONFIGURATION_H
