#include "Soldier.h"

Soldier::Soldier(const QString &firstName, const QString &lastName) : firstName(firstName), lastName(lastName) {
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
