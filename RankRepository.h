//
// Created by pawlllosss on 18.03.2020.
//

#ifndef SOLDIERAPP_RANKREPOSITORY_H
#define SOLDIERAPP_RANKREPOSITORY_H


#include <list>
#include "Rank.h"

class RankRepository {
public:
    RankRepository();

    const std::list<Rank> &getRanks() const;

private:
    std::list<Rank> ranks;
};

#endif //SOLDIERAPP_RANKREPOSITORY_H
