#ifndef SOLDIERAPP_SOLDIER_H
#define SOLDIERAPP_SOLDIER_H

#include <QtCore/QString>
#include "RankDescription.h"

/**
 * Represents information about soldier his first name, last name and rank.
 */
class Soldier {
public:

    /**
    * Converts json representation to Soldier
    *
    * @param soldierJson soldier represented as json
    * @return Soldier
    */
    static Soldier fromJson(const QJsonObject& soldierJson);

    Soldier(const QString &firstName, const QString &lastName, const RankDescription &rank);

    /**
    * Converts Soldier to QJsonObject ready to write to file in json format.
    *
    * @return Soldier represented as QJsonObject
    */
    QJsonObject convertToJson();

    long getId() const;
    void setId(long id);
    const QString &getFirstName() const;
    void setFirstName(const QString &firstName);
    const QString &getLastName() const;
    void setLastName(const QString &lastName);
    const RankDescription &getRank() const;
    void setRank(const RankDescription &rank);

private:
    long id;
    QString firstName;
    QString lastName;
    RankDescription rank;
};

#endif //SOLDIERAPP_SOLDIER_H
