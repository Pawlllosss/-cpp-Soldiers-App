#ifndef SOLDIERAPP_RANKDESCRIPTION_H
#define SOLDIERAPP_RANKDESCRIPTION_H

#include <QtCore/QString>
#include <QtCore/QMetaType>
#include "Rank.h"

/**
 * Represents rank with name and numeric value
 */
struct RankDescription {

    /**
     *  Converts json representation to RankDescription
     *
     * @param rankDescriptionJson rank represented as json
     * @return RankDescription
     */
    static RankDescription fromJson(const QJsonObject& rankDescriptionJson);

    RankDescription() = default;

    RankDescription(const QString &name, Rank rank);
    RankDescription(const char *name, Rank rank);

    /**
     *
     * @return QJsonObject - RankDescription as json object
     */
    QJsonObject convertToJson();

    QString name;
    Rank rank;
};

Q_DECLARE_METATYPE(RankDescription)
#endif //SOLDIERAPP_RANKDESCRIPTION_H
