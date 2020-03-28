//
// Created by pawlllosss on 18.03.2020.
//

#ifndef SOLDIERAPP_RANKREPOSITORY_H
#define SOLDIERAPP_RANKREPOSITORY_H


#include <list>
#include "RankDescription.h"

class RankRepository {
public:
    RankRepository();

    const std::list<RankDescription> &getRanks() const;

private:
    std::list<RankDescription> ranks;
};

#endif //SOLDIERAPP_RANKREPOSITORY_H
