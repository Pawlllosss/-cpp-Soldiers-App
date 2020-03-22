#ifndef SOLDIERAPP_SOLDIER_H
#define SOLDIERAPP_SOLDIER_H

#include <QtCore/QString>
#include "Rank.h"

class Soldier {
public:
    Soldier(const QString &firstName, const QString &lastName, const Rank &rank);

    const QString &getFirstName() const;
    void setFirstName(const QString &firstName);
    const QString &getLastName() const;
    void setLastName(const QString &lastName);
    const Rank &getRank() const;
    void setRank(const Rank &rank);
    QJsonObject convertToJson();

private:
    QString firstName;
    QString lastName;

    Rank rank;
};

#endif //SOLDIERAPP_SOLDIER_H
