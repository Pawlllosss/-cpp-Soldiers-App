#include <QtCore/QJsonObject>
#include "RankDescription.h"
#include <qdebug.h>

RankDescription RankDescription::fromJson(const QJsonObject& rankDescriptionJson) {
    QString name = rankDescriptionJson["name"].toString();
    Rank rank = static_cast<Rank>(rankDescriptionJson["value"].toInt());

    return RankDescription(name, rank);
}

RankDescription::RankDescription(const QString &name, Rank rank) : name(name), rank(rank) {
}

RankDescription::RankDescription(const char *name, Rank rank) : RankDescription(QString(name), rank) {
}

QJsonObject RankDescription::convertToJson() {
    QJsonObject jsonRank;
    jsonRank["name"] = name;
    jsonRank["value"] = rank;

    return jsonRank;
}
