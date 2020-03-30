#ifndef SOLDIERAPP_MAP_H
#define SOLDIERAPP_MAP_H


#include <QtCore/QJsonObject>

/**
 * Structure that describes map colors with use of the rgb paramaters.
 */
struct Map {
    Map(int red, int green, int blue);
    Map(const QJsonObject& jsonMap);

    /**
     * Converts Map to QJsonObject ready to write to file in json format.
     *
     * @return Map represented as QJsonObject
     */
    QJsonObject convertToJson();

    int red;
    int green;
    int blue;
};

#endif //SOLDIERAPP_MAP_H
