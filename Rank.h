#ifndef SOLDIERAPP_RANK_H
#define SOLDIERAPP_RANK_H

#include <QtCore/QString>
#include <QtCore/QMetaType>

struct Rank {
    Rank() = default;

    Rank(const QString &name);
    Rank(const char *name);

    QString name;
};

Q_DECLARE_METATYPE(Rank)
#endif //SOLDIERAPP_RANK_H
