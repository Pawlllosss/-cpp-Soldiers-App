#ifndef SOLDIERAPP_MAP_H
#define SOLDIERAPP_MAP_H


#include <QtCore/QJsonObject>

struct Map {
    Map(int red, int green, int blue);
    Map(const QJsonObject& jsonMap);


    int red;
    int green;
    int blue;

    QJsonObject convertToJson();
};

#endif //SOLDIERAPP_MAP_H
