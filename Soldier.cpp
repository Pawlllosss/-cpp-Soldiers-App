#include <QtCore/QJsonObject>
#include "Soldier.h"

Soldier::Soldier(const QString &firstName, const QString &lastName, const Rank &rank) : id(id),
                                                        firstName(firstName), lastName(lastName), rank(rank) {
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

const Rank &Soldier::getRank() const {
    return rank;
}

void Soldier::setRank(const Rank &rank) {
    Soldier::rank = rank;
}

QJsonObject Soldier::convertToJson() {
    QJsonObject jsonSoldier;
    jsonSoldier["firstName"] = firstName;
    jsonSoldier["lastName"] = lastName;
    jsonSoldier["rank"] = rank.name;

    return jsonSoldier;
}

void Soldier::setId(long id) {
    Soldier::id = id;
}

long Soldier::getId() const {
    return id;
}
