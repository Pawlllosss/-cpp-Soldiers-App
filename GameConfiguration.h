#ifndef SOLDIERAPP_GAMECONFIGURATION_H
#define SOLDIERAPP_GAMECONFIGURATION_H


#include <list>
#include <QtCore/QJsonObject>
#include "Map.h"
#include "Soldier.h"

/**
 * Structure that stores configuration of game. Map and soldiers.
 */
struct GameConfiguration {

    /**
     *  Converts json representation to GameConfiguration
     *
     * @param gameConfiguration rank represented as json
     * @return GameConfiguration
     */
    static GameConfiguration fromJson(const QJsonObject& jsonGameConfiguration);

    GameConfiguration(const std::vector<Soldier>& soldiers, const Map& map);

    /**
    *
    * @return QJsonObject - GameConfiguration
    */
    QJsonObject convertToJson();
    /**
    * Converts soldiers stored in GameConfiguration to json array
    * @return QJsonArray - Soldier as json array
    */
    QJsonArray convertSoldiersToJsonArray();

    std::vector<Soldier> soldiers;
    Map map;
};

#endif //SOLDIERAPP_GAMECONFIGURATION_H
