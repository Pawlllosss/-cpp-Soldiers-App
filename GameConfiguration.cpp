#include <QtCore/QJsonArray>
#include "GameConfiguration.h"

GameConfiguration::GameConfiguration(const std::vector<Soldier> &soldiers, const Map &map) : soldiers(soldiers),
                                                                                             map(map) {
}

//TODO: provide soldiers configuration
GameConfiguration::GameConfiguration(const QJsonObject &jsonGameConfiguration)
        : map(jsonGameConfiguration["map"].toObject()) {
}

QJsonObject GameConfiguration::convertToJson() {
    QJsonObject jsonConfiguration;
    QJsonObject jsonMap = map.convertToJson();
    jsonConfiguration["map"] = jsonMap;
    QJsonArray jsonSoldiers = convertSoldiersToJsonArray();
    jsonConfiguration["soldiers"] = jsonSoldiers;

    return jsonConfiguration;
}

QJsonArray GameConfiguration::convertSoldiersToJsonArray() {
    QJsonArray jsonSoldiers;

    foreach (auto soldier, soldiers) {
            QJsonObject jsonSoldier = soldier.convertToJson();
            jsonSoldiers.push_back(jsonSoldier);
    }

    return jsonSoldiers;
}
