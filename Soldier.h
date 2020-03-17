#ifndef SOLDIERAPP_SOLDIER_H
#define SOLDIERAPP_SOLDIER_H

#include <QtCore/QString>

class Soldier {
public:
    Soldier(const QString &firstName, const QString &lastName);

    const QString &getFirstName() const;

    void setFirstName(const QString &firstName);

    const QString &getLastName() const;

    void setLastName(const QString &lastName);

private:
    QString firstName;
    QString lastName;
//TODO: add rank(enum?)

};

#endif //SOLDIERAPP_SOLDIER_H
