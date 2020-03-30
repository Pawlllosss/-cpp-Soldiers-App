#include <QtCore/QJsonArray>
#include "GameConfiguration.h"

GameConfiguration GameConfiguration::fromJson(const QJsonObject &jsonGameConfiguration) {
    Map map = jsonGameConfiguration["map"].toObject();

    const QJsonArray &soldiersJson = jsonGameConfiguration["soldiers"].toArray();
    std::vector<Soldier> soldiers;

    for (QJsonValue soldierJsonValue : soldiersJson) {
        QJsonObject soldierJson = soldierJsonValue.toObject();
        Soldier soldier = Soldier::fromJson(soldierJson);
        soldiers.push_back(soldier);
    }

    return GameConfiguration(soldiers, map);
}

GameConfiguration::GameConfiguration(const std::vector<Soldier> &soldiers, const Map &map) : soldiers(soldiers),
                                                                                             map(map) {
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

    for (auto soldier : soldiers) {
            QJsonObject jsonSoldier = soldier.convertToJson();
            jsonSoldiers.push_back(jsonSoldier);
    }

    return jsonSoldiers;
}
