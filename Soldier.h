#ifndef SOLDIERAPP_SOLDIER_H
#define SOLDIERAPP_SOLDIER_H

#include <QtCore/QString>
#include "RankDescription.h"

class Soldier {
public:
    static Soldier fromJson(const QJsonObject& soldierJson);

    Soldier(const QString &firstName, const QString &lastName, const RankDescription &rank);

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
