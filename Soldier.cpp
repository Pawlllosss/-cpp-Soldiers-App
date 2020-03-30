#include <QtCore/QJsonObject>
#include "Soldier.h"

Soldier Soldier::fromJson(const QJsonObject& soldierJson) {
    QString firstName = QString(soldierJson["firstName"].toString());
    QString lastName = soldierJson["lastName"].toString();
    RankDescription rankDescription = RankDescription::fromJson(soldierJson["rank"].toObject());

    return Soldier(firstName, lastName, rankDescription);
}

Soldier::Soldier(const QString &firstName, const QString &lastName, const RankDescription &rank) : id(id),
                                                                                                   firstName(firstName), lastName(lastName), rank(rank) {
}

QJsonObject Soldier::convertToJson() {
    QJsonObject jsonSoldier;
    jsonSoldier["firstName"] = firstName;
    jsonSoldier["lastName"] = lastName;
    jsonSoldier["rank"] = rank.convertToJson();

    return jsonSoldier;
}

long Soldier::getId() const {
    return id;
}

void Soldier::setId(long id) {
    Soldier::id = id;
}

const QString &Soldier::getFirstName() const {
    return firstName;
}

void Soldier::setFirstName(const QString &firstName) {
    Soldier::firstName = firstName;
}

const QString &Soldier::getLastName() const {
    return lastName;
}

void Soldier::setLastName(const QString &lastName) {
    Soldier::lastName = lastName;
}

const RankDescription &Soldier::getRank() const {
    return rank;
}

void Soldier::setRank(const RankDescription &rank) {
    Soldier::rank = rank;
}
