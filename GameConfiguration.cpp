#include "GameConfiguration.h"

GameConfiguration::GameConfiguration(const Map &map) : map(map) {

}

GameConfiguration::GameConfiguration(const QJsonObject &jsonGameConfiguration)
        : map(jsonGameConfiguration["map"].toObject()) {
}

QJsonObject GameConfiguration::convertToJson() {
    QJsonObject jsonConfiguration;
    QJsonObject jsonMap = map.convertToJson();
    jsonConfiguration["map"] = jsonMap;

    return jsonConfiguration;
}
