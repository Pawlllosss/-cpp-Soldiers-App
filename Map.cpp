#include "Map.h"

Map::Map(int red, int green, int blue): red(red), green(green), blue(blue) {
}

Map::Map(const QJsonObject &jsonMap) {
    red = jsonMap["red"].toInt();
    green = jsonMap["green"].toInt();
    blue = jsonMap["blue"].toInt();
}

QJsonObject Map::convertToJson() {
    QJsonObject jsonMap;
    jsonMap["red"] = red;
    jsonMap["green"] = green;
    jsonMap["blue"] = blue;

    return jsonMap;
}
